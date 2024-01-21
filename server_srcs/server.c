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

int	byte_of_utf8(int c)
{
	if (c >= 0 || c <= 0x7F)
		return (1);
	else if (c >= 0xC2 || c <= 0xDF)
		return (2);
	else if (c >= 0xE0 || c <= 0xEF)
		return (3);
	else if (c >= 0xF0 || c <= 0xF4)
		return (4);
	else
	{
		ft_printf("Error while decoding.\n");
		exit(0);
	}
}

int	is_end_of_msg(int c)
{
	if (c == -1)
		return (1);
	else
		return (0);
}

void	parse_byte(int signum)
{
	static char	c[4] = {0};
	static int	count = 0;
	static int	byte_of_c = 1;
	int			bit;

	if (count == 8)
		byte_of_c = byte_of_utf8(c[0]);

	if (signum == SIGUSR1)
		bit = 0;
	if (signum == SIGUSR2)
		bit = 1;
	c[count / 8] = c[count / 8] >> 1 + bit * 0b10000000;
	count++;
	if (count == byte_of_c * 8)
	{
		if (*(int *)c == END_OF_MSG)
			ft_printf("\n");
		else
			write(1, c, byte_of_c);
		count = 0;
	}
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
