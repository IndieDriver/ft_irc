/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cli_create.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amathias <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/25 11:23:21 by amathias          #+#    #+#             */
/*   Updated: 2017/10/26 14:31:26 by amathias         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include <netinet/in.h>
#include "bircd.h"
#include <unistd.h>

void	init_client(t_env_client *e, int client_socket)
{
	e->server_soc = client_socket;
	e->server_fd->type = FD_SERV;
	e->server_fd->fct_read = read_from_server;
	e->server_fd->fct_write = write_to_server;
	e->stdin_fd->type = FD_SERV;
	e->stdin_fd->fct_read = read_from_server;
	e->stdin_fd->fct_write = write_to_server;
	e->connected = 1;
}

void	register_connection(t_env_client *e)
{
	char *cmd;
	char request[512];
	char login[256];

	getlogin_r(login, 256);
	ft_memset(request, '\0', 512);
	ft_strncat(request, "/nick ", 512);
	ft_strncat(request, login, 512);
	cmd = get_request(e, request);
	e->server_fd->fct_write(e, cmd);
	free(cmd);

	ft_bzero(request, 512);
	ft_memset(request, '\0', 512);
	ft_strncat(request, "/user ", 512);
	ft_strncat(request, login, 512);
	ft_strncat(request, " * * default user", 512);
	printf("request: %s\n", request);
	cmd = get_request(e, request);
	e->server_fd->fct_write(e, cmd);
	free(cmd);
}

void	cli_create(t_env_client *e, const char *addr, int port)
{
	int					s;
	struct sockaddr_in	sin;
	struct protoent		*pe;
	struct hostent		*hostinfo;

	if (addr == NULL)
		return ;
	pe = (struct protoent*)Xv(NULL, getprotobyname("tcp"), "getprotobyname");
	s = X(-1, socket(PF_INET, SOCK_STREAM, pe->p_proto), "socket");
	hostinfo = gethostbyname(addr);
	if (hostinfo == NULL)
	{
		printf("Unknown host %s\n", addr);
		return ;
	}
	sin.sin_family = AF_INET;
	sin.sin_addr = *(struct in_addr*)hostinfo->h_addr;
	sin.sin_port = htons(port);
	X(-1, connect(s, (const struct sockaddr*)&sin, sizeof(struct sockaddr_in)),
			"connect");
	init_client(e, s);
	register_connection(e);
}
