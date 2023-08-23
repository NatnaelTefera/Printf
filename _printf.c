#include "main.h"

/**
 * _printf - Printf function
 * @format: format.
 * Return: Printed chars.
 */
int _printf(const char *format, ...)
{
    if (!format)
        return -1;

    va_list args;
    va_start(args, format);

    char buffer[BUFF_SIZE];
    int buff_ind = 0, printed_chars = 0, printed = 0;
    
    for (int i = 0; format[i]; i++)
    {
        if (format[i] != '%')
        {
            buffer[buff_ind++] = format[i];
            if (buff_ind == BUFF_SIZE || !format[i + 1])
            {
                write(1, buffer, buff_ind);
                buff_ind = 0;
            }
            printed_chars++;
        }
        else
        {
            int flags, width, precision, size;
            flags = get_flags(format, &i);
            width = get_width(format, &i, args);
            precision = get_precision(format, &i, args);
            size = get_size(format, &i);
            i++;

            printed = handle_print(format, &i, args, buffer,
                                   flags, width, precision, size);

            if (printed == -1)
            {
                va_end(args);
                return -1;
            }

            printed_chars += printed;
        }
    }

    va_end(args);

    return printed_chars;
}
