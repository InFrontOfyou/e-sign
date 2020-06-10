#include "print.h"

void print_byte(uint8_t byte)
{
    uint8_t i = (uint8_t)1 << (BITS_IN_BYTE - 1);
    while (i)
    {
        printf((byte & i) ? "1" : "0");
        i >>= 1;
    }
}

void print_memory(uint8_t *ptr, int size)
{
    if (size > 0)
    {
        print_byte(*ptr);
        while (--size)
        {
            printf(" ");
            print_byte(*++ptr);
        }
        printf("\n");
    }
}
