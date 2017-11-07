/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amathias <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:37:19 by amathias          #+#    #+#             */
/*   Updated: 2017/11/07 09:37:58 by amathias         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bircd.h"

int		get_client_fd(t_env *e, char *nick)
{
	int i;

	i = 0;
	while (i < e->maxfd)
	{
		if (e->fds[i].type == FD_CLIENT
				&& e->fds[i].user.nick != NULL
				&& ft_strcmp(e->fds[i].user.nick, nick) == 0)
			return (i);
		i++;
	}
	return (-1);
}

char	*ft_fgets(char *str, int bytes)
{
	int i;
	int r;

	i = 0;
	if (bytes <= 0)
		return (str);
	r = read(STDIN_FILENO, str, BUF_SIZE);
	if (r == -1)
		return (NULL);
	str[r] = '\0';
	i = 0;
	while (str[i] && i < bytes - 1)
	{
		if (str[i++] == '\n')
			break ;
	}
	str[i] = '\0';
	if (i > 0)
		return (str);
	else
		return (NULL);
}
