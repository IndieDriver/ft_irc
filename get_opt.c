/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_opt.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amathias <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/03 15:46:00 by amathias          #+#    #+#             */
/*   Updated: 2017/11/03 15:55:23 by amathias         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bircd.h"

int		is_valid_port(char *str)
{
	int tmp;
	int i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	tmp = ft_atoi(str);
	if (tmp < 1 || tmp > 65535)
		return (0);
	return (1);
}

void	get_opt_server(t_env *e, int ac, char **av)
{
	if (ac == 2)
	{
		if (is_valid_port(av[1]))
			e->port = ft_atoi(av[1]);
		else
		{
			ft_putendl_fd("Invalid port", 2);
			exit(1);
		}
	}
	else
		e->port = 6697;
	if (ac > 2)
	{
		ft_putendl_fd(USAGE, 2);
		exit(1);
	}
}

char	*get_opt_client(t_env_client *e, int ac, char **av)
{
	char *hostname;

	hostname = (ac == 2 || ac == 3) ? ft_strdup(av[1]) : NULL;
	if (ac == 3)
	{
		if (is_valid_port(av[2]))
			e->port = ft_atoi(av[2]);
		else
		{
			ft_putendl_fd("Invalid port", 2);
			exit(1);
		}
	}
	else
		e->port = 6697;
	if (ac > 3)
	{
		ft_putendl_fd(CL_USAGE, 2);
		exit(1);
	}
	return (hostname);
}
