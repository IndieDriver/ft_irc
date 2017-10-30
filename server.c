/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amathias <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/26 14:57:11 by amathias          #+#    #+#             */
/*   Updated: 2017/10/30 11:57:30 by amathias         ###   ########.fr       */
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

void	add_user(t_serv *serv, char *nick, char *username, char *hostname)
{
	t_user *user;

	if (is_nick_free(serv->users, nick))
	{
		ft_putendl_fd("nick already in use", 2);
		//TODO: send rep nick in use
	}
	user = new_user(nick, username, hostname);
	if (user != NULL)
	{
		add_user_to_list(&serv->users, user);
	}
}

void	remove_user(t_serv *serv, char *nick)
{
	t_chan *tmp_chan;
	t_user *user;

	user = get_user(serv->users, nick);
	if (user == NULL)
	{
		ft_putstr_fd("No user named ", 2);
		ft_putstr_fd(nick, 2);
		ft_putendl_fd(" on server", 2);
	}
	tmp_chan = serv->channels;
	while (tmp_chan)
	{
		delete_user_from_channel(serv->channels, user, tmp_chan->name);
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
