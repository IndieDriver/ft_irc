/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   broadcast.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amathias <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/31 10:51:31 by amathias          #+#    #+#             */
/*   Updated: 2017/11/07 21:07:56 by amathias         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include "bircd.h"

void	send_message_to_user(t_env *e, char *user, char *msg)
{
	int fd;

	if (user == NULL)
		return ;
	fd = get_client_fd(e, user);
	if (fd != -1)
	{
		append_msg_client(e, msg, fd);
	}
}

void	broadcast_msg_channel(t_env *e, t_chan *chan, char *msg, char *sender)
{
	t_user	*user;
	int		fd;

	if (chan == NULL || msg == NULL)
		return ;
	if (!is_user_in_channel(chan, sender))
		return ;
	user = chan->users;
	while (user)
	{
		fd = get_client_fd(e, user->nick);
		if (fd != -1)
		{
			append_msg_client(e, msg, fd);
		}
		user = user->next;
	}
}

void	broadcast_msg_users_channel(t_env *e, char *nick, char *msg)
{
	t_chan *chan;

	if (nick == NULL || msg == NULL)
		return ;
	chan = e->serv->channels;
	while (chan)
	{
		if (is_user_in_channel(chan, nick))
			broadcast_msg_channel(e, chan, msg, nick);
		chan = chan->next;
	}
}

void	broadcast_msg_server(t_env *e, char *msg)
{
	t_user	*user;
	int		fd;

	user = e->serv->users;
	while (user)
	{
		fd = get_client_fd(e, user->nick);
		if (fd != -1)
		{
			append_msg_client(e, msg, fd);
		}
		user = user->next;
	}
}

void	broadcast_msg(t_env *e, char *dest, char *msg, char *sender)
{
	char *tmp;

	tmp = ft_strstr(dest, "#");
	if (tmp != NULL && tmp == dest && sender != NULL)
	{
		if (is_user_in_channel(get_chan(e->serv->channels, dest), sender))
		{
			broadcast_msg_channel(e, get_chan(e->serv->channels, dest),
				msg, sender);
		}
	}
	else
	{
		send_message_to_user(e, dest, msg);
	}
}
