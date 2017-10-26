/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amathias <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/26 14:57:11 by amathias          #+#    #+#             */
/*   Updated: 2017/10/26 18:08:33 by amathias         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bircd.h"

int		is_nick_free(t_env *e, char *nick)
{
	int i;

	i = 0;
	while (i < MAX_USER)
	{
		if ((nick != NULL && e->serv->users[i].nick != NULL)
				&& ft_strcmp(e->serv->users[i].nick, nick) == 0)
			return (0);
	}
	return (1);
}

void	connect_user(t_env *e, char *nick, char *user, char *hostname)
{
	int i;

	if (is_nick_free(e, nick))
	{
		ft_putendl_fd("nick already in use", 2);
		//TODO: send rep nick in use
	}
	i = 0;
	while (i < MAX_USER)
	{
		if (e->serv->users[i].nick == NULL)
		{
			e->serv->users[i].nick = nick;
			e->serv->users[i].user = user;
			e->serv->users[i].hostname = hostname;
		}
		i++;
	}
}

