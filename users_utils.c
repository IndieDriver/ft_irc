/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   users_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amathias <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/26 18:10:37 by amathias          #+#    #+#             */
/*   Updated: 2017/11/07 16:43:31 by amathias         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bircd.h"

void	rename_user_in_list(t_user **users, char *old_nick, char *new_nick)
{
	t_user *tmp;

	tmp = *users;
	if (tmp == NULL)
		return ;
	while (tmp)
	{
		if (ft_strcmp(tmp->nick, old_nick) == 0)
		{
			tmp->nick = new_nick;
		}
		tmp = tmp->next;
	}
}

void	rename_user(t_env *e, char *old_nick, char *new_nick)
{
	t_chan	*chan;

	chan = e->serv->channels;
	while (chan)
	{
		rename_user_in_list(&chan->users, old_nick, new_nick);
		chan = chan->next;
	}
	rename_user_in_list(&e->serv->users, old_nick, new_nick);
}

char	*get_users_string(t_chan *chan)
{
	t_user	*user;
	char	*msg;

	msg = ft_strnew(BUF_SIZE);
	user = chan->users;
	if (user && msg)
	{
		ft_strncat(msg, ":", BUF_SIZE - ft_strlen(msg));
		ft_strncat(msg, chan->name, BUF_SIZE - ft_strlen(msg));
		ft_strncat(msg, " ", BUF_SIZE - ft_strlen(msg));
		while (user)
		{
			if (user != chan->users)
				ft_strncat(msg, ", ", BUF_SIZE - ft_strlen(msg));
			ft_strncat(msg, user->nick, BUF_SIZE - ft_strlen(msg));
			user = user->next;
		}
	}
	return (msg);
}

void	clear_userlist(t_user **users)
{
	t_user *current;
	t_user *next;

	current = *users;
	while (current)
	{
		next = current->next;
		free(current);
		current = next;
	}
	*users = NULL;
}

void	free_user(t_user *user)
{
	if (user)
	{
		free(user->nick);
		free(user->hostname);
		free(user);
	}
}
