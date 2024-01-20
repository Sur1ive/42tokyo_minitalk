/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yxu <yxu@student.42tokyo.jp>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 17:16:21 by yxu               #+#    #+#             */
/*   Updated: 2024/01/20 23:14:36 by yxu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minitalk.h"

void	parse_byte(int signum)
{
	static char	c[4] = {0};
	static int	count = 0;
	int			bit;

	if (signum == SIGUSR1)
		bit = 0;
	if (signum == SIGUSR2)
		bit = 1;
	c[count / 8] += pow(2, count % 8);
	count++;

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
