#ifndef TUI_MASKEDIT_H
#define TUI_MASKEDIT_H
#include <tui_lineedit.h>

/** @brief Однострочный редактор маскированного значения*/
class TUIMaskedEdit : public TUILineEdit
{
public:
	/** Конструктор
	 * @param _mainwin главное окно (фоновое)
	 * @param _title заголовок 
	 * @param _label текст слева от строки редактирование
	 * @param plate задает маску где символ <b>#</b> используется как
	 * место где пользователь может вводить свой символ. Пример :
	 * <i>###.###.###.###</i> маска для редактирования IP адреса.
	 * @param filler символ заплнитель пустого места строки редактирования
	 */
	TUIMaskedEdit(WINDOW *_mainwin, const std::string &title, const std::string &_label,
		const std::string &plate, chtype _filler = ' ');
	/** Установить вводимое значение
	 * @param val значение
	 */
	virtual void setValue(const std::string &_val) override;
	/** Очистить вводимое значение */
	virtual void clear(void) override;
	/** Получить ширину окна
	 * @return ширина
	 */
	virtual size_t width(void) override;
	/** Получить вводимое значение наложенное на маску
	 * @return значение
	 */
	std::string mixed(void);
	/** Выполнить диалог
	 * @return введенное значение
	 */
	virtual const char *exec(void) override;
	/** Проверить возможность вставки в позицию
	 * @param key код клавиши
	 * @param pos позиция
	 */
	virtual bool validateInsert(int key, int pos);

	virtual void draw(void) override;

	virtual void drawSelected(void) override;

	virtual WINDOW* getFocusWindow() override;

private:
	std::string mask;
	/** Получение позиции курсрора в строке с маской
	 * @param pos позиция курсора в вводимой строке без маски
	 * @return абсолютноя позиция курсора
	 */
	size_t mixCursorPos(const size_t pos);
	/** Размер введенных символов, без учета фиксированных символов маски
	 * @return длина строки
	 */
	size_t valSize(void) const;
	
	void clearImpl(void);
};
#endif
