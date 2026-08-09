#ifndef TUI_LINEEDIT_H
#define TUI_LINEEDIT_H
#include <vector>
#include <tui_defs.h>
#include <tui_absedit.h>

/** @brief Однострочный редактор */
class TUILineEdit : public TUIAbstractEdit
{
public:
	/** Конструктор
	 * @param _mainwin главное окно (фоновое)
	 * @param _title заголовок
	 * @param _label текст слева от строки редактирование
	 * @param filler символ заплнитель пустого места строки редактирования
	 * @param _dtype тип вводимой информации CHAR, INT, PASS_CHAR, PASS_INT.
	 * Префикс PASS обозначает что строка скрывается символом <b>*</b>.
	 */
	TUILineEdit(WINDOW *_mainwin, const std::string &title, const std::string &_label,
		chtype _filler = ACS_CKBOARD, int _dtype =  CHAR, size_t _editWidth = 20);
	/** Выполнить диалог
	 * @return введенное значение
	 */
	virtual const char *exec(void) override;
	/** Получить тип завершения диалога
	 * @return false если пользователь не завершил корректный ввод
	 */
	virtual bool exitType(void) override;
	/** Установить вводимое значение
	 * @param val значение
	 */
	virtual void setValue(const std::string &_val) override;
	/** Получить вводимое значение
	 * @return значение
	 */
	virtual std::string getValue(void) override;
	/** Установить минимальное количество символов для ввода
	 * @param chars количество символов
	 */
	virtual void setMinCharactersToEnter(size_t chars) override;
	/** Установить максимальное количество символов для ввода
	 * @param chars количество символов
	 */
	void setMaxCharactersToEnter(size_t chars);
	/** Очистить вводимое значение */
	virtual void clear(void) override;
	/** Нарисовать все и вернуть управление
	 * @param ypos позиция окна по вертикали
	 * @param xpos позиция окна по горизонтали
	 * @param refresh вызывать ли функцию обновления окна
	 */
	void draw(int ypos, int xpos, bool refresh);

	virtual void draw(void) override;

	virtual void drawSelected(void) override;

	virtual WINDOW* getFocusWindow() override;

	/** Получить ширину окна
	 * @return ширина
	 */
	virtual size_t width(void);
	/** Получить высоту окна
	 * @return высота
	 */
	size_t height(void) const;

protected:
	std::vector<TUIListItem> itemsList;
	std::string label;
	std::string val;
	chtype filler;
	bool exitTypeVal;
	size_t curPos;
private:
	size_t minChars, maxChars;
	int dtype;
	size_t editWidth;
	size_t offset;
};
#endif
