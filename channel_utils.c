/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   channel_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amathias <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/30 11:31:28 by amathias          #+#    #+#             */
/*   Updated: 2017/10/30 11:31:48 by amathias         ###   ########.fr       */
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
