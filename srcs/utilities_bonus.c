/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yxu <yxu@student.42tokyo.jp>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 17:50:17 by yxu               #+#    #+#             */
/*   Updated: 2024/01/29 21:29:16 by yxu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minitalk_bonus.h"

void	exit_with_msg(int exitcode, char *msg)
{
	ft_printf("\nError:\n%s\n", msg);
	exit(exitcode);
}

int	byte_of_utf8(unsigned char c)
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
		ft_printf("Decoding error.\n");
		exit(0);
	}
}

void	set_signal(void (*f)(int))
{
	struct sigaction	sa;

	sigemptyset(&sa.sa_mask);
	sa.sa_handler = f;
	sa.sa_flags = 0;
	if (sigaction(SIGUSR1, &sa, NULL) == -1)
		exit_with_msg(0, "Failed to set SIGUSR1's behavior");
	if (sigaction(SIGUSR2, &sa, NULL) == -1)
		exit_with_msg(0, "Failed to set SIGUSR2's behavior");
}
