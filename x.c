/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   x.c                                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amathias <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/25 11:24:28 by amathias          #+#    #+#             */
/*   Updated: 2017/11/03 16:43:50 by amathias         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bircd.h"

int		x_int(int err, int res, char *str, char *file)
{
	if (res == err)
	{
		ft_putstr_fd(str, 2);
		ft_putstr_fd(" error (", 2);
		ft_putstr_fd(file, 2);
		ft_putstr_fd("): ", 2);
		ft_putendl_fd(strerror(errno), 2);
		exit(1);
	}
	return (res);
}

void	*x_void(void *err, void *res, char *str, char *file)
{
	if (res == err)
	{
		ft_putstr_fd(str, 2);
		ft_putstr_fd(" error (", 2);
		ft_putstr_fd(file, 2);
		ft_putstr_fd("): ", 2);
		ft_putendl_fd(strerror(errno), 2);
		exit(1);
	}
	return (res);
}
