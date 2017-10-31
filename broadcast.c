/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   broadcast.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amathias <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/31 10:51:31 by amathias          #+#    #+#             */
/*   Updated: 2017/10/31 10:53:43 by amathias         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include "bircd.h"

void	broadcast_msg_channel(t_env *e, t_chan *chan, char *msg)
{
	t_user	*user;
	int		fd;

	user = chan->users;
	while (user)
	{
		fd = get_client_fd(e, user->nick);
		if (fd != -1)
		{
			X(-1, send(fd, msg, BUF_SIZE, 0), "send");
		}
		user = user->next;
	}
}

void	broadcast_msg_users_channel(t_env *e, char *nick, char *msg)
{
	t_chan *chan;

	//chan = get_chan(e->serv->channels)
	chan = e->serv->channels;
	while (chan)
	{
		if (is_user_in_channel(chan, nick))
			broadcast_msg_channel(e, chan, msg);
		chan = chan->next;
	}
}

void	broadcast_msg_server(t_env *e, char *msg)
{
	t_user *user;
	int		fd;

	user = e->serv->users;
	while (user)
	{
		fd = get_client_fd(e, user->nick);
		printf("fd: %d\n", fd);
		if (fd != -1)
		{
			printf("send\n");
			X(-1, send(fd, msg, BUF_SIZE, 0), "send");
			//send(fd, msg, r , 0);
		}
		user = user->next;
	}
}
