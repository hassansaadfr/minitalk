#include "server.h"

static char	*ft_strjoin(char *str, char c)
{
	int		i;
	int		size;
	char	*out;

	i = 0;
	size = ft_strlen(str);
	out = (char *)malloc(sizeof(char) * (size + 2));
	if (out == NULL)
		print_err("Malloc error");
	while (str && str[i])
	{
		out[i] = str[i];
		i++;
	}
	if (str)
		free(str);
	out[i] = c;
	i++;
	out[i] = '\0';
	return (out);
}

static void	send_sig(int signal, int pid)
{
	int	ret;

	if (signal == SIGUSR1 || signal == SIGUSR2)
	{
		ret = kill(pid, signal);
		if (ret == -1)
		{
			if (signal == SIGUSR1)
				print_err("Error on sending resume sig\n");
			else
				print_err("Error on sending end sig\n");
		}
	}
}

static void	write_sig(int byte_received, int pid)
{
	static unsigned char	byte_to_char = 0;
	static int				i = 0;
	static char				*buff = NULL;

	byte_to_char |= (byte_received << i++);
	if (i > 7)
	{
		if (byte_to_char == '\0')
		{
			write(1, buff, ft_strlen(buff));
			write(1, "\n", 1);
			free(buff);
			buff = NULL;
			send_sig(pid, SIGUSR2);
		}
		else
		{
			buff = ft_strjoin(buff, byte_to_char);
			send_sig(pid, SIGUSR1);
		}
		i = 0;
		byte_to_char = 0;
	}
	else
		send_sig(pid, SIGUSR1);
}

static void	sig_handler(int signal, siginfo_t *info, void *context)
{
	(void)context;
	if (signal == SIGUSR1)
		write_sig(0, info->si_pid);
	else if (signal == SIGUSR2)
		write_sig(1, info->si_pid);
}

int	main(int argc, char **argv)
{
	struct sigaction	sig;

	(void)argv;
	if (argc > 1)
		print_err("Usage: ./server\n");
	sig.sa_flags = SA_SIGINFO | SA_RESTART;
	sigemptyset(&sig.sa_mask);
	sig.sa_sigaction = sig_handler;
	sigaction(SIGUSR1, &sig, NULL);
	sigaction(SIGUSR2, &sig, NULL);
	write(STDOUT_FILENO, "\t\t\033[1;32mPID : ", 15);
	ft_putnbr(getpid());
	write(STDOUT_FILENO, "\n\033[0m", 5);
	while (1)
		pause();
	return (0);
}
