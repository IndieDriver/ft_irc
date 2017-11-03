/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amathias <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/03 13:56:39 by amathias          #+#    #+#             */
/*   Updated: 2017/11/03 17:02:48 by amathias         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bircd.h"

char	*server_cmd_user(t_env *e, t_server_response *response,
			t_server_command server_cmd)
{
	(void)server_cmd;
	if (response->fd->user.user != NULL)
	{
		free(response->fd->user.user);
	}
	response->fd->user.user = ft_strdup(response->split[1]);
	if (response->fd->user.nick != NULL
			&& is_nick_free(e->serv->users, response->fd->user.nick))
	{
		add_user(e->serv, copy_user(&response->fd->user));
		response->fd->has_login = 1;
		return (rpl_welcome(e, response->fd, &response->fd->user));
	}
	return (NULL);
}

char	*server_cmd_nick(t_env *e, t_server_response *response,
			t_server_command server_cmd)
{
	(void)server_cmd;
	if (response->fd->user.nick != NULL)
	{
		remove_user(e->serv, response->fd->user.nick);
		free(response->fd->user.nick);
	}
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

char	*server_cmd_privmsg(t_env *e, t_server_response *response,
			t_server_command server_cmd)
{
	char *rpl;
	char *fci;

	(void)server_cmd;
	if (!(rpl = malloc(sizeof(char) * 510)))
		return (NULL);
	rpl[0] = '\0';
	fci = user_to_prefix(&response->fd->user);
	ft_strncat(rpl, fci, 510);
	free(fci);
	ft_strncat(rpl, " ", 510);
	ft_strncat(rpl, response->raw_msg, 510);
	ft_strncat(rpl, "\r\n", 512);
	broadcast_msg(e, response->split[1], rpl);
	free(rpl);
	return (NULL);
}

char	*server_cmd_join(t_env *e, t_server_response *response,
			t_server_command server_cmd)
{
	char	*rpl;
	char	*fci;
	t_chan	*chan;

	(void)server_cmd;
	if (!(rpl = malloc(sizeof(char) * 510)))
		return (NULL);
	rpl[0] = '\0';
	fci = user_to_prefix(&response->fd->user);
	ft_strncat(rpl, fci, 510);
	free(fci);
	ft_strncat(rpl, " ", 510);
	ft_strncat(rpl, response->raw_msg, 510);
	ft_strncat(rpl, "\r\n", 512);
	chan = add_channel(&e->serv->channels, response->split[1]);
	add_user_to_channel(&e->serv->channels,
			get_user(e->serv, response->fd->user.nick),
			response->split[1]);
	broadcast_msg_channel(e, chan, rpl);
	free(rpl);
	return (NULL);
}

char	*server_cmd_part(t_env *e, t_server_response *response,
			t_server_command server_cmd)
{
	char	*rpl;
	char	*fci;
	t_chan	*chan;

	(void)server_cmd;
	if (!(rpl = malloc(sizeof(char) * 510)))
		return (NULL);
	rpl[0] = '\0';
	fci = user_to_prefix(&response->fd->user);
	ft_strncat(rpl, fci, 510);
	free(fci);
	ft_strncat(rpl, " ", 510);
	ft_strncat(rpl, response->raw_msg, 510);
	ft_strncat(rpl, "\r\n", 512);
	chan = get_chan(e->serv->channels, response->split[1]);
	remove_user_from_channel(e->serv->channels,
			get_user(e->serv, response->fd->user.nick),
			response->split[1]);
	broadcast_msg_channel(e, chan, rpl);
	free(rpl);
	return (NULL);
}
