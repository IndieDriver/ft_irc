/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_read.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amathias <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/25 11:24:51 by amathias          #+#    #+#             */
/*   Updated: 2017/10/25 11:49:31 by amathias         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include "bircd.h"

void	read_from_server(t_env_client *e)
{
	int r;

	r = recv(e->server_soc, e->server_fd->buf_read, BUF_SIZE, 0);
	if (r <= 0)
	{
		close(e->server_soc);
		clean_fd(e->server_fd);
		printf("server #%d gone away\n", e->server_soc);
	}
}

void	read_from_client(t_env *e, int cs)
{
	int	r;
	int	i;

	r = recv(cs, e->fds[cs].buf_read, BUF_SIZE, 0);
	printf("message received: %s", e->fds[cs].buf_read);
	if (r <= 0)
	{
		close(cs);
		clean_fd(&e->fds[cs]);
		printf("client #%d gone away\n", cs);
	}
	else
	{
		i = 0;
		while (i < e->maxfd)
		{
			if ((e->fds[i].type == FD_CLIENT) &&
					(i != cs))
				send(i, e->fds[cs].buf_read, r, 0);
			i++;
		}
	}
}
