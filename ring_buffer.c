/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ring_buffer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amathias <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/02 15:46:20 by amathias          #+#    #+#             */
/*   Updated: 2017/11/03 11:38:41 by amathias         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bircd.h"

t_ring_buffer	*rb_init(t_ring_buffer *buffer, size_t size)
{
	size_t i;

	rb_reset(buffer);
	buffer->size = size;
	if ((buffer->buffer = (char**)malloc(sizeof(char*) * size)) == NULL)
		return (NULL);
	i = 0;
	while (i < size)
	{
		if ((buffer->buffer[i] = (char*)malloc(sizeof(char*) * BUF_SIZE + 1))
				== NULL)
			return (NULL);
		i++;
	}
	return (buffer);
}


int				rb_put(t_ring_buffer *buffer, char *data)
{
	int r;

	r = -1;
	if (buffer)
	{
		ft_bzero(buffer->buffer[buffer->head], BUF_SIZE);
		ft_strncpy(buffer->buffer[buffer->head], data, BUF_SIZE);
		//buffer->buffer[buffer->head] = data;
		buffer->head = (buffer->head + 1) % buffer->size;
		if (rb_empty(buffer))
		{
			buffer->tail = (buffer->tail + 1) % buffer->size;
		}
		r = 0;
	}
	return (r);
}

char			*rb_get(t_ring_buffer *buffer)
{
	if (buffer && !rb_empty(buffer))
	{
		return (buffer->buffer[buffer->tail]);
	}
	return (NULL);
}

void			rb_pop(t_ring_buffer *buffer)
{
	size_t old_tail;
	if (buffer && !rb_empty(buffer))
	{
		old_tail = buffer->tail;
		buffer->tail = (buffer->tail + 1) % buffer->size;
		ft_bzero(buffer->buffer[old_tail], BUF_SIZE);
	}
}
