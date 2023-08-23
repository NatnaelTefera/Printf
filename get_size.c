#include "main.h"

/**
 * get_size - Calculates the size based on format specifiers
 * @format: Formatted string in which to check for format specifiers
 * @i: Pointer to the current index in the format string
 *
 * Return: Size of the data type (S_LONG, S_SHORT, or 0)
 */
int get_size(const char *format, int *i) {
    int curr_i = *i + 1;
    int size = 0;

    // Check for 'l' (long) specifier
    if (format[curr_i] == 'l') {
        size = S_LONG;
    }
    // Check for 'h' (short) specifier
    else if (format[curr_i] == 'h') {
        size = S_SHORT;
    }

    // Update the index pointer based on whether a specifier was found
    *i = (size != 0) ? curr_i : curr_i - 1;

    return size;
}
