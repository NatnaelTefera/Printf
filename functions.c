#include "main.h"

int print_char(va_list types, char buffer[], int flags, int width, int precision, int size) {
    return handle_write_char(va_arg(types, int), buffer, flags, width, precision, size);
}

int print_string(va_list types, char buffer[], int flags, int width, int precision, int size) {
    char *str = va_arg(types, char *);
    int length = 0, i;

    if (!str) str = (precision >= 6) ? "      " : "(null)";

    while (str[length]) length++;
    if (precision >= 0 && precision < length) length = precision;

    if (width > length) {
        char fill_char = (flags & F_MINUS) ? ' ' : '0';
        for (i = width - length; i > 0; i--) write(1, &fill_char, 1);
    }

    return write(1, str, length);
}

int print_percent(va_list types, char buffer[], int flags, int width, int precision, int size) {
    UNUSED(types); UNUSED(buffer); UNUSED(flags); UNUSED(width); UNUSED(precision); UNUSED(size);
    return write(1, "%%", 1);
}

int print_int(va_list types, char buffer[], int flags, int width, int precision, int size) {
    int i = BUFF_SIZE - 2;
    int is_negative = 0;
    long int n = convert_size_number(va_arg(types, long int), size);
    unsigned long int num;

    if (n == 0) buffer[i--] = '0';
    buffer[BUFF_SIZE - 1] = '\0';
    num = (unsigned long int)n;

    if (n < 0) {
        num = (unsigned long int)(-n);
        is_negative = 1;
    }

    i++;

    return write_number(is_negative, i, buffer, flags, width, precision, size);
}

int print_binary(va_list types, char buffer[], int flags, int width, int precision, int size) {
    unsigned int n = va_arg(types, unsigned int);
    unsigned int m = 2147483648; // 2^31
    unsigned int a[32];
    int count = 0;

    UNUSED(buffer); UNUSED(flags); UNUSED(width); UNUSED(precision); UNUSED(size);

    a[0] = n / m;

    for (int i = 1; i < 32; i++) {
        m /= 2;
        a[i] = (n / m) % 2;
    }

    for (int i = 0, sum = 0; i < 32; i++) {
        sum += a[i];
        if (sum || i == 31) write(1, &(char){'0' + a[i]}, 1);
    }

    return count;
}
