#include "client.h"

void	print_err(char *str)
{
	int	size;

	size = 0;
	while (str[size])
		size++;
	write(STDERR_FILENO, str, size);
	write(STDERR_FILENO, "\n", 1);
	exit(1);
}

int	get_process_pid(char *pid)
{
	int	pid_nb;
	int	i;

	i = 0;
	pid_nb = 0;
	while (pid[i])
	{
		if (pid[i] >= '0' && pid[i] <= '9')
			i++;
		else
			print_err("Invalid PID");
	}
	while (*pid)
		pid_nb = (pid_nb * 10) + *pid++ - '0';
	return (pid_nb);
}

void	send_char(int pid, char c)
{
	char		i;
	int			byte;

	i = 0;
	while (i < 8)
	{
		byte = (c >> i++) & 1;
		if (byte == 0)
			if (kill(pid, SIGUSR1) == -1)
				print_err("SIGUSR1 error.\n");
		if (byte == 1)
			if (kill(pid, SIGUSR2) == -1)
				print_err("SIGUSR2 error.\n");
	}
}

void	sig_handler(int signal)
{
	(void)signal;
	if (signal == SIGUSR2)
		exit(1);
}

int	main(int argc, char **argv)
{
	int					pid;
	struct sigaction	sig;

	sig.sa_handler = sig_handler;
	sigaction(SIGUSR1, &sig, NULL);
	sigaction(SIGUSR2, &sig, NULL);
	if (argc != 3)
		print_err("Usage: ./client PID \"Message to send to the server");
	pid = get_process_pid(argv[1]);
	while (*argv[2])
		send_char(pid, *argv[2]++);
	send_char(pid, 0);
	return (0);
}
