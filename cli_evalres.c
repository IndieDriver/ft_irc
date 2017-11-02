/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cli_evalres.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amathias <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/31 12:09:19 by amathias          #+#    #+#             */
/*   Updated: 2017/11/02 14:58:51 by amathias         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bircd.h"

void	print_message(char **split, char *msg, t_user *user)
{
	char *start;

	start = ft_strrchr(msg, ':');
	if (start != NULL && user->nick != NULL)
	{
		if (split[2] && split[2][0] == '#')
		{
			ft_putstr("[");
			ft_putstr(split[2]);
			ft_putstr("] ");
		}
		ft_putstr(user->nick);
		ft_putstr(": ");
		ft_putstr(start + 1);
	}
}

char	*handle_server_rpl(t_env_client *e, char *msg, char **split, int rpl_code)
{
	char *start;
	(void)e;
	(void)split;
	(void)rpl_code;

	start = ft_strrchr(msg, ':');
	if (start != NULL)
	{
		if (split[1])
		ft_putstr(start + 1);
	}
	return (NULL);
}

char	*handle_server_command(t_env_client *e, char *msg, char **split)
{
	t_user *user;

	(void)e;
	(void)msg;
	user = prefix_to_user(split[0]);
	print_message(split, msg, user);
	//printf("%s|%s|%s\n", user->nick, user->user, user->hostname);
	return (NULL);
}

char	*handle_response(t_env_client *e, char *msg, char **split)
{
	char				*hostname;
	char				*cmd;
	char				*tmp;

	tmp = NULL;
	hostname = split[0] + 1;
	cmd = split[1];
	if (ft_atoi(cmd) != 0)
	{
		handle_server_rpl(e, msg, split, ft_atoi(split[1]));
	}
	else
	{
		handle_server_command(e, msg, split);
	}
	return (tmp);
}

char	*client_evalmsg(t_env_client *e, char *cmd)
{
	char	**split;
	int		i;
	char	*request;

	if (cmd == NULL)
		return (NULL);
	request = NULL;
	split = ft_strsplit(cmd, ' ');
	if (split == NULL)
		return (NULL);
	if (split[0][0] == ':')
		request = handle_response(e, cmd, split);
	else
		request = handle_server_command(e, cmd, split);
	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
	return (request);
}
