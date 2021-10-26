/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsaadaou <hsaadaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 16:06:40 by hsaadaou          #+#    #+#             */
/*   Updated: 2021/10/26 16:06:40 by hsaadaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

static void	write_sig(int byte_received, int pid)
{
	static int		bit = 0;
	static int		tmp = 0;

	tmp |= (byte_received << bit);
	if (tmp < 0 || tmp > 255)
	{
		tmp = 0;
		bit = 0;
		write(1, "\nError during communication\n", 29);
		usleep(500);
		kill(pid, SIGUSR2);
	}
	else if (++bit == 8)
	{
		if (tmp == '\0')
			write(1, "\n", 2);
		else
			write(1, &tmp, 1);
		bit = 0;
		tmp = 0;
	}
	usleep(500);
	kill(pid, SIGUSR1);
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
	sigemptyset(&sig.sa_mask);
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
