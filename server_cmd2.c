/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_cmd2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amathias <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/03 14:02:22 by amathias          #+#    #+#             */
/*   Updated: 2017/11/03 14:36:10 by amathias         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bircd.h"

char	*server_cmd_users(t_env *e, t_server_response *response,
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

void	send_who(t_env *e, char *prefix, char *msg, int user_socket)
{
	char *tmp;

	tmp = ft_strnew(BUF_SIZE);
	if (!tmp)
		return ;
	ft_strncpy(tmp, prefix, BUF_SIZE);
	ft_strncat(tmp, msg, BUF_SIZE);
	ft_strncat(tmp, "\r\n", BUF_SIZE);
	append_msg_client(e, tmp, user_socket);
	free(tmp);
}

void	parse_user_chan(t_env *e, char *prefix, t_user *user, int user_socket)
{
	char	*tmp;
	t_chan	*chan;

	chan = e->serv->channels;
	if (chan)
	{
		while (chan)
		{
			if (is_user_in_channel(chan, user->nick))
			{
				tmp = get_users_string(chan);
				if (tmp != NULL)
				{
					send_who(e, prefix, tmp, user_socket);
					free(tmp);
				}
			}
			chan = chan->next;
		}
	}
}

char	*server_cmd_who(t_env *e, t_server_response *response,
			t_server_command server_cmd)
{
	char	*rpl;
	char	*fci;

	(void)server_cmd;
	if (!(rpl = malloc(sizeof(char) * 510)))
		return (NULL);
	rpl[0] = '\0';
	fci = user_to_prefix(&response->fd->user);
	ft_strncat(rpl, fci, 510);
	free(fci);
	ft_strncat(rpl, " ", 510);
	ft_strncat(rpl, "\0", 510);
	parse_user_chan(e, rpl, &response->fd->user, response->fd->user.socket);
	free(rpl);
	return (NULL);
}
