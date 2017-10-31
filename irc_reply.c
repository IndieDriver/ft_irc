/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   irc_reply.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amathias <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/30 15:56:55 by amathias          #+#    #+#             */
/*   Updated: 2017/10/31 14:28:05 by amathias         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include "bircd.h"

char	*rpl_welcome(t_env *e, t_user *user)
{
	//:bar.example.com 001 amy :Welcome to the Internet Relay Network borja!borja@polaris.cs.uchicago.edu
	char *rpl;
	char *fci;

	(void)e;
	if (!(rpl = malloc(sizeof(char) * 510)))
		return (NULL);
	rpl[0] = '\0';
	ft_strncat(rpl, ":", 510);
	ft_strncat(rpl, "127.0.0.1 ", 510);
	ft_strncat(rpl, "001 ", 510);
	ft_strncat(rpl, user->nick, 510);
	ft_strncat(rpl, " :Welcome on IRC ", 510);
	fci = user_to_prefix(user);
	ft_strncat(rpl, fci, 510);
	free(fci);
	ft_strncat(rpl, "\r\n", 512);
	write_msg_to_client(rpl, get_client_fd(e, user->nick));
	free(rpl);
	return (NULL);
}

char	*rpl_nickinuse(t_env *e, t_user *user)
{
	char *rpl;

	(void)e;
	if (!(rpl = malloc(sizeof(char) * 510)))
		return (NULL);
	rpl[0] = '\0';
	ft_strncat(rpl, ":", 510);
	ft_strncat(rpl, "127.0.0.1 ", 510);
	ft_strncat(rpl, "443 * ", 510);
	ft_strncat(rpl, user->nick, 510);
	ft_strncat(rpl, " :Nickname is already in use", 510);
	ft_strncat(rpl, "\r\n", 512);
	write_msg_to_client(rpl, get_client_fd(e, user->nick));
	free(rpl);
	return (NULL);
}
