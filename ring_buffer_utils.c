/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ring_buffer_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amathias <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/02 17:21:59 by amathias          #+#    #+#             */
/*   Updated: 2017/11/03 15:11:57 by amathias         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bircd.h"

int				rb_contain_message(t_ring_buffer *buffer)
{
	char	*ptr;
	size_t	tail;

	if (buffer && !rb_empty(buffer))
	{
		tail = buffer->tail;
		while (ft_strlen(buffer->buffer[tail]) != 0)
		{
			ptr = ft_strchr(buffer->buffer[tail], '\n');
			if (ptr != NULL)
				return (1);
			tail = (tail + 1) % buffer->size;
		}
	}
	return (0);
}

char			*rb_get_message(t_ring_buffer *buffer)
{
	char	*msg;
	char	*ptr;

	msg = NULL;
	if (buffer && !rb_empty(buffer))
	{
		if ((msg = ft_strnew(512)) == NULL)
			return (NULL);
		while (ft_strlen(rb_get(buffer)) != 0)
		{
			ptr = ft_strchr(rb_get(buffer), '\n');
			ft_strncat(msg, rb_get(buffer), 510);
			rb_pop(buffer);
			if (ptr != NULL)
			{
				ft_strncat(msg, "\r\n", 512);
				break ;
			}
		}
	}
	return (msg);
}

int				rb_reset(t_ring_buffer *buffer)
{
	size_t	i;
	int		r;

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
	return ((buffer->head == buffer->tail));
}

int				rb_full(t_ring_buffer *buffer)
{
	return (((buffer->head + 1) % buffer->size) == buffer->tail);
}
