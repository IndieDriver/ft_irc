/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_client.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amathias <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/25 11:24:14 by amathias          #+#    #+#             */
/*   Updated: 2017/10/31 16:14:44 by amathias         ###   ########.fr       */
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
	/*
	if (fd->nick != NULL)
		free(fd->nick);
	if (fd->hostname != NULL)
		free(fd->hostname);
	if (fd->user != NULL)
		free(fd->user); */
	fd->hostname = NULL;
	fd->nick = NULL;
	fd->user = NULL;
}

void	init_fds(t_fd *fd)
{
	fd->type = FD_FREE;
	//fd->fct_read = NULL;
	//fd->fct_write = NULL;
	fd->hostname = NULL;
	fd->nick = NULL;
	fd->hostname = NULL;
	fd->user = NULL;
}

void	init_env_client(t_env_client *e)
{
	e->connected = 0;
	//e->stdin_fd = (t_fd*)Xv(NULL, malloc(sizeof(t_fd*)), "malloc");
	//e->server_fd = (t_fd*)Xv(NULL, malloc(sizeof(t_fd*)), "malloc");
	init_fds(&e->stdin_fd);
	init_fds(&e->server_fd);
	e->running = 1;

}

char	*get_opt(t_env_client *e, int ac, char **av)
{
	char *hostname;

	hostname = (ac == 2 || ac == 3) ? ft_strdup(av[1]) : NULL;
	e->port = ac == 3 ? ft_atoi(av[2]) : 6697;
	if (ac > 3)
	{
		fprintf(stderr, CL_USAGE, av[0]);
		exit(1);
	}
	return (hostname);
}

int		main(int ac, char **av)
{
	t_env_client	e;
	char			*hostname;

	init_env_client(&e);
	hostname = get_opt(&e, ac, av);
	cli_create(&e, hostname, e.port);
	while (e.running)
	{
		init_fd_client(&e);
		e.r = select(e.max + 1, &e.fd_read, NULL, NULL, NULL);
		check_fd_client(&e);
	}
	free(hostname);
	return (0);
}
