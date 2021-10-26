#include "client.h"
#include "utils.h"
#include <stdio.h>

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
		// usleep(1000);
		if (kill(pid, SIGUSR1 + (byte * 2)) == -1)
			print_err("Signal error.");
		pause();
	}
}
void	sig_handler(int signal)
{
	if (signal == SIGUSR2)
		exit(1);
}

int	main(int argc, char **argv)
{
	int					pid;
	struct sigaction	sig;

	sig.sa_flags = SA_RESTART;
	sig.sa_handler = sig_handler;
	sigaction(SIGUSR1, &sig, NULL);
	sigaction(SIGUSR2, &sig, NULL);
	// signal(SIGUSR1, sig_handler);
	// signal(SIGUSR2, sig_handler);
	if (argc != 3)
		print_err("Usage: ./client PID \"Message to send to the server");
	pid = get_process_pid(argv[1]);
	usleep(1000);
	while (*argv[2])
		send_char(pid, *argv[2]++);
	send_char(pid, 0);
	return (0);
}
