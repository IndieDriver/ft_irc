/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_io.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amathias <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/30 15:21:46 by amathias          #+#    #+#             */
/*   Updated: 2017/11/07 17:02:36 by amathias         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include "bircd.h"

void	read_contain_message(t_env *e, int cs)
{
	char *message;
	char *response;

	message = rb_get_message(&e->fds[cs].rbuffer_read);
	printf("[%d] message received: %s", cs, message);
	response = server_evalmsg(e, &e->fds[cs], message);
	if (message)
		free(message);
	if (response != NULL)
	{
		printf("response: %s", response);
		free(response);
	}
}

void	read_from_client(t_env *e, int cs)
{
	char	*response;
	int		r;

	response = ft_strnew(BUF_SIZE);
	if (response == NULL)
		return ;
	r = recv(cs, response, BUF_SIZE, 0);
	rb_put(&e->fds[cs].rbuffer_read, response);
	free(response);
	if (r <= 0)
	{
		printf("disconnecting %d\n", cs);
		if (e->fds[cs].has_login)
			remove_user(e->serv, e->fds[cs].user.nick);
		close(cs);
		clean_fd(&e->fds[cs]);
		printf("client #%d gone away\n", cs);
	}
	else if (rb_contain_message(&e->fds[cs].rbuffer_read))
	{
		read_contain_message(e, cs);
	}
}

void	write_to_client(t_env *e, int cs)
{
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
		{
			e->fds[i].fct_read(e, i);
			e->r--;
		}
		if (FD_ISSET(i, &e->fd_write))
		{
			e->fds[i].fct_write(e, i);
			e->r--;
		}
		i++;
	}
}
