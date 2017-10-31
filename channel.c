/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   channel.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amathias <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/26 17:26:21 by amathias          #+#    #+#             */
/*   Updated: 2017/10/31 17:05:02 by amathias         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bircd.h"

void		add_channel(t_chan **channels, char *name)
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
	chan->next = *channels;
	*channels = chan;
}

void		remove_channel(t_chan **channels, char *name)
{
	t_chan	*tmp;
	t_chan	*prev;

	tmp = *channels;
	if (tmp != NULL && ft_strcmp(tmp->name, name) == 0)
	{
		*channels = tmp->next;
		clear_userlist(&tmp->users);
		free(tmp);
		return ;
	}
	while (tmp != NULL && ft_strcmp(tmp->name, name) == 0)
	{
		prev = tmp;
		tmp = tmp->next;
	}
	if (tmp == NULL)
		return ;
	prev->next = tmp->next;
	clear_userlist(&tmp->users);
	free(tmp);
}

t_chan		*get_chan(t_chan *channels, char *name)
{
	t_chan	*list;
	int		i;

	i = 0;
	list = channels;
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

void		add_user_to_channel(t_chan **channels, t_user *user,
				char *chan_name)
{
	t_chan *chan;

	chan = get_chan(*channels, chan_name);
	if (chan == NULL)
	{
		add_channel(channels, chan_name);
		chan = get_chan(*channels, chan_name);
	}
	add_user_to_list(&chan->users, copy_user(user));
}

void		remove_user_from_channel(t_chan *channels, t_user *user,
			char *chan_name)
{
	t_chan *chan;

	chan = get_chan(channels, chan_name);
	if (chan != NULL)
	{
		remove_user_from_list(&chan->users, user->nick);
	}
	//add_user_to_list(&chan->users, user);
}
