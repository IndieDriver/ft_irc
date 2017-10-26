/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   channel.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amathias <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/26 17:26:21 by amathias          #+#    #+#             */
/*   Updated: 2017/10/26 18:00:36 by amathias         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bircd.h"

void	add_channel(t_chan **channels, char *name)
{
	t_chan *chan;

	chan = NULL;
	if ((chan = malloc(sizeof(t_chan))) == NULL)
		return ;
	if (name != NULL)
	{
		chan->name = name;
		chan->users = NULL;
		chan->next = NULL;
	}
	if (*channels)
	{
		chan->next = *channels;
		*channels = chan;
	}
}

t_chan		*get_chan(t_chan *begin, char *name)
{
	t_chan	*list;
	int		i;

	i = 0;
	list = begin;
	if (list)
	{
		while (list)
		{
			if (ft_strcmp(list->name, name) == 0)
				return (list);
			i++;
			list = list->next;
		}
	}
	return (NULL);
}

void	add_user_to_channel(t_env *e, t_user *user, char *chan_name)
{
	t_chan *chan;

	chan = get_chan(e->serv->channels, chan_name);
	if (chan == NULL)
	{
		add_channel(&e->serv->channels, chan_name);
		chan = get_chan(e->serv->channels, chan_name);
	}
	add_user_to_list(&chan->users, user);
}
