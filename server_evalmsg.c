/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_evalmsg.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amathias <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/26 10:21:47 by amathias          #+#    #+#             */
/*   Updated: 2017/11/02 12:58:25 by amathias         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "bircd.h"

char 	*server_cmd_user(t_env *e, t_server_response *response, t_server_command server_cmd)
{
	(void)server_cmd;
	response->fd->user.user = ft_strdup(response->split[1]);
	if (response->fd->user.nick != NULL && is_nick_free(e->serv->users, response->fd->user.nick))
	{
		add_user(e->serv, copy_user(&response->fd->user));
		response->fd->has_login = 1;
		return (rpl_welcome(e, response->fd, &response->fd->user));
	}
	return (NULL);
}

char 	*server_cmd_nick(t_env *e, t_server_response *response, t_server_command server_cmd)
{
	(void)server_cmd;
	response->fd->user.nick = ft_strdup(response->split[1]);
	if (is_nick_free(e->serv->users, response->split[1]))
	{
		if (response->fd->user.user != NULL)
		{
			add_user(e->serv, copy_user(&response->fd->user));
			response->fd->has_login = 1;
			return (rpl_welcome(e, response->fd, &response->fd->user));
		}
		else
			return (NULL);
	}
	else
		return (rpl_nickinuse(e, response->fd, &response->fd->user));
	return (NULL);
}

char 	*server_cmd_privmsg(t_env *e, t_server_response *response, t_server_command server_cmd)
{
	char *rpl;
	char *fci;

	(void)server_cmd;
	(void)e;
	if (!(rpl = malloc(sizeof(char) * 510)))
		return (NULL);
	rpl[0] = '\0';
	fci = user_to_prefix(&response->fd->user);
	ft_strncat(rpl, fci, 510);
	free (fci);
	ft_strncat(rpl, " ", 510);
	ft_strncat(rpl, response->raw_msg, 510);
	ft_strncat(rpl, "\r\n", 512);
	broadcast_msg(e, response->split[1], rpl);
	free (rpl);
	return (NULL);
}

char 	*server_cmd_join(t_env *e, t_server_response *response,
			t_server_command server_cmd)
{
	char *rpl;
	char *fci;
	t_chan *chan;

	(void)e;
	(void)server_cmd;
	if (!(rpl = malloc(sizeof(char) * 510)))
		return (NULL);
	rpl[0] = '\0';
	fci = user_to_prefix(&response->fd->user);
	ft_strncat(rpl, fci, 510);
	free (fci);
	ft_strncat(rpl, " ", 510);
	ft_strncat(rpl, response->raw_msg, 510);
	ft_strncat(rpl, "\r\n", 512);
	chan = add_channel(&e->serv->channels, response->split[1]);
	broadcast_msg_channel(e, chan, rpl);
	add_user_to_channel(&e->serv->channels,
			get_user(e->serv, response->fd->user.nick),
			response->split[1]);
	free (rpl);
	return (NULL);
}

char 	*server_cmd_part(t_env *e, t_server_response *response,
			t_server_command server_cmd)
{
	char *rpl;
	char *fci;
	t_chan *chan;

	(void)e;
	(void)server_cmd;
	if (!(rpl = malloc(sizeof(char) * 510)))
		return (NULL);
	rpl[0] = '\0';
	fci = user_to_prefix(&response->fd->user);
	ft_strncat(rpl, fci, 510);
	free (fci);
	ft_strncat(rpl, " ", 510);
	ft_strncat(rpl, response->raw_msg, 510);
	ft_strncat(rpl, "\r\n", 512);
	chan = get_chan(e->serv->channels, response->split[1]);
	remove_user_from_channel(e->serv->channels,
			get_user(e->serv, response->fd->user.nick),
			response->split[1]);
	broadcast_msg_channel(e, chan, rpl);
	free (rpl);
	return (NULL);
}

char 	*server_cmd_users(t_env *e, t_server_response *response,
			t_server_command server_cmd)
{
	char *rpl;
	char *fci;
	t_chan *chan;

	(void)e;
	(void)server_cmd;
	if (!(rpl = malloc(sizeof(char) * 510)))
		return (NULL);
	rpl[0] = '\0';
	fci = user_to_prefix(&response->fd->user);
	ft_strncat(rpl, fci, 510);
	free (fci);
	ft_strncat(rpl, " ", 510);
	ft_strncat(rpl, response->raw_msg, 510);
	ft_strncat(rpl, "\r\n", 512);
	chan = get_chan(e->serv->channels, response->split[1]);
	remove_user_from_channel(e->serv->channels,
			get_user(e->serv, response->fd->user.nick),
			response->split[1]);
	broadcast_msg_channel(e, chan, rpl);
	free (rpl);
	return (NULL);
}

char	*handle_command_split(t_env *e, t_server_response *response, t_server_command server_cmd)
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
		return (server_cmd_users(e, response, server_cmd));
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

char	*server_evalmsg(t_env *e, t_fd *fd)
{
	t_server_response	response;
	char				*res;
	int					i;

	res = NULL;
	response.fd = fd;
	if ((response.raw_msg = ft_strstr(fd->buf_read, "\r\n")))
		*response.raw_msg = '\0';
	response.split = ft_strsplit(fd->buf_read, ' ');
	response.raw_msg = fd->buf_read;
	if (response.split != NULL)
	{
		res = handle_server_command(e, &response);
	}
	i = 0;
	while (response.split[i])
	{
		free(response.split[i]);
		i++;
	}
	free(response.split);
	return (res);
}
