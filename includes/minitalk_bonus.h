/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk_bonus.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yxu <yxu@student.42tokyo.jp>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 15:39:58 by yxu               #+#    #+#             */
/*   Updated: 2024/01/29 19:52:35 by yxu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_BONUS_H
# define MINITALK_BONUS_H

# include "../libft/libft.h"
# include <unistd.h>
# include <stdlib.h>
# include <signal.h>

# define BIT_PER_BYTE 8

void	exit_with_msg(int exitcode, char *msg);
int		byte_of_utf8(unsigned char c);

#endif
