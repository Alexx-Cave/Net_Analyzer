#pragma once

#include <string>
#include <memory.h>
#include <cstdint>
#include <stdlib.h>


/** @brief длина строки в символах
* @param s строка
*/
size_t tui_utf8_strlen(const char *s);
/** @brief смещение до символа в байтах
* @param s строка
* @param pos номер символа
*/
size_t tui_utf8_string_offset(const std::string &s, int pos);

/** @brief возвращает подстроку длиной не более указанной
* @param str строка
* @param start начальная позиция
* @param len максимальная длина
*/
std::string tui_utf8_substr(const std::string &str, size_t start = 0,
	size_t len = std::string::npos);

/* utility predicates used by the above */
int octal_digit(char c);
int hex_digit(char c);

/** конвертирует символ в UTF-8
* @param ch код символа
* @param dest UTF-8-последовательность
*/
int u8_wc_toutf8(char *dest, uint32_t ch);

/** @brief читает escape-последовательность, сохраняя её в виде 32-битного значения
* @return количество символов в последовательности
* @param str указатель на символ, следующий за backslach
* @param dest указатель на выходное значение
*/
int u8_read_escape_sequence(char *str, uint32_t *dest);

/** @brief конвертирует строку "src", содержащую UTF-escape-последовательности в UTF-8
* @param src строка
* @param sz максимальная длина
*/
int u8_unescape(char *buf, int sz, char *src);

/** @brief конвертирует строку "src_str", содержащую UTF-escape-последовательности в UTF-8
* @param src строка
* @param out_len длина строки
*/
std::string UCtoU8(const std::string &src_str, size_t out_len);
