#ifndef TUI_DIALOG_H
#define TUI_DIALOG_H
#include <map>
#include <tui_absitems.h>

/** @brief Класс диалога (текст и кнопки)*/
class TUIDiaLog : public TUIAbstractItemsListParent
{
public:
	/** Конструктор
	 * @param _mainwin главное окно (фоновое)
	 */
	explicit TUIDiaLog(WINDOW *_mainwin);
	/** Выполнить диалог*/
	int exec();
	/** Получить ширину окна
	 * @return ширина
	 */
	size_t width();
	/** Получить высоту окна
	 * @return высота
	 */
	size_t height() const;
	/** Получить тип завершения диалога
	 * @return false если пользователь не завершил корректный выбор
	 */
	bool exitType() const;
	/** Добавить кнопку
	 * @param itemText текст
	 * @param itemColor цвет
	 */
	void addButton(const std::string &itemText, const int itemColor = TUI_NORMAL_COLOR);

	// Установить выбранный элемент
	void setSelection(size_t pos);

	/// Удалить все кнопки
	void clearButtons();

	/** Нарисовать все и вернуть управление
	 * @param ypos позиция окна по вертикали
	 * @param xpos позиция окна по горизонтали
	 * @param refresh вызывать ли функцию обновления окна
	 */
	void draw(int ypos, int xpos, bool refresh);

	/** Событие нажатие на клавишу
	 * @param key код клавиши
	 */
	virtual KeyEventResult keyPressedEvent(int key);

	virtual void draw() override;

	virtual void drawSelected() override;

	virtual WINDOW* getFocusWindow() override;
private:
	WINDOW *mainwin;
	std::vector<TUIListItem> buttonList;
	std::map<int, int> buttonPos;
	bool exitTypeVal;
	size_t curPos;
};
#endif
