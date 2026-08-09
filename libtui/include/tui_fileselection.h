#ifndef TUI_FILE_SELECTION_DIALOG_H
#define TUI_FILE_SELECTION_DIALOG_H
#include <tui_absselection.h>

/** @brief Диалог выбора файла*/
class TUIFileSelectionDialog : public TUIAbstractSelection
{
public:
	/** Конструктор
	 * @param _mainwin главное окно (фоновое)
	 * @param _title заголовок
	 * @param height высота окна
	 * @param width ширина окна
	 */
	TUIFileSelectionDialog(WINDOW *mainwin, const std::string &title, size_t height = 10,
		size_t width = 50);
	/** Выполнить диалог
	 * @param[out] selectedFile выбранный файл
	 * @param currentItem номер выделенного элемента
	 * @return -1 если пользователь не завершил корректный выбор, 0 - если нажат Esc, 1 при успешном выборе файла,
	 *	индекс выбранного элемента при выборе элемента после списка файлов
	 */
	int exec(std::string &selectedFile, size_t currentItem = 0);
	/** Добавить файлы
	 * @param pattern список файлов по маске
	 */
	void dir(const char *pattern);
	/** Добавить элемент после списка файлов
	 * @param itemText текст
	 * @param itemColor цвет
	 * @param itemId DB ID элемента (ID записи в БД)
	 * @param bold будет использовать выделение элемента (яркий цвет)
	 */
	void add(const std::string &itemText);
	/** Очистить все файлы */
	virtual void clear() override;

	virtual WINDOW* getFocusWindow() override;

private:
	std::vector<std::string> foundFiles;
	std::vector<std::string> filenamesList;
	std::vector<std::string> additionalItemsList;
};
#endif
