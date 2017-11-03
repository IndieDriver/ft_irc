/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amathias <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/26 14:49:38 by amathias          #+#    #+#             */
/*   Updated: 2017/11/03 14:20:20 by amathias         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_H
# define SERVER_H
# include <stdio.h>

# define MAX_CHANNEL	512
# define MAX_USER		4096

typedef struct		s_user
{
	char			*nick;
	char			*user;
	char			*hostname;
	int				socket;
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

void				add_user(t_serv *serv, t_user *user);
void				remove_user(t_serv *serv, char *nick);
int					is_nick_free(t_user *users, char *nick);

void				add_user_to_list(t_user **users, t_user *user);
void				remove_user_from_list(t_user **users, char *nick);
t_user				*get_user(t_serv *serv, char *nick);
t_user				*new_user(char *nick, char *username, char *hostname,
						int socket);
t_user				*copy_user(t_user *user);
void				clear_userlist(t_user **users);
void				print_userlist(t_user *begin);
void				free_user(t_user *user);
char				*get_users_string(t_chan *chan);

t_chan				*add_channel(t_chan **channels, char *name);
void				remove_channel(t_chan **channels, char *name);
t_chan				*get_chan(t_chan *channels, char *name);
void				print_channellist(t_chan *begin);
int					is_user_in_channel(t_chan *chan, char *nick);

int					is_channel_name_free(t_chan *channels, char *chan_name);
int					is_channel_name_valid(char *chan_name);
void				add_user_to_channel(t_chan **channels, t_user *user,
						char *chan_name);
void				remove_user_from_channel(t_chan *channels, t_user *user,
						char *chan_name);
void				clear_channellist(t_chan **channels);

#endif
