/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_fd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amathias <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/25 11:24:02 by amathias          #+#    #+#             */
/*   Updated: 2017/11/03 15:10:48 by amathias         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <sys/select.h>
#include "bircd.h"

void	init_fd_client(t_env_client *e)
{
	FD_ZERO(&e->fd_read);
	FD_ZERO(&e->fd_write);
	FD_SET(STDIN_FILENO, &e->fd_read);
	e->max = MAX(e->max, STDIN_FILENO);
	if (e->connected)
	{
		FD_SET(e->server_soc, &e->fd_read);
		if (!rb_empty(&e->server_fd.rbuffer_write))
		{
			FD_SET(e->server_soc, &e->fd_write);
		}
		e->max = MAX(e->max, e->server_soc);
	}
	else
		e->max = MAX(e->max, STDIN_FILENO);
}

void	init_fd(t_env *e)
{
	int	i;

	i = 0;
	e->max = 0;
	FD_ZERO(&e->fd_read);
	FD_ZERO(&e->fd_write);
	while (i < e->maxfd)
	{
		if (e->fds[i].type != FD_FREE)
		{
			FD_SET(i, &e->fd_read);
			if (!rb_empty(&e->fds[i].rbuffer_write))
			{
				FD_SET(i, &e->fd_write);
			}
			e->max = MAX(e->max, i);
		}
		i++;
	}
}
