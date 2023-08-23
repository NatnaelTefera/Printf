#include "main.h"

/**
 * get_width - Extracts the width specifier from a format string
 * @format: Formatted string in which to find the width specifier.
 * @i: Pointer to the current position in the format string.
 * @list: Variable argument list.
 *
 * Return: Extracted width specifier.
 */
int get_width(const char *format, int *i, va_list list)
{
    int curr_i = *i + 1; // Start parsing one character ahead
    int width = 0;

    while (format[curr_i] != '\0') {
        if (isdigit(format[curr_i])) {
            width = width * 10 + (format[curr_i] - '0');
            curr_i++;
        } else if (format[curr_i] == '*') {
            curr_i++;
            width = va_arg(list, int);
            break; // Found width specifier, exit loop
        } else {
            break; // Reached the end of the width specifier
        }
    }

    *i = curr_i - 1; // Update the current position
    return width;
}
