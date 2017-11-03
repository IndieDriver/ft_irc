/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_io.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amathias <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/30 15:22:09 by amathias          #+#    #+#             */
/*   Updated: 2017/11/03 15:15:22 by amathias         ###   ########.fr       */
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

	response = ft_strnew(BUF_SIZE);
	r = recv(e->server_soc, response, BUF_SIZE, 0);
	rb_put(&e->server_fd.rbuffer_read, response);
	free(response);
	if (r <= 0)
	{
		close(e->server_soc);
		clean_fd(&e->server_fd);
		printf("server #%d gone away\n", e->server_soc);
		e->running = 0;
	}
	else
	{
		printf("[%d] message received: %s", e->server_soc,
				rb_get(&e->server_fd.rbuffer_read));
		response = client_evalmsg(e, rb_get(&e->server_fd.rbuffer_read));
		rb_pop(&e->server_fd.rbuffer_read);
		if (response != NULL)
			free(response);
	}
}

void	write_to_server(t_env_client *e, char *buffer)
{
	printf("[%d] message send: %s", e->server_soc, buffer);
	X(-1, send(e->server_soc, buffer, BUF_SIZE, 0), "send");
	rb_pop(&e->server_fd.rbuffer_write);
}

void	append_msg_server(t_env_client *e, char *msg)
{
	rb_put(&e->server_fd.rbuffer_write, msg);
}

void	check_fd_client(t_env_client *e)
{
	char *cmd;
	char *tmp;

	cmd = NULL;
	if (FD_ISSET(e->server_soc, &e->fd_write))
		e->server_fd.fct_write(e, rb_get(&e->server_fd.rbuffer_write));
	else if (e->connected && FD_ISSET(e->server_soc, &e->fd_read))
		e->server_fd.fct_read(e);
	if (FD_ISSET(STDIN_FILENO, &e->fd_read))
	{
		cmd = ft_strnew(BUF_SIZE);
		fgets(cmd, BUF_SIZE, stdin);
		if ((tmp = ft_strstr(cmd, "\n")))
		{
			*tmp = '\0';
			cmd[BUF_SIZE] = '\0';
		}
		rb_put(&e->stdin_fd.rbuffer_write, cmd);
		free(cmd);
		cmd = get_request(e, rb_get(&e->stdin_fd.rbuffer_write));
		rb_pop(&e->stdin_fd.rbuffer_write);
		if (e->connected && cmd)
		{
			append_msg_server(e, cmd);
			free(cmd);
		}
	}
}
