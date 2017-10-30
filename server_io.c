/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_io.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amathias <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/30 15:21:46 by amathias          #+#    #+#             */
/*   Updated: 2017/10/30 19:02:54 by amathias         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include "bircd.h"

void	read_from_client(t_env *e, int cs)
{
	char	*response;
	int		r;
	//int		i;

	r = recv(cs, e->fds[cs].buf_read, BUF_SIZE, 0);
	printf("[%d] message received: %s", cs, e->fds[cs].buf_read);
	printf("fd nick: %s\n", e->fds[cs].nick);
	//user = get_user(e->serv, e->fds[cs].nick);
	//printf("user: %s\n", user->nick);
	response = server_evalmsg(e, &e->fds[cs]);
	if (response != NULL)
	{
		printf("response: %s\n", response);
		broadcast_msg_server(e, response);
	}
	if (r <= 0)
	{
		close(cs);
		clean_fd(&e->fds[cs]);
		printf("client #%d gone away\n", cs);
	}
	/*
	else
	{
		i = 0;
		while (i < e->maxfd)
		{
			if ((e->fds[i].type == FD_CLIENT) && (i != cs))
				send(i, e->fds[cs].buf_read, r, 0);
			i++;
		}
	} */
}

int	get_client_fd(t_env *e, char *nick)
{
	int i;

	i = 0;
	while (i < e->maxfd)
	{
		if (e->fds[i].type == FD_CLIENT
				&& e->fds[i].nick != NULL
				&& ft_strcmp(e->fds[i].nick, nick))
			return (i);
	}
	return (-1);
}

void	broadcast_msg_channel(t_env *e, t_chan *chan, char *msg)
{
	t_user	*user;
	int		fd;
	int		r;

	r = ft_strlen(msg);
	user = chan->users;
	while (user)
	{
		fd = get_client_fd(e, user->nick);
		if (fd != -1)
		{
			printf("send\n");
			send(fd, msg, r , 0);
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
	int		r;

	r = ft_strlen(msg);
	user = e->serv->users;
	while (user)
	{
		printf("while (user)\n");
		fd = get_client_fd(e, user->nick);
		if (fd != -1)
		{
			printf("send\n");
			send(fd, msg, r , 0);
		}
		user = user->next;
	}
}

void	write_to_client(t_env *e, int cs)
{
	X(-1, send(cs, e->fds[cs].buf_write, BUF_SIZE, 0), "send");
}

void	check_fd_server(t_env *e)
{
	int	i;

	i = 0;
	while ((i < e->maxfd) && (e->r > 0))
	{
		if (FD_ISSET(i, &e->fd_read))
			e->fds[i].fct_read(e, i);
		if (FD_ISSET(i, &e->fd_write))
			e->fds[i].fct_write(e, i);
		if (FD_ISSET(i, &e->fd_read) ||
				FD_ISSET(i, &e->fd_write))
			e->r--;
		i++;
	}
}

