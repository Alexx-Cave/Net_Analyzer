#ifndef TUI_ABSTRACT_EDIT_H
#define TUI_ABSTRACT_EDIT_H
#include <string>
#include <ncurses.h>
#include "tui_abswindow.h"
/** @brief Класс абстрактного редактора */
class TUIAbstractEdit : public TUIAbstractWindow
{
public:
	/** Конструктор
	 * @param _mainwin главное окно (фоновое)
	 */
	explicit TUIAbstractEdit(WINDOW *_mainwin);
	virtual ~TUIAbstractEdit();
	/** Выполнить диалог
	 * @return введенное значение
	 */
	virtual const char *exec() = 0;
	/** Получить тип завершения диалога
	 * @return false если пользователь не завершил корректный ввод
	 */
	virtual bool exitType() = 0;
	/** Установить вводимое значение
	 * @param val значение
	 */
	virtual void setValue(const std::string &val) = 0;
	/** Получить вводимое значение
	 * @return значение
	 */
	virtual std::string getValue() = 0;
	/** Установить минимальное количество символов для ввода
	 * @param chars количество символов
	 */
	virtual void setMinCharactersToEnter(size_t chars) = 0;
	/** Очистить вводимое значение */
	virtual void clear() = 0;
	/** Событие нажатие на клавишу
	 * @param key код клавиши
	 */
	virtual KeyEventResult keyPressedEvent(int key);
protected:
	WINDOW *mainwin;
	WINDOW *win;
	WINDOW *shadow;
};
#endif
