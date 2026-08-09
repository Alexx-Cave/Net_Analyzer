#ifndef TUI_ABSTRACT_VIEW_H
#define TUI_ABSTRACT_VIEW_H
#include <tui_absselection.h>

/** @brief Класс полноэкранного скролера элементов*/
class TUIAbstractView : public TUIAbstractSelection
{
public:
	/** Конструктор
	 * @param _mainwin главное окно (фоновое)
	 * @param _title заголовок
	 * @param _scrollbarPlacement место скролера RIGHT/LEFT
	 */
	TUIAbstractView(WINDOW *mainwin, const std::string &title, int scrollbarPlacement = RIGHT);
	/** Выполнить диалог*/
	virtual void exec();

	virtual WINDOW* getFocusWindow() override;

protected:
	/** Событие нажатие на клавишу не обрабатываемую интерфейсом
	 * @param key код клавиши
	 */
	virtual void unknownKeyPressed(int key) override;
};
#endif
