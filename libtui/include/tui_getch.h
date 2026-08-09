#ifndef TUI_GETCH_H
#define TUI_GETCH_H

#include <ncurses.h>
#include "tui_abswindow.h"

/** Функция для обработки времени ожидания клавиатурного ввода
 * @param input_focus_item - окно, которое в данный момент ожидает клавиатурный ввод
 * @param continuous_idle_seconds - суммарное время ожидания клавиатурного ввода
 * @param nesting_level - уровень вложенности обработчика (1..+inf)
 * (обработчик будет вложенным если вызов tuiGetch(), который привёл к вызову этого обработчика, был
 * сам вызван в обработчике ожидания клавиатурного ввода. Например в обработчике можно вызвать message box
 * и тогда косвенно вызовется tuiGetch())
 */
typedef void (*TUIIdleCallback)(TUIAbstractWindow *input_focus_item, int continuous_idle_seconds,
	int nesting_level);

/** Ожидание нажатия клавиши на клавиатуре
 * если нажатие долго не происходит - вызывается callback, установленный tuiSetIdleCallback
 * Если callback не установлен, tuiGetch работает как простой wgetch()
 * @param input_focus_item - окно, которое в данный момент ожидает клавиатурный ввод
 * @return код нажатой клавиши
 */
int tuiGetch(TUIAbstractWindow *input_focus_item);

/** Установка callback-а, который в цикле вызывается при достаточно длительном
 * ожидании клавиатурного ввода.
 * @param idle_cb - callback обрабатывающий время ожидания
 * @param millisec_delay - время безрезультатного ожидания ввода до очередного вызова callback-а
 */
 int tuiSetIdleCallback(TUIIdleCallback idle_cb, int millisec_delay);

 /** Проверка нажатия клавиши
  * @param timeout таймаут ожидания нажатия в секундах
  * @return true если за timeout была нажата клавиша
  */
bool tuiIfKeyPressed(float timeout);

#endif
