#pragma once
#include <string>
#include <ncurses.h>
#include <tui_abswindow.h>

/** Абстрактный редактор списка элементов*/
class TUIAbstractListEdit : public TUIAbstractWindow
{
public:
	/**
	 * @param _mainwin главное окно (фоновое)
	 * @param _title заголовок
	 * @param _scrollsize высота области прокрутки (видимое количество элементов)
	 */
	TUIAbstractListEdit(WINDOW *_mainwin, const std::string &_title, size_t _scrollsize = 0);
	~TUIAbstractListEdit() override;
	/// Событие нажатие на клавишу
	virtual KeyEventResult keyPressedEvent(int key);
	/// Очистить список
	virtual void clear() = 0;
	/// Установить текст заголовока
	void setTitle(const std::string &_title);
	/// Получить высоту заголовка
	size_t titleHeight() const;
	/// Получить высоту окна
	size_t height() const;
	/// Получить ширину окна
	virtual size_t width() = 0;
	/// Нарисовать все и вернуть управление
	virtual void draw() override = 0;
	/// Выполнить диалог
	virtual bool exec() = 0;
	/// Получить количество элементов
	virtual size_t valueCount() const = 0;
protected:
	WINDOW *mainwin;
	WINDOW *shadow;
	WINDOW *win;
	std::string title;
	size_t scrollsize;
	size_t curItem, curTop, curPos;
};
