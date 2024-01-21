/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yxu <yxu@student.42tokyo.jp>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 17:16:21 by yxu               #+#    #+#             */
/*   Updated: 2024/01/22 00:59:43 by yxu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minitalk.h"

static int	byte_of_utf8(unsigned char c)
{
	unsigned char first4bit;

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

static int	is_end_of_msg(int byte_of_c, unsigned char *c)
{
	if (byte_of_c == 4)
		if (c[0] == 0xFF || c[1] == 0xFF || c[2] == 0xFF || c[3] == 0xFF)
			return (1);
	return (0);
}

static void	parse_byte(int signum)
{
	static unsigned char	c[4] = {0};
	static int	count = 0;
	static int	byte_of_c = 1;
	int			bit;

	if (signum == SIGUSR1)
		bit = 0;
	else if (signum == SIGUSR2)
		bit = 1;
	if (bit == 0)
		c[count / 8] = (c[count / 8] >> 1) & 0b01111111;
	else if (bit == 1)
		c[count / 8] = (c[count / 8] >> 1) | 0b10000000;
	count++;
	if (count == 8)
		byte_of_c = byte_of_utf8(c[0]);
	if (count == byte_of_c * 8)
	{
		if (is_end_of_msg(byte_of_c, c))
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
