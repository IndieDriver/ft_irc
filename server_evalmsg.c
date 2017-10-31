/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_evalmsg.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amathias <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/26 10:21:47 by amathias          #+#    #+#             */
/*   Updated: 2017/10/31 18:11:03 by amathias         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "bircd.h"

char 	*server_cmd_user(t_env *e, t_fd *fd, t_server_command server_cmd,
			char **split)
{
	fd->user.user = ft_strdup(split[1]);
	(void)server_cmd;
	if (fd->user.nick != NULL && is_nick_free(e->serv->users, fd->user.nick))
	{
		add_user(e->serv, copy_user(&fd->user));
		fd->has_login = 1;
		return (rpl_welcome(e, fd, &fd->user));
	}
	return (NULL);
}

char 	*server_cmd_nick(t_env *e, t_fd *fd, t_server_command server_cmd,
			char **split)
{
	(void)server_cmd;
	fd->user.nick = ft_strdup(split[1]);
	if (is_nick_free(e->serv->users, split[1]))
	{
		if (fd->user.user != NULL)
		{
			add_user(e->serv, copy_user(&fd->user));
			fd->has_login = 1;
			return (rpl_welcome(e, fd, &fd->user));
		}
		else
			return (NULL);
	}
	else
		return (rpl_nickinuse(e, fd, &fd->user));
	return (NULL);
}

char 	*server_cmd_privmsg(t_env *e, t_fd *fd, char *msg)
{
	char *rpl;
	char *fci;

	(void)e;
	if (!(rpl = malloc(sizeof(char) * 510)))
		return (NULL);
	rpl[0] = '\0';
	fci = user_to_prefix(&fd->user);
	ft_strncat(rpl, fci, 510);
	free (fci);
	ft_strncat(rpl, " ", 510);
	ft_strncat(rpl, msg, 510);
	broadcast_msg_server(e, rpl);
	free (rpl);
	return (NULL);
}

char	*handle_command_split(t_env *e, t_fd *fd, t_server_command server_cmd,
			char **split)
{
	if (ft_strcmp(server_cmd.irc_cmd, "NICK") == 0)
		return (server_cmd_nick(e, fd, server_cmd, split));
	else if (ft_strcmp(server_cmd.irc_cmd, "USER") == 0)
		return (server_cmd_user(e, fd, server_cmd, split));
	return (NULL);
}

char	*handle_command_chaining(t_env *e, t_fd *fd,
			t_server_command server_cmd, char *msg)
{
	//For Every command that just need chaining
	if (ft_strcmp(server_cmd.irc_cmd, "PRIVMSG") == 0)
		return (server_cmd_privmsg(e, fd, msg));

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
	{
		tmp = handle_command_split(e, fd, server_cmd, split);
		if (tmp == NULL)
			tmp = handle_command_chaining(e, fd, server_cmd, msg);
	}
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
