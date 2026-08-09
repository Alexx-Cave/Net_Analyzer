#pragma once
#include <tui_absselection.h>

/** @brief Диалог выбора файла*/
class TUIExFileSelectionDialog : public TUIAbstractSelection
{
public:
	/** Конструктор
	 * @param _mainwin главное окно (фоновое)
	 * @param _title заголовок
	 * @param height высота окна
	 * @param width ширина окна
	 */
	TUIExFileSelectionDialog(WINDOW *mainwin, const std::string &title, size_t height = 10,
		size_t width = 50);
	/** Выполнить диалог
	 * @return false если пользователь не завершил корректный выбор
	 */
	bool exec(const std::string &pattern);
	/** Добавить файлы
	 * @param pattern список файлов по маске
	 */
	void setPath(const std::string &_path);
	/** Получить название выбранного файла
	 * @returns имя файла
	 */
	std::string getSelectedFile() const;

	virtual WINDOW* getFocusWindow() override;

private:
	std::string path;
	std::string file;
};
