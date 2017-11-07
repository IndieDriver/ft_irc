/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amathias <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/03 13:56:39 by amathias          #+#    #+#             */
/*   Updated: 2017/11/07 21:09:52 by amathias         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bircd.h"

char	*server_cmd_privmsg(t_env *e, t_server_response *response,
			t_server_command server_cmd)
{
	char *rpl;
	char *fci;

	(void)server_cmd;
	if (!(rpl = malloc(sizeof(char) * 512)))
		return (NULL);
	rpl[0] = '\0';
	fci = user_to_prefix(&response->fd->user);
	ft_strncat(rpl, fci, 510 - ft_strlen(rpl));
	free(fci);
	ft_strncat(rpl, " ", 510 - ft_strlen(rpl));
	ft_strncat(rpl, response->raw_msg, 510 - ft_strlen(rpl));
	ft_strncat(rpl, "\r\n", 512 - ft_strlen(rpl));
	broadcast_msg(e, response->split[1], rpl, response->fd->user.nick);
	free(rpl);
	return (NULL);
}

char	*server_cmd_join(t_env *e, t_server_response *response,
			t_server_command server_cmd)
{
	char	*rpl;
	char	*fci;

	(void)server_cmd;
	if (!(rpl = malloc(sizeof(char) * 512)))
		return (NULL);
	rpl[0] = '\0';
	fci = user_to_prefix(&response->fd->user);
	ft_strncat(rpl, fci, 510 - ft_strlen(rpl));
	free(fci);
	ft_strncat(rpl, " ", 510 - ft_strlen(rpl));
	ft_strncat(rpl, response->raw_msg, 510 - ft_strlen(rpl));
	ft_strncat(rpl, "\r\n", 512 - ft_strlen(rpl));
	add_channel(&e->serv->channels, response->split[1]);
	add_user_to_channel(&e->serv->channels,
			get_user(e->serv, response->fd->user.nick),
			response->split[1]);
	broadcast_msg_channel(e,
			get_chan(e->serv->channels, response->split[1]), rpl,
			response->fd->user.nick);
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
	if (!(rpl = malloc(sizeof(char) * 512)))
		return (NULL);
	rpl[0] = '\0';
	fci = user_to_prefix(&response->fd->user);
	ft_strncat(rpl, fci, 510 - ft_strlen(rpl));
	free(fci);
	ft_strncat(rpl, " ", 510 - ft_strlen(rpl));
	ft_strncat(rpl, response->raw_msg, 510 - ft_strlen(rpl));
	ft_strncat(rpl, "\r\n", 512 - ft_strlen(rpl));
	chan = get_chan(e->serv->channels, response->split[1]);
	broadcast_msg_channel(e, chan, rpl, response->fd->user.nick);
	remove_user_from_channel(e->serv->channels,
			get_user(e->serv, response->fd->user.nick),
			response->split[1]);
	free(rpl);
	return (NULL);
}
