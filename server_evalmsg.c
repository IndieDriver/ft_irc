/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_evalmsg.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amathias <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/26 10:21:47 by amathias          #+#    #+#             */
/*   Updated: 2017/10/30 14:55:48 by amathias         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "bircd.h"

void	server_evalmsg(char *msg)
{
	char **split;

	t_user *user = prefix_to_user("amy!amy123@localhost");
	free_user(user);
	split = ft_strsplit(msg, ' ');
	if (split != NULL)
	{

	}
}
