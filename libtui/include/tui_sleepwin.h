/** @file tui_sleepwin.h
 * @brief Заголовочный функции showSleepWin
 */
#pragma once
#include <string>
#include <ncurses.h>
/** Показывает окно с сообщением и усыпляет вызвавший процесс на указанное число секунд.
 * Поддеживаются многострочные сообщения.
 */
void showSleepWin(WINDOW *mainwin, const std::string &info, uint32_t seconds);
