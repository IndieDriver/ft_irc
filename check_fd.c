/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_fd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amathias <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/25 11:23:47 by amathias          #+#    #+#             */
/*   Updated: 2017/10/26 10:12:18 by amathias         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "bircd.h"

void	check_fd_client(t_env_client *e)
{
	char *cmd;

	if (FD_ISSET(STDIN_FILENO, &e->fd_read))
	{
		fgets(e->stdin_fd->buf_write, BUF_SIZE, stdin);
		if (strstr(e->stdin_fd->buf_write, "\n"))
		{
			e->stdin_fd->buf_write[BUF_SIZE] = '\0';
		}
		cmd = get_request(e, e->stdin_fd->buf_write);
		if (e->connected)
			e->server_fd->fct_write(e, cmd);
		if (ft_strlen(cmd))
			free(cmd);
	}
	else if (e->connected && FD_ISSET(e->server_soc, &e->fd_read))
	{
		e->server_fd->fct_read(e);
	}
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
