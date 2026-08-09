#ifndef TUI_ABSTRACTWINDOW_H
#define TUI_ABSTRACTWINDOW_H

#include <list>
#include "ncurses.h"

enum KeyEventResult
{
	KE_DEFAULT,
	KE_DONT_PROCESS
};

class TUIAbstractWindow
{
public:
	TUIAbstractWindow();
	virtual ~TUIAbstractWindow();

	/** Нарисовать все и вернуть управление
	 */
	virtual void draw() = 0;

	/** Перерисовать выделенную часть окна
	 * (то, что обычно менятся при нажатии на клавиши: выделенные элементы, фокус ввода и т.п.)
	 * Это оптимизация для уменьшения мерцания картинки.
	 */
	virtual void drawSelected() = 0;

	/** Получить окно ncurses, которое принимает ввод
	 *  (где должен находиться курсор, если он разрешён)
	 *  @return окно ncurses
	 */
	virtual WINDOW* getFocusWindow() = 0;

	/** Сохранить позицию курсора ncurses в этом окне
	 */
	void saveCursorPos();

	/** Восстановить позицию курсора ncurses в этом окне
	 */
	void restoreCursorPos();

	/** Перерисовать все окна в порядке их создания
	 */
	static void redrawAllWindows();

private:
	static std::list<TUIAbstractWindow*> drawables;
	int cursor_y;
	int cursor_x;
};

#endif
