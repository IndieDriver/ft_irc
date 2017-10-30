/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_evalmsg.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amathias <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/26 10:21:47 by amathias          #+#    #+#             */
/*   Updated: 2017/10/30 15:17:34 by amathias         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "bircd.h"

/*
void	broadcast_msg(t_env *e, char **split)
{
} */

char	*handle_server_command(t_env *e, char *msg, char **split)
{
	char				*tmp;
	int					command_index;
	t_server_command	server_cmd;

	(void)msg;
	(void)e;
	tmp = NULL;
	command_index = get_server_command_index(split[0]);
	if (command_index == -1)
	{
		ft_putendl_fd("Unrecognized command\n", 2);
		return (NULL);
	}
	server_cmd = g_server_commands[command_index];
	/*
	if (is_valid_server_command(server_cmd, split))
		tmp = get_command_msg(server_cmd, split);
	else
		ft_putendl_fd("Invalid usage", 2); */
	return (tmp);
}

void	server_evalmsg(t_env *e, char *msg)
{
	char	**split;
	int		i;

	split = ft_strsplit(msg, ' ');
	if (split != NULL)
	{
		handle_server_command(e, msg, split);
	}
	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}
