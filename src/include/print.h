#ifndef _PRINT_H_
# define _PRINT_H_

# include <stdint.h>
# include <stdio.h>

# ifndef BITS_IN_BYTE
#  define BITS_IN_BYTE 8
# endif

void	print_memory(uint8_t *ptr, int size);

#endif
