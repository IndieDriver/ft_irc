/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cli_evalcmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amathias <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/25 11:12:30 by amathias          #+#    #+#             */
/*   Updated: 2017/10/26 10:10:57 by amathias         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "bircd.h"

/*
	/connect <machine> [port]
	/nick <nickname>
	/join <#chan>
	/leave [#channel]
	/who
	/msg <nick> <message>
*/

typedef enum {
	RPL_NONE = 0,
	RPL_WELCOME = 1
}		e_ircmd;

char	*get_prvmsg(char *to, const char *content)
{
	char *msg;

	msg = malloc(sizeof(char) * 512);
	msg[0] = '\0';
	ft_strncat(msg, "PRIVMSG ", 512);
	ft_strncat(msg, to, 512);
	ft_strncat(msg, " :", 512);
	ft_strncat(msg, content, 512);
	ft_strncat(msg, "\r\n", 512);
	return (msg);
}

char	*cmd_msg(char **split)
{
	int i;
	char msg[512];

	msg[0] = '\0';
	if (split[1] == NULL)
	{
		ft_putendl_fd("Invalid usage: /msg <nick> <message>", 2);
		return (NULL);
	}
	i = 2;
	while (split[i])
	{
		if (i != 2)
			ft_strncat(msg, " ", 512);
		ft_strncat(msg, split[i], 512);
		i++;
	}
	return (get_prvmsg(split[1], msg));
}

char	*cmd_connect(t_env_client *e, char **split)
{
	if (split[1] == NULL)
	{
		ft_putendl_fd("Invalid usage: /connect <machine> [port]", 2);
		return (NULL);
	}
	e->port = split[2] != NULL ? ft_atoi(split[2]) : 6697;
	cli_create(e, split[1], e->port);
	return (NULL);
}

char	*cmd_nick(char **split)
{
	char *msg;

	if (split[1] == NULL)
	{
		ft_putendl_fd("Invalid usage: /nick <nickname>", 2);
		return (NULL);
	}
	msg = malloc (sizeof(char) * 512);
	msg[0] = '\0';
	ft_strncat(msg, "NICK ", 512);
	ft_strncat(msg, split[1], 512);
	ft_strncat(msg, "\r\n", 512);
	return (msg);
}

char	*cmd_join(char **split)
{
	char *msg;

	if (split[1] == NULL)
	{
		ft_putendl_fd("Invalid usage: /join <chan>", 2);
		return (NULL);
	}
	msg = malloc (sizeof(char) * 512);
	msg[0] = '\0';
	ft_strncat(msg, "JOIN ", 512);
	ft_strncat(msg, split[1], 512);
	ft_strncat(msg, "\r\n", 512);
	return (msg);
}

char	*cmd_leave(char **split)
{
	char *msg;

	if (split[1] == NULL)
	{
		ft_putendl_fd("Invalid usage: /leave <chan>", 2);
		return (NULL);
	}
	msg = malloc (sizeof(char) * 512);
	msg[0] = '\0';
	ft_strncat(msg, "PART ", 512);
	ft_strncat(msg, split[1], 512);
	ft_strncat(msg, "\r\n", 512);
	return (msg);
}

char	*cmd_who(char **split)
{
	char *msg;

	msg = malloc (sizeof(char) * 512);
	msg[0] = '\0';
	ft_strncat(msg, "USERS", 512);
	ft_strncat(msg, split[1], 512);
	ft_strncat(msg, "\r\n", 512);
	return (msg);
}

char	*get_command(t_env_client *e, char **split)
{
	char *tmp;

	tmp = NULL;
	if (ft_strstr(split[0], "/connect"))
		tmp = cmd_connect(e, split);
	else if (ft_strstr(split[0], "/nick"))
		tmp = cmd_nick(split);
	else if (ft_strstr(split[0], "/join"))
		tmp = cmd_join(split);
	else if (ft_strstr(split[0], "/leave"))
		tmp = cmd_leave(split);
	else if (ft_strstr(split[0], "/who"))
		tmp = cmd_who(split);
	else if (ft_strstr(split[0], "/msg"))
		tmp = cmd_msg(split);
	else
		ft_putendl_fd("Unrecognized command", 2);

	return (tmp);
}

char	*get_request(t_env_client *e, char *cmd)
{
	int i;
	char **split = ft_strsplit(cmd, ' ');

	if (split != NULL)
	{
		if (split[0][0] == '/')
			cmd = get_command(e, split);
		else
			cmd = get_prvmsg("#chan", cmd);
	}
	if (cmd == NULL)
		cmd = "";
	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free (split);
	return cmd;
}
