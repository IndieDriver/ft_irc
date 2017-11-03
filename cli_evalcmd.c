/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cli_evalcmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amathias <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/25 11:12:30 by amathias          #+#    #+#             */
/*   Updated: 2017/11/03 17:12:59 by amathias         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "bircd.h"

char	*cmd_connect(t_env_client *e, char **split)
{
	if (split[1] == NULL)
	{
		ft_putendl_fd("Invalid usage: /connect <machine> [port]", 2);
		return (NULL);
	}
	if (split[2])
	{
		if (is_valid_port(split[2]))
			e->port = ft_atoi(split[2]);
		else
		{
			ft_putendl_fd("Invalid port", 2);
			e->port = 6697;
		}
	}
	else
		e->port = 6697;
	//e->port = split[2] != NULL ? ft_atoi(split[2]) : 6697;
	cli_create(e, split[1], e->port);
	return (NULL);
}

char	*append_arg(char *msg, enum e_arg_type arg_type, char **split,
			int split_index)
{
	int i;

	if (arg_type == SINGLE || (arg_type == OPTIONAL && split[split_index]))
	{
		ft_strncat(msg, split[split_index], 510);
	}
	else if (arg_type == MULTI)
	{
		i = split_index;
		while (split[i])
		{
			if (i != split_index)
				ft_strncat(msg, " ", 510);
			ft_strncat(msg, split[i], 510);
			i++;
		}
	}
	return (msg);
}

char	*get_command_msg(t_client_command cli_cmd, char **split)
{
	char	*msg;
	int		last_argument;

	last_argument = arg_with_colon(cli_cmd);
	msg = malloc(sizeof(char) * 510);
	msg[0] = '\0';
	ft_strncat(msg, cli_cmd.irc_cmd, 510);
	ft_strncat(msg, " ", 510);
	msg = append_arg(msg, cli_cmd.arg1, split, 1);
	last_argument == 2 ? ft_strncat(msg, " :", 510) : ft_strncat(msg, " ", 510);
	msg = append_arg(msg, cli_cmd.arg2, split, 2);
	last_argument == 3 ? ft_strncat(msg, " :", 510) : ft_strncat(msg, " ", 510);
	msg = append_arg(msg, cli_cmd.arg3, split, 3);
	last_argument == 4 ? ft_strncat(msg, " :", 510) : ft_strncat(msg, " ", 510);
	msg = append_arg(msg, cli_cmd.arg4, split, 4);
	ft_strncat(msg, "\r\n", 512);
	return (msg);
}

char	*handle_client_command(t_env_client *e, char **split)
{
	char				*tmp;
	int					command_index;
	t_client_command	client_cmd;

	tmp = NULL;
	if (ft_strstr(split[0], "/connect"))
		tmp = cmd_connect(e, split);
	else if (ft_strstr(split[0], "/nick") && split[1] != NULL)
		register_connection(e, split[1]);
	else
	{
		command_index = get_client_command_index(split[0]);
		if (command_index == -1)
		{
			ft_putendl_fd("Unrecognized command\n", 2);
			return (NULL);
		}
		client_cmd = g_client_commands[command_index];
		if (is_valid_client_command(client_cmd, split))
			tmp = get_command_msg(client_cmd, split);
		else
			ft_putendl_fd(client_cmd.usage, 2);
	}
	return (tmp);
}

char	*get_request(t_env_client *e, char *cmd)
{
	char	**split;
	int		i;
	char	*request;

	if (cmd == NULL || ft_strlen(cmd) == 0)
		return (NULL);
	request = NULL;
	split = ft_strsplit(cmd, ' ');
	if (split == NULL)
		return (NULL);
	if (split[0][0] == '/')
		request = handle_client_command(e, split);
	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
	return (request);
}
