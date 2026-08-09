#ifndef TUI_LABEL_H
#define TUI_LABEL_H
#include <tui_absitems.h>


/**
 * @brief Тип выравнивания для текста
 */
enum TUILabelAlign {
	ALIGN_LEFT,
	ALIGN_RIGHT,
	ALIGN_CENTER
};

/** @brief Сообщение пользователю*/
class TUILabel : public TUIAbstractItemsListParent
{
public:
	/** Конструктор
	 * @param _mainwin главное окно (фоновое)
	 * @param _title_lines высота заголовка
	 */
	explicit TUILabel(WINDOW *_mainwin, size_t _title_lines = 0);
	/** Коструктор
	 * @param _mainwin главное окно (фоновое)
	 * @param _title_lines высота загаловка
	 * @param _align выравнивание
	 */
	TUILabel(WINDOW *_mainwin, size_t _title_lines, TUILabelAlign _align);
	/** Получить ширину окна
	 * @return ширина
	 */
	size_t width();
	/** Получить высоту окна
	 * @return высота
	 */
	size_t height() const;
	/** Нарисовать все и вернуть управление
	 * @param ypos позиция окна по вертикали
	 * @param xpos позиция окна по горизонтали
	 * @param refresh вызывать ли функцию обновления окна
	 */
	void draw(int ypos, int xpos, bool refresh);

	/** Выполнить диалог. Соообщение будет показано пользователю,
	 * пока он не нажмент Enter или ESC.
	 * @return true если пользователь нажал Enter,
	 * false если ESC.
	 */

	virtual void draw() override;

	virtual void drawSelected() override;

	virtual WINDOW *getFocusWindow() override;

	bool exec();

	/** Событие нажатие на клавишу
	 * @param key код клавиши
	 */
	virtual KeyEventResult keyPressedEvent(int key);
private:
	WINDOW *mainwin;
	size_t title_lines;
	TUILabelAlign align;
};
#endif
