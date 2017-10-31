/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   users.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amathias <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/26 17:46:00 by amathias          #+#    #+#             */
/*   Updated: 2017/10/31 17:04:13 by amathias         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bircd.h"

void	add_user_to_list(t_user **users, t_user *user)
{
	user->next = *users;
	*users = user;
}

void	remove_user_from_list(t_user **users, char *nick)
{
	t_user	*tmp;
	t_user	*prev;

	tmp = *users;
	if (tmp != NULL && ft_strcmp(tmp->nick, nick) == 0)
	{
		*users = tmp->next;
		free(tmp);
		return ;
	}
	while (tmp != NULL && ft_strcmp(tmp->nick, nick) == 0)
	{
		prev = tmp;
		tmp = tmp->next;
	}
	if (tmp == NULL)
		return ;
	prev->next = tmp->next;
	free(tmp);
}

t_user	*get_user(t_serv *serv, char *nick)
{
	t_user	*list;
	int		i;

	i = 0;
	list = serv->users;
	if (list)
	{
		while (list)
		{
			if (ft_strcmp(list->nick, nick) == 0)
				return (list);
			i++;
			list = list->next;
		}
	}
	return (NULL);
}

t_user	*new_user(char *nick, char *username, char *hostname, int socket)
{
	t_user *user;

	if ((user = malloc(sizeof(t_user))) == NULL)
		return (NULL);
	user->nick = nick;
	user->user = username;
	user->hostname = hostname;
	user->socket = socket;
	user->next = NULL;
	return (user);
}
t_user	*copy_user(t_user *user)
{
	t_user *newuser;

	if ((newuser = malloc(sizeof(t_user))) == NULL)
		return (NULL);
	newuser->nick = user->nick;
	newuser->user = user->user;
	newuser->hostname = user->hostname;
	newuser->socket = user->socket;
	newuser->next = NULL;
	return (newuser);
}
