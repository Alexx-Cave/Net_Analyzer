#ifndef TUI_FILE_VIEW_H
#define TUI_FILE_VIEW_H
#include <tui_absview.h>
#include <tui_defs.h>

/** @brief Класс полноэкранного скролера элементов текстового файла*/
class TUIFileView : public TUIAbstractView
{
public:
	/** Конструктор
	 * @param _mainwin главное окно (фоновое)
	 * @param _title заголовок
	 * @param _scrollbarPlacement место скролера RIGHT/LEFT
	 */
	TUIFileView(WINDOW *mainwin, const std::string &title, int scrollbarPlacement = RIGHT);
	/** Загрузить файл
	 * @param filename имя файла
	 */
	bool loadFile(const std::string &filename);
	/** Событие чтение строки файла
	 * @param line содиржимое строки
	 * @return цвет который будет присвоен строке
	 */
	virtual int lineReadEvent(char *line);

	virtual WINDOW* getFocusWindow() override;
};
#endif
