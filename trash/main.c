#include "minishell.h"

int main()
{
	int i;
	char *line;

	i = 0;
	write(1,"minishell$> ", 12);
	while ((i = get_next_line(0, &line)) > 0)
	{
		printf("%s\n", line);
		free(line);
		write(1,"minishell$> ", 12);
	}
	return (0);
}
