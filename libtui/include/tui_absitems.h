#pragma once

#include <cstdint>
#include <vector>
#include <ncurses.h>
#include <tui_defs.h>
#include <tui_abswindow.h>

/** @brief Класс абстрактного родителя работающего со списком элементов */
class TUIAbstractItemsListParent : public TUIAbstractWindow
{
public:
	TUIAbstractItemsListParent();
	virtual ~TUIAbstractItemsListParent();
	/** Добавить элемент
	 * @param itemText текст
	 * @param itemColor цвет
	 * @param itemId DB ID элемента (ID записи в БД)
	 * @param bold будет использовать выделение элемента (яркий цвет)
	 */
	void add(const std::string &itemText, const int itemColor = TUI_NORMAL_COLOR,
		const uint64_t itemId = 0, const bool bold = false);
	/** Установить текст элемента
	 * @param id порядковый номер элемента
	 * @param itemText новый текст
	 */
	void setItemText(const int id, const std::string &itemText);
	/** Получить текст элемента
	 * @param id порядковый номер элемента
	 * @returns текст
	 */
	std::string getItemText(const int id) const;
	/** Получить DB ID элемента
	 * @param id порядковый номер элемента
	 * @returns DB ID
	 */
	uint64_t getItemDB(const int id) const;
	/** Очистить все элементы */
	virtual void clear(void);
protected:
	std::vector<TUIListItem> itemsList;
	WINDOW *win;
	WINDOW *shadow;
};
