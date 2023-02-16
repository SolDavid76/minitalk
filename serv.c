/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   serv.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djanusz <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 11:43:39 by djanusz           #+#    #+#             */
/*   Updated: 2023/02/16 17:02:28 by djanusz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

char	*msg;

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (i);
	while (str[i])
		i++;
	return (i);
}

char	*ft_recalloc(char *str, int size, int cpy)
{
	char	*res;
	int		i;

	res = malloc(sizeof(char) * (size + 1));
	if (!res)
	{
		free(str);
		exit(1);
	}
	i = 0;
	while (str[i] && cpy)
	{
		res[i] = str[i];
		i++;
	}
	while (i < size)
		res[i++] = 0;
	return (free(str), res);
}

void	handler(int signal)
{
	static int	res = 0;
	static int	i = 0;
	static int	n = 7;

	res += (signal == SIGUSR1) << n--;
	if (n == -1)
	{
		if (i % BUFFER_SIZE == 0)
			msg = ft_recalloc(msg, i + BUFFER_SIZE, 1);
		msg[i] = res;
		if (res == '\0')
		{
			write(1, msg, ft_strlen(msg));
			msg = ft_recalloc(msg, i + BUFFER_SIZE, 0);
			i = 0;
		}
		else
			i++;
		res = 0;
		n = 7;
	}
}

int	main(void)
{
	msg = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!msg)
		return (1);
	msg[BUFFER_SIZE] = '\0';
	printf("PID : %i\n", getpid());
	signal(SIGUSR1, handler);
	signal(SIGUSR2, handler);
	while (1);
}
