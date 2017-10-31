/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_io.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amathias <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/30 15:21:46 by amathias          #+#    #+#             */
/*   Updated: 2017/10/31 12:03:59 by amathias         ###   ########.fr       */
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

	ft_bzero(e->fds[cs].buf_read, BUF_SIZE);
	r = recv(cs, e->fds[cs].buf_read, BUF_SIZE, 0);
	if (r <= 0)
	{
		remove_user(e->serv, e->fds[cs].nick);
		close(cs);
		clean_fd(&e->fds[cs]);
		printf("client #%d gone away\n", cs);
	}
	else
	{
		printf("bytes received: %d\n", r);
		printf("[%d] message received: %s", cs, e->fds[cs].buf_read);
		response = server_evalmsg(e, &e->fds[cs]);
		if (response != NULL)
		{
			printf("response: %s\n", response);
			broadcast_msg_server(e, response);
			free(response);
		}
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

int	get_client_fd(t_env *e, char *nick)
{
	int i;

	i = 0;
	while (i < e->maxfd)
	{
		if (e->fds[i].type == FD_CLIENT
				&& e->fds[i].nick != NULL
				&& ft_strcmp(e->fds[i].nick, nick) == 0)
			return (i);
		i++;
	}
	return (-1);
}
