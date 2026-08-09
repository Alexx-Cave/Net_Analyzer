#ifndef TUI_ABSTRACT_SELECTION_LIST_H
#define TUI_ABSTRACT_SELECTION_LIST_H
#include <tui_absitems.h>

/** @brief Класс абстрактного списока элементов*/
class TUIAbstractSelection : public TUIAbstractItemsListParent
{
public:
	/** Конструктор
	 * @param _mainwin главное окно (фоновое)
	 * @param _title заголовок
	 * @param _scrollbarPlacement место скролера RIGHT/LEFT
	 * @param _height высота окна
	 * @param _width высота окна
	 * @param _upDownCycle переходит ли курсор после последней позиции на первую
	 */
	TUIAbstractSelection(WINDOW *_mainwin, const std::string &_title, int _scrollbarPlacement,
		size_t _height, size_t _width, bool _upDownCycle = false);
	/** Получить тип завершения диалога
	 * @return false если пользователь не завершил корректный выбор
	 */
	bool exitType() const;
	/** Установить текст заголовока
	 * @param _title новый текст
	 */
	void setTitle(const std::string &_title);
	/** Получить высоту заголовка
	 * @return высота
	 */
	size_t titleHeight() const;
	/** Установить текущий элемент
	 * @param item позиция курсора
	 */
	void setCurrentItem(size_t item);
	/** Получить текущий элемент
	 * @return позиция курсора
	 */
	size_t getCurrentItem() const;
	/** Удалить текущий элемент
	 * @return позиция курсора
	 */
	size_t removeCurrentItem();
	/** Получить текст текущего элемент
	 * @return текст
	 */
	std::string getCurrentItemText() const;
	/** Событие нажатие на клавишу
	 * @param key код клавиши
	 */
	virtual KeyEventResult keyPressedEvent(int key);
protected:
	virtual void draw() override;

	virtual void drawSelected() override;

	/** Запустить интерфейс, возврат управления при нажатии на Enter или ESC
	 * @return выбранный элемент
	 */
	int run();
	/** Получить строку готовую для печати длиной не более len
	 * @param _str исходная строка
	 * @param len максимальная длина
	 * @return строку готовую для печати
	 */
	std::string getPrintString(const std::string &_str, const int len);
	/** Событие нажатие на клавишу не обрабатываемую интерфейсом
	 * @param key код клавиши
	 */
	virtual void unknownKeyPressed(int key);
	size_t curLeft, curItem, curTop;
	WINDOW *mainwin;
private:
	bool exitTypeVal;
	size_t height, width;
	int scrollbarPlacement;
	std::string title;
	bool upDownCycle;
	std::string expandPrintString(const std::string &str);
};
#endif
