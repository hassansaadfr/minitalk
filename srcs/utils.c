/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsaadaou <hsaadaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 16:06:22 by hsaadaou          #+#    #+#             */
/*   Updated: 2021/10/26 16:06:25 by hsaadaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

static void	ft_bzero(void *s, size_t n)
{
	size_t	i;
	char	*temp;

	temp = (char *)s;
	i = 0;
	while (i < n)
	{
		temp[i] = '\0';
		i++;
	}
}

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*alloc;

	alloc = malloc(size * nmemb);
	if (alloc == NULL)
		return (NULL);
	ft_bzero(alloc, size * nmemb);
	return (alloc);
}

void	print_err(char *str)
{
	int	size;

	size = 0;
	while (str[size])
		size++;
	write(1, str, size);
	write(1, "\n", 1);
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
		write(1, &c, 1);
	}
}

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
		i++;
	return (i);
}
