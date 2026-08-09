//============================================================================
// Name        : Net_analyzer.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================
#include <clocale>
#include <string>

#include <tui_background.h>
#include <tui_selectionmenu.h>
#include <tui_dialog.h>
#include <tui_showinfo.h>
#include <tui_lineedit.h>
#include <tui_fileview.h>
#include "tools.h"

using namespace std;

int main() {

	setlocale(LC_ALL, "ru_RU.UTF-8");
	WINDOW *cursesWin = initscr();
	initColorPairs();

	TUIBackground *x = new TUIBackground(cursesWin);
	x->setTitle("Сетевой Анализатор (версия 1.0)");
	x->draw();
	x->printStatusBar(" Стрелочки - перемещение    Enter - выбор    Escape - выход");

	TUISelectionMenu menu(cursesWin, "Главное меню");
	menu.add("Сканирование ЛВС");					// 0
	menu.add("Сканирование хоста или подсети");	// 1
	menu.add("Диагностика сети");					// 2
	menu.add("Сетевые интерфейсы");				// 3
	menu.add("Информация о программе");			// 4
	menu.add("Выход");								// 5

	while (1) {
		int number = menu.exec();

		if (number == 5 || ! menu.exitType()) {
			TUIDiaLog newdialog(cursesWin);
			newdialog.add(" Вы хотите выйти? ");
			newdialog.addButton(" Да ");	// 0
			newdialog.addButton(" Нет ");	// 1

			int exit = newdialog.exec();
			if (exit == 0 && newdialog.exitType()) {
				break;
			}
		}

		if (number == 4) {
			showInfo(cursesWin, " Автор: Александр Курасов \n"
								" Школа: ГБОУ №1363\n"
								" Класс: 11Д" );
		}

		if (number == 3) {
			GetNetInterfaces(cursesWin);
			x->draw();
			x->printStatusBar(" Стрелочки - перемещение    Enter - выбор    Escape - выход");
		}

		if (number == 2) {
			TUISelectionMenu dopmenu(cursesWin, "Диагностика сети");
			dopmenu.add("PING");					// 0
			dopmenu.add("TRACEROUTE");				// 1
			dopmenu.add("ARP таблица");			// 2
			dopmenu.add("Возврат в главное меню");	// 3

			while (1) {
				int number = dopmenu.exec();

				if (number == 3 || ! dopmenu.exitType()) {
					break;
				}

				switch (number) {
					case 0:
						TestPing(cursesWin);
						break;
					case 1:
						TestTraceroute(cursesWin);
						break;
					case 2:
						TestArp(cursesWin);
						break;
				}
				x->draw();
				x->printStatusBar(" Стрелочки - перемещение    Enter - выбор    Escape - выход");
			}
		}

		if (number == 1) {
			TUILineEdit dialogadr(cursesWin, " Сканирование хоста или подсети ", " Адрес: ");
			dialogadr.exec();
			if (!dialogadr.exitType()) {
				continue;
			}
			string str = dialogadr.getValue();
			if (str.size() == 0) {
				continue;
			}
			if (isValidIpOrHostname(str) == false) {
				showInfo(cursesWin, str + " - Неверный адрес");
				continue;
			}
			PrepareScanReport(str, "file", x);
			TUIFileView results(cursesWin, "Результаты сканирования");
			results.loadFile("file");
			results.exec();
			x->draw();
			x->printStatusBar(" Стрелочки - перемещение    Enter - выбор    Escape - выход");
			remove("file");
		}

		if (number == 0) {
			TUISelectionMenu dopmenu(cursesWin, "Выбор сетевого интервейса");
			auto list = GetNetInterfaces();
			for (auto el : list) {
				dopmenu.add(el.name + "   (" + el.addr + ") ");
			}
			int number = dopmenu.exec();
			if (! dopmenu.exitType()) {
				continue;
			}
			string str = list[number].subnet + "/" + list[number].mask;
			PrepareScanReport(str, "file", x);
			TUIFileView results(cursesWin, "Результаты сканирования");
			results.loadFile("file");
			results.exec();
			x->draw();
			x->printStatusBar(" Стрелочки - перемещение    Enter - выбор    Escape - выход");
			remove("file");
		}
	}

	delete x;
	clear();
	refresh();
	endwin();
	return 0;
}
