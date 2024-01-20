/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yxu <yxu@student.42tokyo.jp>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 18:02:32 by yxu               #+#    #+#             */
/*   Updated: 2024/01/20 22:59:57 by yxu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minitalk.h"

static void	send_byte(pid_t pid, char byte)
{
	int	bit_i;
	int	bit;

	bit_i = 0;
	while (bit_i < BIT_PER_BYTE)
	{
		bit = byte >> bit_i++ & 0b00000001;
		if (bit == 0)
			kill(pid, SIGUSR1);
		if (bit == 1)
			kill(pid, SIGUSR2);
		usleep(1000);
	}
}

static void	send_end_of_msg(pid_t pid)
{
	send_byte(pid, 0xFF);
	send_byte(pid, 0xFF);
	send_byte(pid, 0xFF);
	send_byte(pid, 0xFF);
}

int	main(int argc, char **argv)
{
	pid_t	pid;
	int		char_i;

	if (argc != 3)
		exit(0);
	pid = ft_atoi(argv[1]);
	char_i = 0;
	while (argv[2][char_i])
		send_byte(pid, argv[2][char_i++]);
	send_end_of_msg(pid);
	return (0);
}
