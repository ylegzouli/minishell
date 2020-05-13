#include <unistd.h>
#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	unsigned int	k;

	if (n < 0)
	{
		ft_putchar_fd('-', fd);
		k = -n;
	}
	else
		k = n;
	if (k >= 10)
		ft_putnbr_fd(k / 10, fd);
	ft_putchar_fd(k % 10 + '0', fd);
}
