# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <limits.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <signal.h>
# include <dirent.h>

void        fork2(int tube[2], int tube2[2], char **environ);
void        fork3(int tube[2], char **environ);

int		main(int ac, char **av)
{
	extern  char        **environ;
    int     			tube[2];
	int					tube2[2];
	char	*arg[] = {"/bin/cat", "Makefile", NULL};
	pid_t   pid;
	
    if (pipe(tube) == -1)
        return (1);
	pipe(tube2);
    if ((pid = fork()) == 0)
    {
        close(tube[0]);
        dup2(tube[1], STDOUT_FILENO);
        if (execve("/bin/cat", arg, environ) == -1)
            return (1);
    }
	else
	{
		wait(NULL);
		close(tube[1]);
		dup2(tube[0],STDIN_FILENO);
    	fork2(tube, tube2, environ);
	}
	close(tube[0]);
	close(tube[1]);
	close(tube2[0]);
	close(tube2[1]);
    wait(NULL);
	return (0);
}

void		fork2(int tube[2], int tube2[2], char **environ)
{
	char	*arg[] = {"/usr/bin/grep", "inc", NULL};
	pid_t	pid;

	if ((pid = fork()) == 0)
	{	
		close(tube2[0]);
		dup2(tube2[1],STDOUT_FILENO);
    	if (execve("/usr/bin/grep", arg, environ) == -1)
			return ;
	}
	else
	{
		wait(NULL);
        close(tube2[1]);
        dup2(tube2[0],STDIN_FILENO);
		fork3(tube2, environ);
	}
}

void		fork3(int tube2[2], char **environ)
{
	char	*arg[] = {"/usr/bin/wc", NULL, NULL};
	pid_t   pid;
	char	buff[100];

    if ((pid = fork()) == 0)
    {
        if (execve("/usr/bin/wc", arg, environ) == -1)
            return ;
    }
}
