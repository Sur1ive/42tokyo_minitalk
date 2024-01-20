/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yxu <yxu@student.42tokyo.jp>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 17:16:21 by yxu               #+#    #+#             */
/*   Updated: 2024/01/20 23:01:04 by yxu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minitalk.h"

void	parse_byte(int signum)
{
	// char	c[24];

	if (signum == SIGUSR1)
		ft_printf("0");
	if (signum == SIGUSR2)
		ft_printf("1");
}

int	main(void)
{
	ft_printf("Server start\nPID: %d\n", getpid());
	signal(SIGUSR1, parse_byte);
	signal(SIGUSR2, parse_byte);
	while (1)
		;
	return (0);
}
