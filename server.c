#include <unistd.h>
#include <sys/types.h>
#include <signal.h>

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

int	handle_sig(void)
{
	struct sigaction	*act;
	struct sigaction	*old_act;

	if (sigaction(SIGUSR1, act, old_act) == 1)
		return (1);
}

int	main(int argc, char **argv)
{
	int		pid;

	if (argc > 1)
	{
		write(STDERR_FILENO, "Usage: ./server\n", 16);
		return (1);
	}
	pid = getpid();
	ft_putnbr(pid);
	write(STDOUT_FILENO, "\n", 1);
	while (1)
	{
		pause();
	}
	return (0);
}
