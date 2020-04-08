#include "libft.h"

size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	unsigned int i;
	unsigned int j;

	i = 0;
	j = 0;
	if (src == NULL)
		return (0);
	j = ft_strlen((char *)src);
	while (src[i] && i + 1 < size)
	{
		dest[i] = src[i];
		i++;
	}
	if (size != 0)
		dest[i] = '\0';
	if (src[i])
	{
		while (src[i])
			i++;
		return (i);
	}
	return (j);
}
