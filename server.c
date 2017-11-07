/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amathias <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/26 14:57:11 by amathias          #+#    #+#             */
/*   Updated: 2017/11/07 12:44:02 by amathias         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bircd.h"

int		is_nick_free(t_user *users, char *nick)
{
	t_user *tmp_user;

	tmp_user = users;
	if (nick == NULL)
		return (0);
	while (tmp_user)
	{
		if (ft_strcmp(tmp_user->nick, nick) == 0)
			return (0);
		tmp_user = tmp_user->next;
	}
	return (1);
}

void	add_user(t_serv *serv, t_user *user)
{
	if (user == NULL)
		return ;
	if (is_nick_free(serv->users, user->nick))
	{
		add_user_to_list(&serv->users, copy_user(user));
	}
	else
	{
		fprintf(stderr, "nick already in use\n");
	}
}

void	remove_user(t_serv *serv, char *nick)
{
	t_chan *tmp_chan;
	t_user *user;

	user = get_user(serv, nick);
	if (user == NULL)
	{
		fprintf(stderr, "No user named %s on server\n", nick);
		return ;
	}
	tmp_chan = serv->channels;
	while (tmp_chan)
	{
		remove_user_from_channel(serv->channels, user, tmp_chan->name);
		tmp_chan = tmp_chan->next;
	}
	remove_user_from_list(&serv->users, user->nick);
}

void	clear_server(t_env *e)
{
	clear_userlist(&e->serv->users);
	clear_channellist(&e->serv->channels);
	free(&e->serv);
}
