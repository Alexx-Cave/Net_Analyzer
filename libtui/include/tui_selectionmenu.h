#ifndef TUI_SELECTION_MENU_H
#define TUI_SELECTION_MENU_H
#include <string>
#include <tui_absselection.h>

/** @brief Меню*/
class TUISelectionMenu : public TUIAbstractSelection
{
public:
	/** Конструктор
	 * @param _mainwin главное окно (фоновое)
	 * @param _title заголовок
	 * @param _height высота окна
	 * @param _width высота окна
	 */
	TUISelectionMenu(WINDOW *mainwin, const std::string &title, size_t height = 10, size_t width = 50);
	/** Выполнить диалог
	 * @return порядковый номер выбранного элемента меню
	 */
	int exec();

	virtual WINDOW* getFocusWindow() override;
};
#endif
