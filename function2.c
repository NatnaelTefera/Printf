#include "main.h"

int print_pointer(va_list types, char buffer[], int flags, int width, int precision, int size) {
    unsigned long num_addrs = (unsigned long)va_arg(types, void *);
    if (num_addrs == 0)
        return write(1, "NULL", 4);
    
    char map_to[] = "0123456789abcdef";
    char padd = (flags & F_ZERO && !(flags & F_MINUS)) ? '0' : ' ';
    char extra_c = (flags & F_PLUS) ? '+' : ((flags & F_SPACE) ? ' ' : 0);
    int length = 2; // For '0x'
    int ind = BUFF_SIZE - 2;
    
    while (num_addrs > 0) {
        buffer[ind--] = map_to[num_addrs % 16];
        num_addrs /= 16;
        length++;
    }
    
    return write_pointer(buffer, ind + 1, length, width, flags, padd, extra_c, 1);
}

int print_non_printable(va_list types, char buffer[], int flags, int width, int precision, int size) {
    char *str = va_arg(types, char *);
    if (str == NULL)
        return write(1, "(null)", 6);
    
    int i = 0, offset = 0;
    
    while (str[i] != '\0') {
        if (is_printable(str[i]))
            buffer[i + offset] = str[i];
        else
            offset += append_hexa_code(str[i], buffer, i + offset);
        i++;
    }
    
    buffer[i + offset] = '\0';
    return write(1, buffer, i + offset);
}

int print_reverse(va_list types, char buffer[], int flags, int width, int precision, int size) {
    char *str = va_arg(types, char *);
    if (str == NULL)
        str = ")Null(";
    
    int count = 0;
    
    for (int i = 0; str[i]; i++)
        count++;
    
    for (int i = count - 1; i >= 0; i--)
        write(1, &str[i], 1);
    
    return count;
}

int print_rot13string(va_list types, char buffer[], int flags, int width, int precision, int size) {
    char *str = va_arg(types, char *);
    if (str == NULL)
        str = "(AHYY)";
    
    char in[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
    char out[] = "NOPQRSTUVWXYZABCDEFGHIJKLMnopqrstuvwxyzabcdefghijklm";
    int count = 0;
    
    for (unsigned int i = 0; str[i]; i++) {
        char x = str[i];
        for (unsigned int j = 0; in[j]; j++) {
            if (in[j] == str[i]) {
                x = out[j];
                break;
            }
        }
        write(1, &x, 1);
        count++;
    }
    
    return count;
}
