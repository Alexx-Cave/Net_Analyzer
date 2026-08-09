#ifndef TUI_BACKGROUND_H
#define TUI_BACKGROUND_H
#include <string>
#include <ncurses.h>
#include <tui_defs.h>
#include <tui_abswindow.h>

/** @brief Класс фона приложения*/
class TUIBackground : public TUIAbstractWindow
{
public:
	/** Конструктор
	 * @param _mainwin главное окно (фоновое)
	 * @param _colorBack цвета фона
	 * @param _colorBars цвет заголовков
	 */
	explicit TUIBackground(WINDOW *_window, int _colorBack = TUI_BACKGROUND_COLOR,
			int _colorBars = TUI_TITLEBARS_COLOR);

	virtual void draw() override;

	virtual void drawSelected() override;

	virtual WINDOW* getFocusWindow() override;

	/** Нарисовать текст в окне и не закрывая его вернуть управление
	 * @param mes текст
	 * @param color цвет
	 */
	void showInfo(const std::string &mes, const int color = TUI_NORMAL_COLOR);
	/** Сообщение в строке состояния (нижняя строка)
	 * @param mes текст
	 */
	void printStatusBar(const std::string &mes);
	/** Установить текст заголовока
	 * @param _title новый текст
	 */
	void setTitle(const std::string &_title);
	/** Получить текст заголовка
	 * @return текст
	 */
	std::string getTitle() const;

	/** Получить текст, который последним устанавливался в printStatusBar()
	 * @return текст
	 */
	std::string getLastMsg() const;

private:
	WINDOW *window;
	int colorBack,colorBars;
	std::string title;
	std::string last_msg;
};
#endif
