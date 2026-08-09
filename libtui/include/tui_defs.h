/** @file tui_defs.h
 *  @brief Заголовочный констант
 */
#pragma once

#include <cstdint>
#include <string>
#include <ncurses.h>

#define	LEFT		0
#define RIGHT		1
#define CHAR		0x0002
#define INT		0x0103
#define PASS_BASE	0x1000
#define PASS_CHAR	0x1002
#define PASS_INT	0x1103

#define TUI_NORMAL_COLOR	1
#define TUI_WINDOW_COLOR	2
#define TUI_INFO_COLOR		3
#define TUI_ERROR_COLOR		4
#define TUI_WARNING_COLOR	5
#define TUI_DISABLED_COLOR	6
#define TUI_BACKGROUND_COLOR	7
#define TUI_TITLEBARS_COLOR	8
#define TUI_EDITVALUE_COLOR	9
#define TUI_SHADOW_COLOR	10
#define TUI_BACK_INFO_COLOR	11
#define TUI_BACK_ERROR_COLOR	12
#define TUI_PROGRESSBAR_COLOR	13

#ifndef  KEY_ESC
#define KEY_ESC		'\033'
#endif
#ifndef  KEY_DELETE
#define KEY_DELETE	'\177'
#endif
#undef  KEY_F1
#define KEY_F1		KEY_F(1)
#undef  KEY_F2
#define KEY_F2		KEY_F(2)
#undef  KEY_F3
#define KEY_F3		KEY_F(3)
#undef  KEY_F4
#define KEY_F4		KEY_F(4)
#undef  KEY_F5
#define KEY_F5		KEY_F(5)
#undef  KEY_F6
#define KEY_F6		KEY_F(6)
#undef  KEY_F7
#define KEY_F7		KEY_F(7)
#undef  KEY_F8
#define KEY_F8		KEY_F(8)
#undef  KEY_F9
#define KEY_F9		KEY_F(9)
#undef  KEY_F10
#define KEY_F10		KEY_F(10)
#undef  KEY_F11
#define KEY_F11		KEY_F(11)
#undef  KEY_F12
#define KEY_F12		KEY_F(12)

/** @brief Абстрактный списочный элемент*/
struct TUIListItem
{
	uint64_t id;
	std::string text;
	int color;
	bool bold;
	TUIListItem() : id(0), color(TUI_NORMAL_COLOR), bold(false) {}
};

/** Создание нового окна с проверкой параметров
 * @param (heidht, width) - высота и ширина окна
 * @param (y, x) - координаты левего верхнего угла
 * @return - новое окно или nullptr при ошибке
 */
WINDOW *createNewWin(int height, int width, int y, int x);
/** Нарисовать псевдографическую рамочку по границе окна
 * @param win окно
 */
void drawWindowBox(WINDOW *win);
/// Нарисовать тень
void drawShadow(WINDOW *mainwin, WINDOW ** shadow,
	const size_t height, const size_t width);
/// Инициализация цветовой палитры ncurses*/
void initColorPairs();
