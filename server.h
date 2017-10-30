/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amathias <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/26 14:49:38 by amathias          #+#    #+#             */
/*   Updated: 2017/10/30 11:59:48 by amathias         ###   ########.fr       */
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

void				add_user(t_serv *serv, char *nick, char *user,
						char *hostname);
void				remove_user(t_serv *serv, char *nick);
int					is_nick_free(t_user *users, char *nick);

void				add_user_to_list(t_user **users, t_user *user);
void				remove_user_from_list(t_user **users, char *nick);
t_user				*get_user(t_user *begin, char *nick);
t_user				*new_user(char *nick, char *username, char *hostname);
void				clear_userlist(t_user **users);

void				add_channel(t_chan **channels, char *name);
void				remove_channel(t_chan **channels, char *name);
t_chan				*get_chan(t_chan *channels, char *name);

t_user				*get_user(t_user *begin, char *nick);
void				add_user_to_channel(t_chan **channels, t_user *user,
						char *chan_name);
void				delete_user_from_channel(t_chan *channels, t_user *user,
						char *chan_name);
void				clear_channellist(t_chan **channels);

#endif
