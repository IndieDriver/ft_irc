/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   users_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amathias <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/26 18:10:37 by amathias          #+#    #+#             */
/*   Updated: 2017/10/26 18:15:44 by amathias         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bircd.h"

t_user	*get_user(t_serv *serv, char *nick)
{
	t_user	*list;

	list = serv->users;
	if (list)
	{
		while (list)
		{
			if (list->nick != NULL && ft_strcmp(list->nick, nick) == 0)
				return (list);
			list = list->next;
		}
	}
	return (NULL);
}
