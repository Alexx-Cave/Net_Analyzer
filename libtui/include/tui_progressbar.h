#include <string>
#include <ncurses.h>
#include <tui_abswindow.h>
#include <tui_defs.h>

class TUIProgressBar : public TUIAbstractWindow
{
public:
	TUIProgressBar(WINDOW *_mainwin, const std::string &_title, uint32_t _width = 54,
		uint32_t _height = 5);

	void draw() override;
	void drawSelected() override;
	WINDOW* getFocusWindow() override;
	void setProgress(int percent);
private:
	WINDOW *mainwin;
	WINDOW *progress;
	WINDOW *win;
	std::string title;
	uint32_t width, height;
};
