/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_evalmsg.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amathias <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/26 10:21:47 by amathias          #+#    #+#             */
/*   Updated: 2017/11/07 17:05:20 by amathias         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "bircd.h"

char	*handle_command_split(t_env *e, t_server_response *response,
			t_server_command server_cmd)
{
	if (ft_strcmp(server_cmd.irc_cmd, "NICK") == 0)
		return (server_cmd_nick(e, response, server_cmd));
	else if (ft_strcmp(server_cmd.irc_cmd, "USER") == 0)
		return (server_cmd_user(e, response, server_cmd));
	else if (response->fd->has_login &&
			ft_strcmp(server_cmd.irc_cmd, "PRIVMSG") == 0)
		return (server_cmd_privmsg(e, response, server_cmd));
	else if (response->fd->has_login &&
			ft_strcmp(server_cmd.irc_cmd, "JOIN") == 0)
		return (server_cmd_join(e, response, server_cmd));
	else if (response->fd->has_login &&
			ft_strcmp(server_cmd.irc_cmd, "PART") == 0)
		return (server_cmd_part(e, response, server_cmd));
	else if (response->fd->has_login &&
			ft_strcmp(server_cmd.irc_cmd, "WHO") == 0)
		return (server_cmd_who(e, response, server_cmd));
	return (NULL);
}

char	*handle_server_command(t_env *e, t_server_response *response)
{
	char				*tmp;
	int					command_index;
	t_server_command	server_cmd;

	(void)e;
	tmp = NULL;
	command_index = get_server_command_index(response->split[0]);
	if (command_index == -1)
	{
		ft_putendl_fd("Unrecognized command\n", 2);
		return (NULL);
	}
	server_cmd = g_server_commands[command_index];
	if (is_valid_server_command(server_cmd, response->split))
	{
		tmp = handle_command_split(e, response, server_cmd);
	}
	else
		ft_putendl_fd("Invalid usage", 2);
	return (tmp);
}

char	*server_evalmsg(t_env *e, t_fd *fd, char *msg)
{
	t_server_response	response;
	char				*res;
	int					i;

	res = NULL;
	response.fd = fd;
	if ((response.raw_msg = ft_strstr(msg, "\r\n")))
		*response.raw_msg = '\0';
	response.split = ft_strsplit(msg, ' ');
	if (response.split == NULL)
		return (NULL);
	response.raw_msg = msg;
	res = handle_server_command(e, &response);
	i = 0;
	while (response.split[i])
	{
		free(response.split[i]);
		i++;
	}
	free(response.split);
	return (res);
}
