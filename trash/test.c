int		main(int ac, char **av)
{
	int		i = 0;
	printf("________ TEST _________\n");
	while (i < ac)
	{
		printf("%s\n", av[i]);
		i++;
	}
	printf("_______________________\n");
	return (0);
}
