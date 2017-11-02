/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_server.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amathias <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/25 11:25:08 by amathias          #+#    #+#             */
/*   Updated: 2017/11/02 17:32:40 by amathias         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bircd.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/resource.h>

void		clean_fd(t_fd *fd)
{
	fd->type = FD_FREE;
	fd->fct_read = NULL;
	fd->fct_write = NULL;
	if (fd->user.nick != NULL)
		free(fd->user.nick);
	if (fd->user.hostname != NULL)
		free(fd->user.hostname);
	if (fd->user.user != NULL)
		free(fd->user.user);
	fd->user.hostname = NULL;
	fd->user.nick = NULL;
	fd->user.user = NULL;
	fd->user.socket = -1;
	fd->has_login = 0;
	rb_reset(&fd->rbuffer_write);
	rb_reset(&fd->rbuffer_read);
}

void		init_env(t_env *e)
{
	int				i;
	struct rlimit	rlp;

	X(-1, getrlimit(RLIMIT_NOFILE, &rlp), "getrlimit");
	e->maxfd = rlp.rlim_cur;
	e->fds = (t_fd*)Xv(NULL, malloc(sizeof(*e->fds) * e->maxfd), "malloc");
	i = 0;
	while (i < e->maxfd)
	{
		rb_init(&e->fds[i].rbuffer_write, 10);
		rb_init(&e->fds[i].rbuffer_read, 10);
		clean_fd(&e->fds[i]);
		i++;
	}
	e->serv = (t_serv*)malloc(sizeof(t_serv*));
	e->serv->channels = NULL;
	e->serv->users = NULL;
	e->hostname = NULL;
}

void		get_opt(t_env *e, int ac, char **av)
{
	e->port = ac == 2 ? ft_atoi(av[2]) : 6697;
	if (ac > 2)
	{
		fprintf(stderr, USAGE, av[0]);
		exit(1);
	}
}

int			main(int ac, char **av)
{
	t_env	e;

	init_env(&e);
	get_opt(&e, ac, av);
	srv_create(&e, e.port);
	while (1)
	{
		init_fd(&e);
		e.r = select(e.max + 1, &e.fd_read, &e.fd_write, NULL, NULL);
		check_fd_server(&e);
	}
	main_loop(&e);
	clear_server(&e);
	return (0);
}
