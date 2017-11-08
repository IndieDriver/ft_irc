/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   irc_reply.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amathias <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/30 15:56:55 by amathias          #+#    #+#             */
/*   Updated: 2017/11/08 10:05:24 by amathias         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include "bircd.h"

char	*rpl_welcome(t_env *e, t_fd *fd, t_user *user)
{
	char *rpl;
	char *fci;

	(void)e;
	if (!(rpl = malloc(sizeof(char) * 510)))
		return (NULL);
	rpl[0] = '\0';
	ft_strncat(rpl, ":", 510 - ft_strlen(rpl));
	ft_strncat(rpl, "127.0.0.1 ", 510 - ft_strlen(rpl));
	ft_strncat(rpl, "001 ", 510 - ft_strlen(rpl));
	ft_strncat(rpl, user->nick, 510 - ft_strlen(rpl));
	ft_strncat(rpl, " :Welcome on IRC ", 510 - ft_strlen(rpl));
	fci = user_to_prefix(user);
	ft_strncat(rpl, fci, 510 - ft_strlen(rpl));
	free(fci);
	ft_strncat(rpl, "\r\n", 512 - ft_strlen(rpl));
	append_msg_client(e, rpl, fd->user.socket);
	free(rpl);
	return (NULL);
}

char	*rpl_nickinuse(t_env *e, t_fd *fd, char *nick)
{
	char *rpl;

	(void)e;
	if (!(rpl = malloc(sizeof(char) * 510)))
		return (NULL);
	rpl[0] = '\0';
	ft_strncat(rpl, ":", 510 - ft_strlen(rpl));
	ft_strncat(rpl, "127.0.0.1 ", 510 - ft_strlen(rpl));
	ft_strncat(rpl, "443 * ", 510 - ft_strlen(rpl));
	ft_strncat(rpl, nick, 510 - ft_strlen(rpl));
	ft_strncat(rpl, " :Nickname is already in use, /nick <username>",
			510 - ft_strlen(rpl));
	ft_strncat(rpl, "\r\n", 512 - ft_strlen(rpl));
	append_msg_client(e, rpl, fd->user.socket);
	free(rpl);
	return (NULL);
}
