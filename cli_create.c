/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cli_create.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amathias <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/25 11:23:21 by amathias          #+#    #+#             */
/*   Updated: 2017/10/25 11:54:17 by amathias         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include <netinet/in.h>
#include "bircd.h"

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
}
