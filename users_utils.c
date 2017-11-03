/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   users_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amathias <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/26 18:10:37 by amathias          #+#    #+#             */
/*   Updated: 2017/11/03 14:43:38 by amathias         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bircd.h"

char	*get_users_string(t_chan *chan)
{
	t_user	*user;
	char	*msg;

	msg = ft_strnew(BUF_SIZE);
	user = chan->users;
	if (user && msg)
	{
		ft_strncat(msg, ":", BUF_SIZE);
		ft_strncat(msg, chan->name, BUF_SIZE);
		ft_strncat(msg, " ", BUF_SIZE);
		while (user)
		{
			if (user != chan->users)
				ft_strncat(msg, ", ", BUF_SIZE);
			ft_strncat(msg, user->nick, BUF_SIZE);
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

void	print_userlist(t_user *begin)
{
	t_user	*list;

	list = begin;
	if (list)
	{
		while (list)
		{
			printf("%s|%s|%s\n", list->nick, list->user, list->hostname);
			list = list->next;
		}
	}
}

void	free_user(t_user *user)
{
	free(user->nick);
	free(user->user);
	free(user->hostname);
	free(user);
}
