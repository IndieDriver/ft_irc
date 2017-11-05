/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_client.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amathias <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/25 11:24:14 by amathias          #+#    #+#             */
/*   Updated: 2017/11/05 13:59:23 by amathias         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bircd.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/resource.h>

void	clean_fd(t_fd *fd)
{
	fd->type = FD_FREE;
	fd->fct_read = NULL;
	fd->fct_write = NULL;
	if (fd->user.nick != NULL)
		free(fd->user.nick);
	if (fd->user.hostname != NULL)
		free(fd->user.hostname);
	fd->user.hostname = NULL;
	fd->user.nick = NULL;
	fd->user.socket = -1;
	fd->has_login = 0;
	rb_reset(&fd->rbuffer_write);
	rb_reset(&fd->rbuffer_read);
}

void	init_fds(t_fd *fd)
{
	fd->type = FD_FREE;
	fd->fct_read = NULL;
	fd->fct_write = NULL;
	fd->user.hostname = NULL;
	fd->user.nick = NULL;
	fd->user.hostname = NULL;
	fd->user.socket = -1;
	fd->has_login = 0;
	rb_reset(&fd->rbuffer_write);
	rb_reset(&fd->rbuffer_read);
}

void	init_env_client(t_env_client *e)
{
	e->max = 0;
	e->connected = 0;
	rb_init(&e->stdin_fd.rbuffer_write, 10);
	rb_init(&e->stdin_fd.rbuffer_read, 10);
	rb_init(&e->server_fd.rbuffer_write, 10);
	rb_init(&e->server_fd.rbuffer_read, 10);
	init_fds(&e->stdin_fd);
	init_fds(&e->server_fd);
	e->running = 1;
}

int		main(int ac, char **av)
{
	t_env_client	e;
	char			*hostname;

	init_env_client(&e);
	hostname = get_opt_client(&e, ac, av);
	cli_create(&e, hostname, e.port);
	while (e.running)
	{
		init_fd_client(&e);
		e.r = select(e.max + 1, &e.fd_read, &e.fd_write, NULL, NULL);
		X(-1, e.r, "select");
		check_fd_client(&e);
	}
	free(hostname);
	return (0);
}
