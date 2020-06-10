#include "read.h"
#include <cstring>
#include <string>

ssize_t read_text(int fd, char **dst)
{
	char buf[READ_BUFF];
	char *str = NULL;
	char *tmp;
	ssize_t len = 0;
	ssize_t n;

	while ((n = read(fd, buf, READ_BUFF)) > 0)
	{
		tmp = str;
		str = new char[len + n];
		std::memcpy(str, tmp, len);
		std::memcpy(str + len, buf, n);
		delete tmp;
		len += n;
	}
	if (n < 0)
	{
		delete str;
		return -1;
	}
	*dst = str;
	return len;
}
