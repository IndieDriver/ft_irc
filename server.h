/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amathias <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/26 14:49:38 by amathias          #+#    #+#             */
/*   Updated: 2017/10/26 17:45:46 by amathias         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_H
# define SERVER_H

# define MAX_CHANNEL	512
# define MAX_USER		4096

typedef struct		s_user
{
	char			*nick;
	char			*user;
	char			*hostname;
	void			*next;
}					t_user;

typedef struct		s_chan
{
	char			*name;
	t_user			*users;
	void			*next;
}					t_chan;

typedef struct		s_serv
{
	t_chan			*channels;
	t_user			*users;
}					t_serv;

#endif
