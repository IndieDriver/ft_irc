/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_io.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amathias <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/30 15:21:46 by amathias          #+#    #+#             */
/*   Updated: 2017/11/02 19:11:19 by amathias         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include "bircd.h"

/*
int		read_client(t_env *e, int cs)
{
	int r;
	int sum;

	r = recv(cs, e->fds[cs].buf_read, BUF_SIZE, 0);
	if (r <= 0)
		return (-1);
	else if (r < BUF_SIZE)
	{
		sum = r;
		while (sum < BUF_SIZE)
		{
			r = recv(cs, e->fds[cs].buf_read + sum, BUF_SIZE - sum, 0);
			sum += r;
		}
	}
	return (1);
} */

void	read_from_client(t_env *e, int cs)
{
	char	*response;
	int		r;

	response = ft_strnew(BUF_SIZE);
	r = recv(cs, response, BUF_SIZE, 0);
	printf("reponse: %s\n", response);
	rb_put(&e->fds[cs].rbuffer_read, response);
	free(response);
	//r = read_client(e, cs);
	if (r <= 0)
	{
		if (e->fds[cs].has_login)
			remove_user(e->serv, e->fds[cs].user.nick);
		close(cs);
		clean_fd(&e->fds[cs]);
		printf("client #%d gone away\n", cs);
	}
	else
	{
		printf("[%d] message received: %s", cs,
				rb_get(&e->fds[cs].rbuffer_read));
		response = server_evalmsg(e, &e->fds[cs]);
		rb_pop(&e->fds[cs].rbuffer_read);
		if (response != NULL)
		{
			printf("response: %s", response);
			free(response);
		}
	}
}

void	write_to_client(t_env *e, int cs)
{
	//TODO: if not fully send, append to rbuffer
	char *msg;

	msg = rb_get(&e->fds[cs].rbuffer_write);
	printf("[%d] message send: %s", cs, msg);
	X(-1, send(cs, msg, BUF_SIZE, 0), "send");
	rb_pop(&e->fds[cs].rbuffer_write);
}

void	append_msg_client(t_env *e, char *msg, int cs)
{
	if (cs != -1)
		rb_put(&e->fds[cs].rbuffer_write, msg);
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

int	get_client_fd(t_env *e, char *nick)
{
	int i;

	i = 0;
	while (i < e->maxfd)
	{
		if (e->fds[i].type == FD_CLIENT
				&& e->fds[i].user.nick != NULL
				&& ft_strcmp(e->fds[i].user.nick, nick) == 0)
			return (i);
		i++;
	}
	return (-1);
}
