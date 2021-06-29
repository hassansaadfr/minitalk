#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <stdio.h>

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

void	ft_putnbr(int n)
{
	int		nb;
	char	c;

	nb = n;
	if (nb >= 10)
	{
		ft_putnbr(n / 10);
		ft_putnbr(n % 10);
	}
	else
	{
		c = '0' + nb;
		write(STDOUT_FILENO, &c, 1);
	}
}

void	write_sig(int byte_received, int pid)
{
	static unsigned char	byte_to_char = 0;
	static int				i = 0;

	byte_to_char |= (byte_received << i++);
	if (i > 7)
	{
		if (byte_to_char == '\0')
		{
			write(STDOUT_FILENO, "\n", 1);
			write(STDOUT_FILENO, &byte_to_char, 1);
			kill(pid, SIGUSR2);
		}
		else
		{
			write(STDOUT_FILENO, &byte_to_char, 1);
			kill(pid, SIGUSR1);
		}
		i = 0;
		byte_to_char = 0;
	}
	else
		kill(pid, SIGUSR1);
}

void	sig_handler(int signal, siginfo_t *info, void *context)
{
	(void)context;
	if (signal == SIGUSR1)
		write_sig(0, info->si_pid);
	if (signal == SIGUSR2)
		write_sig(1, info->si_pid);
}

int	main(int argc, char **argv)
{
	struct sigaction	sig;

	(void)argv;
	if (argc > 1)
		print_err("Usage: ./server\n");
	sig.__sigaction_u.__sa_sigaction = sig_handler;
	sigaction(SIGUSR1, &sig, NULL);
	sigaction(SIGUSR2, &sig, NULL);
	write(STDOUT_FILENO, "\t\t\033[1;32mPID : ", 15);
	ft_putnbr(getpid());
	write(STDOUT_FILENO, "\n\033[0m", 5);
	while (1)
		pause();
	return (0);
}
