#include <unistd.h>

void	ft_putchar_fd(char c, int fd)
{
	unsigned char d;

	d = (unsigned char)c;
	write(fd, &c, 1);
}
