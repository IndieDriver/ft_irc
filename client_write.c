/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_write.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amathias <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/25 11:23:07 by amathias          #+#    #+#             */
/*   Updated: 2017/10/25 11:50:47 by amathias         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/socket.h>
#include "bircd.h"

void	write_to_server(t_env_client *e, char *buffer)
{
	X(-1, send(e->server_soc, buffer, BUF_SIZE, 0), "send");
}

void	write_to_client(t_env *e, int cs)
{
	X(-1, send(cs, e->fds[cs].buf_write, BUF_SIZE, 0), "send");
}
