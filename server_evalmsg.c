/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_evalmsg.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amathias <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/26 10:21:47 by amathias          #+#    #+#             */
/*   Updated: 2017/10/26 16:08:39 by amathias         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "bircd.h"

void	server_evalmsg(char *msg)
{
	char **split;

	split = ft_strsplit(msg, ' ');
	if (split != NULL)
	{

	}
}
