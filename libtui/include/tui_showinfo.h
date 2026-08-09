/** @file tui_showinfo.h
 * @brief Заголовочный функции showInfo
 */
#pragma once
#include <string>
#include <ncurses.h>
/** Показывает сообщение в окошке. Ожидает нажатия клавиш Enter или ESC.
 * Поддеживаются многострочные сообщения.
 */
void showInfo(WINDOW *mainwin, const std::string &info);
/** Показывает сообщение и пишет его в журнал
 */
void showInfoAndLog(WINDOW *mainwin, const std::string &info);
