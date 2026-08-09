#ifndef TUI_RADIODIALOG_H
#define TUI_RADIODIALOG_H
#include <map>
#include <tui_absitems.h>

class TUIRadioDialog : public TUIAbstractItemsListParent
{
public:
	explicit TUIRadioDialog(WINDOW *_mainwin, const std::string &title);
	int exec();
	size_t width();
	size_t height() const;
	bool exitType() const;
	void addButton(const std::string &itemText, bool cancel_button = false,
		const int itemColor = TUI_NORMAL_COLOR);
	bool selectRadioById(uint64_t id);
	bool selectRadioByIdx(int idx);
	void clearButtons();
	void draw(int ypos, int xpos, bool refresh);
	virtual KeyEventResult keyPressedEvent(int key);
	virtual void draw() override;
	virtual void drawSelected() override;
	void drawUnSelected();
	virtual WINDOW* getFocusWindow() override;
	int selectedRadioIdx() const;
	uint64_t selectedRadioId() const;
private:
	WINDOW *mainwin;
	std::string title;
	std::vector<TUIListItem> buttonList;
	std::map<int, int> buttonPos;
	bool exitTypeVal;
	size_t curPos;
	size_t curRadio;
	int cancelButtonIdx;
};

#endif // TUI_RADIODIALOG_H
