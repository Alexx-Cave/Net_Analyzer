#ifndef TUI_LISTBOX_H
#define TUI_LISTBOX_H
#include <tui_absselection.h>

/** @brief Полноэкранный реадктор списка элементов.*/
class TUIListBox : public TUIAbstractSelection
{
public:
	/** Конструктор
	 * @param _mainwin главное окно (фоновое)
	 * @param _title заголовок
	 * @param _scrollbarPlacement место скролера RIGHT/LEFT
	 */
	TUIListBox(WINDOW *mainwin, const std::string &title, int scrollbarPlacement = RIGHT);
	/** Выполнить диалог
	 * @param[out] selectedFile выбранный файл
	 * @return false если пользователь не завершил корректный выбор
	 */
	virtual void exec();
	/** Событие удаление элемента
	 * @param id порядковый номер элемента
	 */
	virtual bool deleteItemEvent(int id);
	/** Событие редактирование элемента
	 * @param id порядковый номер элемента
	 * @param itemText новый текст
	 */
	virtual bool editItemEvent(int id, std::string &itemText);
	/** Событие добавление элемента
	 * @param itemText текст
	 */
	virtual bool newItemEvent(std::string &itemText);

	WINDOW* getFocusWindow() override;
protected:
	/** Событие нажатие на клавишу не обрабатываемую интерфейсом
	 * @param key код клавиши
	 */
	virtual void unknownKeyPressed(int key) override;
};
#endif
