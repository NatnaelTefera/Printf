#include "main.h"

/**
 * handle_print - Prints an argument based on its type
 * @fmt: Formatted string in which to print the arguments.
 * @ind: Pointer to the current index in fmt.
 * @list: List of arguments to be printed.
 * @buffer: Buffer array to handle print.
 * @flags: Calculates active flags.
 * @width: Width specifier.
 * @precision: Precision specification.
 * @size: Size specifier.
 * Return: Number of characters printed or -1 on error.
 */
int handle_print(const char *fmt, int *ind, va_list list, char buffer[],
                 int flags, int width, int precision, int size)
{
    int unknow_len = 0;
    int printed_chars = -1;

    // Define a struct to map format characters to functions
    fmt_t fmt_types[] = {
        {'c', print_char}, {'s', print_string}, {'%', print_percent},
        {'i', print_int}, {'d', print_int}, {'b', print_binary},
        {'u', print_unsigned}, {'o', print_octal}, {'x', print_hexadecimal},
        {'X', print_hexa_upper}, {'p', print_pointer}, {'S', print_non_printable},
        {'r', print_reverse}, {'R', print_rot13string}, {'\0', NULL}
    };

    for (int i = 0; fmt_types[i].fmt != '\0'; i++)
    {
        if (fmt[*ind] == fmt_types[i].fmt)
        {
            return fmt_types[i].fn(list, buffer, flags, width, precision, size);
        }
    }

    if (fmt[*ind] == '\0')
    {
        return -1; // Handle case where the format string ends unexpectedly
    }

    unknow_len += write(1, "%%", 1);

    if (fmt[*ind - 1] == ' ')
    {
        unknow_len += write(1, " ", 1);
    }
    else if (width)
    {
        (*ind)--;

        // Find the end of the current format specifier
        while (fmt[*ind] != ' ' && fmt[*ind] != '%')
        {
            (*ind)--;
        }

        if (fmt[*ind] == ' ')
        {
            (*ind)--;
        }
        return 1;
    }

    unknow_len += write(1, &fmt[*ind], 1);
    return unknow_len;
}
