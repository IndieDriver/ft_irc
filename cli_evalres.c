/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cli_evalres.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amathias <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/31 12:09:19 by amathias          #+#    #+#             */
/*   Updated: 2017/10/31 16:20:13 by amathias         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bircd.h"

void	print_message(char *msg)
{
	char *start;

	start = ft_strrchr(msg, ':');
	if (start != NULL)
	{
		ft_putstr(start + 1);
	}
}

char	*handle_server_rpl(t_env_client *e, char *msg, char **split, int rpl_code)
{
	(void)e;
	(void)split;
	if (rpl_code == 443)
	{
		//print_message(msg);
	}
	print_message(msg);
	return (NULL);
}

char	*handle_server_command()
{

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
	printf("%s|%s\n", hostname, cmd);
	if (ft_atoi(cmd) != 0)
	{
		handle_server_rpl(e, msg, split, ft_atoi(split[1]));
	}
	else
	{
		handle_server_command();
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
	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
	return (request);
}
