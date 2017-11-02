/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_io.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amathias <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/30 15:22:09 by amathias          #+#    #+#             */
/*   Updated: 2017/11/02 15:11:45 by amathias         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include "bircd.h"

void	read_from_server(t_env_client *e)
{
	char	*response;
	int		r;

	response = NULL;
	ft_bzero(e->server_fd.buf_read, BUF_SIZE);
	r = recv(e->server_soc, e->server_fd.buf_read, BUF_SIZE, 0);
	if (r <= 0)
	{
		close(e->server_soc);
		clean_fd(&e->server_fd);
		printf("server #%d gone away\n", e->server_soc);
		e->running = 0;
	}
	else
	{
		printf("[%d] message received: %s", e->server_soc, e->server_fd.buf_read);
		e->stdin_fd.buf_read[BUF_SIZE] = '\0';
		response = client_evalmsg(e, e->server_fd.buf_read);
		if (response != NULL)
		{
			printf("response: %s", response);
			free(response);
		}
	}
}

void	write_to_server(t_env_client *e, char *buffer)
{
	printf("[%d] message send: %s", e->server_soc, buffer);
	X(-1, send(e->server_soc, buffer, BUF_SIZE, 0), "send");
}

void	write_msg_to_server(char *msg, int cs)
{
	printf("[%d] message send: %s", cs, msg);
	X(-1, send(cs, msg, BUF_SIZE, 0), "send");
}

void	check_fd_client(t_env_client *e)
{
	char *cmd;

	cmd = NULL;
	if (e->connected && FD_ISSET(e->server_soc, &e->fd_read))
	{
		e->server_fd.fct_read(e);
	}
	if (FD_ISSET(STDIN_FILENO, &e->fd_read))
	{
		fgets(e->stdin_fd.buf_write, BUF_SIZE, stdin);
		if ((cmd = ft_strstr(e->stdin_fd.buf_write, "\n")))
		{
			*cmd = '\0';
			e->stdin_fd.buf_write[BUF_SIZE] = '\0';
		}
		cmd = get_request(e, e->stdin_fd.buf_write);
		if (e->connected && cmd)
		{
			e->server_fd.fct_write(e, cmd);
			free(cmd);
		}
	}
}
