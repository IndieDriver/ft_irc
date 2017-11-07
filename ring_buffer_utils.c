/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ring_buffer_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amathias <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/02 17:21:59 by amathias          #+#    #+#             */
/*   Updated: 2017/11/07 21:41:13 by amathias         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bircd.h"

int				rb_contain_message(t_ring_buffer *buffer)
{
	size_t	count;
	char	*ptr;
	size_t	tail;

	count = 0;
	if (buffer && !rb_empty(buffer))
	{
		tail = buffer->tail;
		while (ft_strlen(buffer->buffer[tail]) != 0)
		{
			if (count >= buffer->size)
				return (0);
			ptr = ft_strchr(buffer->buffer[tail], '\n');
			if (ptr != NULL)
				return (1);
			tail = (tail + 1) % buffer->size;
			count++;
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
			ft_strncat(msg, rb_get(buffer), 510 - ft_strlen(msg));
			rb_pop(buffer);
			if (ptr != NULL)
			{
				ft_strncat(msg, "\r\n", 512 - ft_strlen(msg));
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
			ft_bzero(buffer->buffer[i], BUF_SIZE - 1);
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
