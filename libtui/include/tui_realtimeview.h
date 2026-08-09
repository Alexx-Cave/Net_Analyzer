#ifndef TUI_REAL_TIME_VIEW_H
#define TUI_REAL_TIME_VIEW_H
#include <tui_logview.h>

class TUIRealTimeView : public TUILogView {
public:
	TUIRealTimeView(WINDOW *mainwin, const std::string &title);
	void exec() override;
};
#endif
