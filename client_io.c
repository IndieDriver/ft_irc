/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_io.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amathias <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/30 15:22:09 by amathias          #+#    #+#             */
/*   Updated: 2017/10/30 17:49:19 by amathias         ###   ########.fr       */
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
	printf("[%d] message received: %s", e->server_soc, e->server_fd->buf_read);
	if (r <= 0)
	{
		close(e->server_soc);
		clean_fd(e->server_fd);
		printf("server #%d gone away\n", e->server_soc);
	}
}

void	write_to_server(t_env_client *e, char *buffer)
{
	X(-1, send(e->server_soc, buffer, BUF_SIZE, 0), "send");
}

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
		if (e->connected && cmd)
		{
			e->server_fd->fct_write(e, cmd);
			free(cmd);
		}
	}
	else if (e->connected && FD_ISSET(e->server_soc, &e->fd_read))
	{
		e->server_fd->fct_read(e);
	}
}
