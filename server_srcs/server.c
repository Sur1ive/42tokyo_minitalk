/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yxu <yxu@student.42tokyo.jp>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 17:16:21 by yxu               #+#    #+#             */
/*   Updated: 2024/01/27 01:46:41 by yxu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minitalk.h"

static void	exit_with_msg(int exitcode, char *msg)
{
	ft_printf("%s\n", msg);
	exit(exitcode);
}

static int	byte_of_utf8(unsigned char c)
{
	unsigned char	first4bit;

	first4bit = (c >> 4) & 0b00001111;
	if (first4bit <= 0b0111)
		return (1);
	else if (first4bit >= 0b1100 && first4bit <= 0b1101)
		return (2);
	else if (first4bit == 0b1110)
		return (3);
	else if (first4bit == 0b1111)
		return (4);
	else
	{
		ft_printf("Error while decoding.\n");
		exit(0);
	}
}

static void	parse_package(char package[32])
{
	int		checkbyte;
	int		i;
	int		kill_flag;

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
		kill_flag = kill(((int *)package)[0], SIGUSR2);
	}
	else
		ft_printf("An error occured when receiving message. \
Here are some possible reasons:\n\
1: More than one clients were sending message at the same time.\n\
2: Bad status...\n");
	if (kill_flag != 0)
		exit_with_msg(0, "something wrong with sending success signal\n");
}

static void	deal_signal(int signum)
{
	static char	package[32] = {0};
	static int	count = 0;
	int			bit;

	if (signum == SIGUSR1)
		bit = 0;
	else if (signum == SIGUSR2)
		bit = 1;
	if (bit == 0)
		package[count / 8] = (package[count / 8] >> 1) & 0b01111111;
	else if (bit == 1)
		package[count / 8] = (package[count / 8] >> 1) | 0b10000000;
	count++;
	if (count == 256)
	{
		count = 0;
		parse_package(package);
	}
}

int	main(void)
{
	ft_printf("Server start\nPID: %d\n", getpid());
	signal(SIGUSR1, deal_signal);
	signal(SIGUSR2, deal_signal);
	while (1)
		;
	return (0);
}
