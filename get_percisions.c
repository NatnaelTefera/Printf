#include "main.h"

/**
 * get_precision - Parses and retrieves the precision for printing.
 * @format: The format string that may contain precision specifications.
 * @i: Pointer to the current position in the format string.
 * @list: The variable argument list.
 *
 * Return: The parsed precision value or -1 if not found.
 */
int get_precision(const char *format, int *i, va_list list) {
    int curr_i = *i + 1;
    int precision = -1;

    // Check if precision is specified with a period ('.')
    if (format[curr_i] != '.')
        return precision;

    precision = 0;

    // Parse the precision value
    for (curr_i++; is_digit(format[curr_i]) || format[curr_i] == '*'; curr_i++) {
        if (format[curr_i] == '*') {
            curr_i++;
            precision = va_arg(list, int);
            break;
        }
        precision = precision * 10 + (format[curr_i] - '0');
    }

    // Update the current position pointer
    *i = curr_i - 1;

    return precision;
}
