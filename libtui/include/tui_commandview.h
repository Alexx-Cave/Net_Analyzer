#ifndef TUI_COMMAND_VIEW_H
#define TUI_COMMAND_VIEW_H

#include <tui_absview.h>

/// Класс показа результата работы команды в online режиме
class TUICommandView : public TUIAbstractView
{
public:
	/// @param redrawLines кол-во строк через которое содержимое окна будет обновляться
	TUICommandView(WINDOW *mainwin, const std::string &title,
		int scrollbarPlacement = RIGHT, size_t redrawLines = 5);
	virtual ~TUICommandView() override;
	int runCommand(const std::string &command);
	virtual void exec() override;
	void stop();
	bool running() const;
	virtual void draw() override;
private:
	FILE *fp;
	std::string cmd;
	bool isActive;
	size_t redrawLines;
};

#endif
