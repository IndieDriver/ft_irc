/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   users.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amathias <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/26 17:46:00 by amathias          #+#    #+#             */
/*   Updated: 2017/10/26 18:07:59 by amathias         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bircd.h"

void	add_user_to_list(t_user **users, t_user *user)
{
	if (*users)
	{
		user->next = *users;
		*users = user;
	}
}

t_user	*new_user(char *nick, char *username, char *hostname)
{
	t_user *user;

	if ((user = malloc(sizeof(t_user))) == NULL)
		return (NULL);
	user->nick = nick;
	user->user = username;
	user->hostname = hostname;
	user->next = NULL;
	return (user);
}
