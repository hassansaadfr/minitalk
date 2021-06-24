#include <unistd.h>

int	is_valid_pid(char *pid)
{
	while (*pid)
	{
		if (*pid >= '0' && *pid <= '9')
			pid++;
		else
			return (0);
	}
	return (1);
}

int	ft_atoi(char *pid)
{
	int		out;

	out = 0;
	while (*pid)
		out = (out * 10) + *pid++ - '0';
	return (out);
}

int	main(int argc, char **argv)
{
	int	pid;

	if (argc != 3)
	{
		write(STDERR_FILENO, "Usage: ./server PID \"This is the message\"\n", 42);
		return (1);
	}
	if (is_valid_pid(argv[1]) == 0)
		write(STDERR_FILENO, "Invalid PID\n", 13);
	pid = ft_atoi(argv[1]);
	write(STDOUT_FILENO, "\n", 1);
	return (0);
}
