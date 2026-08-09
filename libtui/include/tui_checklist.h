#pragma once
#include <vector>
#include <tui_defs.h>
#include <tui_abslist.h>

/** Элемент Cписка c Check-Boxами слева*/
struct TUICheckListItem
{
	std::string text;
	int color;
	bool checked;
};

/** Cписок c Check-Boxами слева*/
class TUICheckList : public TUIAbstractListEdit
{
public:
	TUICheckList(WINDOW *_mainwin, const std::string &_title, size_t _scrollsize = 0);
	/// Добавить элемент в список
	void add(const std::string &itemText, const bool checked = false,
		const int itemColor = TUI_NORMAL_COLOR);
	/// Очистить список
	void clear() override;
	/// Получить ширину окна
	size_t width() override;

	virtual void draw() override;

	virtual void drawSelected() override;

	virtual WINDOW* getFocusWindow() override;

	/// Выполнить диалог
	bool exec() override;
	/// Получить значение checkbox для элемента index
	bool getChecked(int index) const;
	/// Установить значение checkbox для элемента index
	void setChecked(int index, bool checked);
	/// Получить количество элементов
	size_t valueCount() const override;
	/// Получить количество checked элементов
	size_t checkedCount() const;

protected:
	std::vector<TUICheckListItem> itemsList;
	/** Событие нажатие на клавишу не обрабатываемую интерфейсом
	 * @param key код клавиши
	 */
	virtual void unknownKeyPressed(int key);
private:
	void drawItem(int index, chtype style);
};
