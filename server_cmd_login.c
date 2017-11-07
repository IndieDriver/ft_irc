/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_cmd_login.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amathias <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:35:05 by amathias          #+#    #+#             */
/*   Updated: 2017/11/07 09:35:07 by amathias         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bircd.h"

char	*server_cmd_user(t_env *e, t_server_response *response,
			t_server_command server_cmd)
{
	(void)e;
	(void)response;
	(void)server_cmd;
	return (NULL);
}

char	*server_cmd_nick(t_env *e, t_server_response *response,
			t_server_command server_cmd)
{
	char *new_nick;

	(void)server_cmd;
	new_nick = response->split[1];
	if (response == NULL || new_nick == NULL)
		return (NULL);
	if (!is_nick_free(e->serv->users, new_nick))
		return (rpl_nickinuse(e, response->fd, new_nick));
	if (response->fd->user.nick != NULL)
	{
		new_nick = ft_strdup(new_nick);
		rename_user(e, &response->fd->user, new_nick);
		response->fd->user.nick = new_nick;
		return (rpl_welcome(e, response->fd, &response->fd->user));
	}
	else
	{
		response->fd->user.nick = ft_strdup(new_nick);
		add_user(e->serv, copy_user(&response->fd->user));
		response->fd->has_login = 1;
		return (rpl_welcome(e, response->fd, &response->fd->user));
	}
}
