/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_evalmsg.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amathias <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/26 10:21:47 by amathias          #+#    #+#             */
/*   Updated: 2017/10/31 14:25:46 by amathias         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "bircd.h"

char 	*server_cmd_user(t_env *e, t_fd *fd, t_server_command server_cmd,
			char **split)
{
	t_user user;

	fd->user = ft_strdup(split[1]);
	user.nick = fd->nick;
	user.hostname = fd->hostname;
	user.user = fd->user;
	(void)server_cmd;
	if (user.nick != NULL)
	{
		add_user(e->serv, user.nick, user.user, user.hostname);
		return (rpl_welcome(e, &user));
	}
	return (NULL);
}

char 	*server_cmd_nick(t_env *e, t_fd *fd, t_server_command server_cmd,
			char **split)
{
	t_user user;

	fd->nick = ft_strdup(split[1]);
	user.nick = fd->nick;
	user.hostname = fd->hostname;
	user.user = fd->user;
	(void)server_cmd;
	if (is_nick_free(e->serv->users, split[1]))
	{
		if (user.user != NULL)
		{
			add_user(e->serv, user.nick, user.user, user.hostname);
			return (rpl_welcome(e, &user));
		}
		else
			return (NULL);
	}
	else
		return (rpl_nickinuse(e, &user));
	return (NULL);
}

char	*handle_command_msg(t_env *e, t_fd *fd, t_server_command server_cmd,
			char **split)
{
	(void)fd;
	(void)split;
	if (ft_strcmp(server_cmd.irc_cmd, "NICK") == 0)
		return (server_cmd_nick(e, fd, server_cmd, split));
	else if (ft_strcmp(server_cmd.irc_cmd, "USER") == 0)
		return (server_cmd_user(e, fd, server_cmd, split));

	return (NULL);
}

char	*handle_server_command(t_env *e, t_fd *fd, char *msg, char **split)
{
	char				*tmp;
	int					command_index;
	t_server_command	server_cmd;

	(void)msg;
	(void)e;
	tmp = NULL;
	command_index = get_server_command_index(split[0]);
	if (command_index == -1)
	{
		ft_putendl_fd("Unrecognized command\n", 2);
		return (NULL);
	}
	server_cmd = g_server_commands[command_index];
	if (is_valid_server_command(server_cmd, split))
		tmp = handle_command_msg(e, fd, server_cmd, split);
	else
		ft_putendl_fd("Invalid usage", 2);
	return (tmp);
}

char	*server_evalmsg(t_env *e, t_fd *fd)
{
	char	*res;
	char	**split;
	int		i;

	res = NULL;
	split = ft_strsplit(fd->buf_read, ' ');
	if (split != NULL)
	{
		res = handle_server_command(e, fd, fd->buf_read, split);
	}
	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
	return (res);
}
