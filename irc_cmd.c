/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   irc_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amathias <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/26 10:37:45 by amathias          #+#    #+#             */
/*   Updated: 2017/10/26 14:29:53 by amathias         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bircd.h"

const t_client_command g_client_commands[] = {
	{"/msg", "PRIVMSG", SINGLE, MULTI, NONE, NONE, "/msg <nick> <message>"},
	{"/nick", "NICK", SINGLE, NONE, NONE, NONE, "/nick <nickname>"},
	{"/join", "JOIN", SINGLE, NONE, NONE, NONE, "/join <chan>"},
	{"/leave", "PART", SINGLE, NONE, NONE, NONE, "/leave <chan>"},
	{"/who", "USERS", NONE, NONE, NONE, NONE, "/who"},
	{"/user", "USER", SINGLE, SINGLE, SINGLE, MULTI,
		"/user <user> <mode> <unused> <realname>"},

};

int		arg_with_colon(t_client_command cli_cmd)
{
	if (cli_cmd.arg1 == NONE)
		return (0);
	if (cli_cmd.arg2 != NONE && cli_cmd.arg3 == NONE && cli_cmd.arg4 == NONE)
		return (2);
	if (cli_cmd.arg3 != NONE && cli_cmd.arg4 == NONE)
		return (3);
	if (cli_cmd.arg4 != NONE)
		return (4);
	return (0);
}

int		is_valid_command(t_client_command cli_cmd, char **split)
{
	if ((cli_cmd.arg1 != NONE) && !split[1])
		return (0);
	if ((cli_cmd.arg2 != NONE) && !split[2])
		return (0);
	if ((cli_cmd.arg3 != NONE) && !split[3])
		return (0);
	return (1);
}

int	get_client_command_index(char *str)
{
	int i;

	i = 0;
	while (i < 6)
	{
		if (ft_strstr(str, g_client_commands[i].client_cmd))
			return (i);
		i++;
	}
	return (-1);
}
