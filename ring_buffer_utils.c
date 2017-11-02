/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ring_buffer_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amathias <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/02 17:21:59 by amathias          #+#    #+#             */
/*   Updated: 2017/11/02 17:38:21 by amathias         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bircd.h"

int				rb_reset(t_ring_buffer *buffer)
{
	size_t i;
	int r;

	r = -1;
	if (buffer)
	{
		buffer->head = 0;
		buffer->tail = 0;
		i = 0;
		while (i < buffer->size)
		{
			ft_bzero(buffer->buffer[i], BUF_SIZE);
			i++;
		}
		r = 0;
	}
	return (r);
}

int				rb_empty(t_ring_buffer *buffer)
{
	return (buffer->head == buffer->tail);
}

int				rb_full(t_ring_buffer *buffer)
{
	return (((buffer->head + 1) % buffer->size) == buffer->tail);
}
