#ifndef TUI_LOG_VIEW_H
#define TUI_LOG_VIEW_H
#include <tui_absview.h>

class TUILogView : public TUIAbstractView
{
public:
	TUILogView(WINDOW *mainwin, const std::string &title);

	void log(const std::string &str);
	virtual void exec() override;
};
#endif
