/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   serv.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djanusz <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 11:43:39 by djanusz           #+#    #+#             */
/*   Updated: 2023/02/15 16:51:25 by djanusz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	handler(int	signal)
{
	if (signal == 10)
		write(1, "1", 1);
	else if (signal == 12)
		write(1, "0", 1);
}

int	main(void)
{
	printf("PID : %i\n", getpid());
	signal(SIGUSR1, handler);
	signal(SIGUSR2, handler);
	while (1);
}
