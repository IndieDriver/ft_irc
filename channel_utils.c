/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   channel_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amathias <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/30 11:31:28 by amathias          #+#    #+#             */
/*   Updated: 2017/11/07 11:27:43 by amathias         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bircd.h"

int			is_channel_name_valid(char *chan_name)
{
	char *tmp;

	tmp = ft_strchr(chan_name, '#');
	if (chan_name != NULL && tmp == chan_name)
		return (1);
	return (0);
}

int			is_channel_name_free(t_chan *channels, char *chan_name)
{
	t_chan	*tmp_chan;

	tmp_chan = channels;
	if (chan_name == NULL)
		return (0);
	while (tmp_chan)
	{
		if (ft_strcmp(tmp_chan->name, chan_name) == 0)
			return (0);
		tmp_chan = tmp_chan->next;
	}
	return (1);
}

void		clear_channellist(t_chan **channels)
{
	t_chan	*current;
	t_chan	*next;

	current = *channels;
	while (current)
	{
		next = current->next;
		clear_userlist(&current->users);
		free(current);
		current = next;
	}
	*channels = NULL;
}

int			is_user_in_channel(t_chan *chan, char *nick)
{
	t_user	*list;

	if (chan == NULL)
		return (0);
	list = chan->users;
	if (list)
	{
		while (list)
		{
			if (ft_strcmp(list->nick, nick) == 0)
				return (1);
			list = list->next;
		}
	}
	return (0);
}
