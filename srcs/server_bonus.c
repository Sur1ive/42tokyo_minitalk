/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yxu <yxu@student.42tokyo.jp>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 17:16:21 by yxu               #+#    #+#             */
/*   Updated: 2024/01/29 21:28:59 by yxu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minitalk_bonus.h"

/*                    32byte-package                         */
/*  [ PID bytes(4B) | message bytes(24B) | check bytes(4B)]  */
/*     client PID    6 utf8 char 1char/4B     sum of 28B     */

static void	parse_package(char package[32])
{
	int		checkbyte;
	int		i;

	i = 0;
	checkbyte = 0;
	while (i < 28)
		checkbyte += package[i++];
	if (((int *)package)[7] == checkbyte)
	{
		i = 0;
		while (i < 6)
		{
			write(1, &package[4 + 4 * i], byte_of_utf8(package[4 + 4 * i]));
			i++;
		}
	}
	else
	{
		usleep(100);
		kill(((int *)package)[0], SIGUSR1);
		exit_with_msg(0, "Package verification failed. Possible reasons:\n\
1: More than one clients were sending message at the same time.\n\
2: Error during data transfer due to system state.\n");
	}
}

static void	deal_signal(int signum)
{
	static char	package[32] = {0};
	static int	count = 0;
	int			bit;
	int			kill_flag;

	bit = signum - SIGUSR1;
	if (bit == 0)
		package[count / 8] = (package[count / 8] >> 1) & 0b01111111;
	else
		package[count / 8] = (package[count / 8] >> 1) | 0b10000000;
	count++;
	if (count == 256)
	{
		count = 0;
		parse_package(package);
		usleep(100);
		kill_flag = kill(((int *)package)[0], SIGUSR2);
		if (kill_flag != 0)
			exit_with_msg(0, "Failed to send success signal.\n");
	}
}

int	main(void)
{
	ft_printf("Server start\nPID: %d\n", getpid());
	set_signal(deal_signal);
	while (1)
		pause();
	return (0);
}
