#ifndef _READ_H_
# define _READ_H_

#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define READ_BUFF 1000

_Static_assert(READ_BUFF > 0, "READ_BUFF cannot be less than or equal to zero");

ssize_t		read_text(int fd, char **dst);

#endif
