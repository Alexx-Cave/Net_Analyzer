#ifndef TUI_VALUELIST_H
#define TUI_VALUELIST_H
#include <vector>
#include <tui_defs.h>
#include <tui_abslist.h>

/** Элемент спика ключ-значение*/
struct TUIValueListItem
{
	std::string text;
	int color;
	std::string val;
	int dtype;
};

/** Редактор списка ключ-значение*/
class TUIValueListEdit : public TUIAbstractListEdit
{
public:
	/**
	 * @param _mainwin главное окно (фоновое)
	 * @param _title заголовок
	 * @param filler символ заплнитель пустого места строки редактирования
	 * @param _editWidth ширина строки редактирования
	 * @param _scrollsize высота области прокрутки (видимое количество элементов)
	 * @param _alterHomeAndEnd По умолчанию кнопки HOME/END переходят от
	 * первого контрола к последнему. Включение _alterHomeAndEnd приводит
	 * к тому, что курсор будет перемещаться внутри текущего контрола.
	 */
	TUIValueListEdit(WINDOW *_mainwin, const std::string &_title, chtype _filler = ' ', size_t _editWidth = 20, size_t _scrollsize = 0, bool _alterHomeAndEnd = false);
	/** Добавить элемент в список
	 * @param itemText текст
	 * @param itemColor цвет
	 * @param itemType тип вводимой информации CHAR, INT, PASS_CHAR, PASS_INT.
	 * Префикс PASS обозначает что строка скрывается символом <b>*</b>.
	 */
	void add(const std::string &itemText, const int itemColor = TUI_NORMAL_COLOR,
		const int itemType = CHAR);
	/// Очистить список
	void clear() override;
	/// Получить ширину окна
	size_t width() override;

	virtual void draw() override;

	virtual void drawSelected() override;

	virtual WINDOW* getFocusWindow() override;

	/// Выполнить диалог
	bool exec() override;
	/** Получить вводимое значение
	 * @param index порядковый номер элемента
	 * @return значение
	 */
	std::string getValue(int index) const;
	/// Получить количество элементов
	size_t valueCount() const override;
	/** Установить вводимое значение
	 * @param index порядковый номер элемента
	 * @param val значение
	 */
	void setValue(int index, const std::string &value);

protected:
	std::vector<TUIValueListItem> itemsList;
private:
	chtype filler;
	size_t editWidth;
	bool alterHomeAndEnd;
	size_t offset;
};
#endif
