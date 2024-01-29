/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yxu <yxu@student.42tokyo.jp>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 18:02:32 by yxu               #+#    #+#             */
/*   Updated: 2024/01/29 18:33:11 by yxu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minitalk.h"

/*                    32byte-package                         */
/*  [ PID bytes(4B) | message bytes(24B) | check bytes(4B)]  */
/*     client PID    6 utf8 char 1char/4B     sum of 28B     */

static void	send_byte(pid_t pid, char byte)
{
	int	bit_i;
	int	bit;
	int	kill_flag;

	bit_i = 0;
	while (bit_i < BIT_PER_BYTE)
	{
		bit = byte >> bit_i++ & 0b00000001;
		if (bit == 0)
			kill_flag = kill(pid, SIGUSR1);
		if (bit == 1)
			kill_flag = kill(pid, SIGUSR2);
		if (kill_flag != 0)
			exit_with_msg(0, "Failed to send message. \
Please check the state of server and pid\n");
		usleep(50);
	}
}

static void	send_package(pid_t clientpid, pid_t serverpid, char msg[24])
{
	static int	count = 0;
	char		package[32];
	int			checkbyte;
	int			i;

	((int *)package)[0] = clientpid;
	i = 0;
	while (i < 24)
	{
		package[4 + i] = msg[i];
		i++;
	}
	i = 0;
	checkbyte = 0;
	while (i < 28)
		checkbyte += package[i++];
	((int *)package)[7] = checkbyte;
	i = 0;
	while (i < 32)
		send_byte(serverpid, package[i++]);
	ft_printf("package%d sent\n", count++);
	usleep(1500);
}

static char	*get_next_msg(char msg[24], char *input)
{
	int		byte_of_char;
	int		utf8char_i;
	int		byte_i;

	utf8char_i = 0;
	if (input == NULL)
		return (NULL);
	while (*input && utf8char_i < 6)
	{
		byte_of_char = byte_of_utf8(*input);
		byte_i = 0;
		while (byte_i < byte_of_char)
			msg[4 * utf8char_i + byte_i++] = *input++;
		utf8char_i++;
	}
	return (input);
}

static void	deal_signal(int signum)
{
	static int	count = 0;

	(void)signum;
	ft_printf("package%d received correctly\n", count++);
}

int	main(int argc, char **argv)
{
	pid_t	serverpid;
	pid_t	clientpid;
	char	*input;
	char	msg[24];

	if (argc != 3 || ft_strlen(argv[1]) >= 6
		|| argv[1][0] < '0' || argv[1][0] > '9')
		exit_with_msg(0, "Please enter PID and message correctly.\n");
	serverpid = ft_atoi(argv[1]);
	clientpid = getpid();
	signal(SIGUSR2, deal_signal);
	input = argv[2];
	while (*input)
	{
		ft_memset(msg, 0, 24);
		input = get_next_msg(msg, input);
		send_package(clientpid, serverpid, msg);
	}
	ft_memset(msg, 0, 24);
	msg[0] = '\n';
	send_package(clientpid, serverpid, msg);
	return (0);
}
