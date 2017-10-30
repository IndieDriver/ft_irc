/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   channel_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amathias <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/30 11:31:28 by amathias          #+#    #+#             */
/*   Updated: 2017/10/30 12:37:22 by amathias         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bircd.h"

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

void	print_channellist(t_chan *begin)
{
	t_chan	*list;

	list = begin;
	if (list)
	{
		while (list)
		{
			printf("Channel %s:\n", list->name);
			print_userlist(list->users);
			printf("\n");
			list = list->next;
		}
	}
}
