/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   users_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amathias <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/26 18:10:37 by amathias          #+#    #+#             */
/*   Updated: 2017/10/30 14:35:57 by amathias         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bircd.h"

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
