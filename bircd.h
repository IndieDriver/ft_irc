/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bircd.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amathias <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/25 11:12:24 by amathias          #+#    #+#             */
/*   Updated: 2017/10/31 16:52:36 by amathias         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BIRCD_H
# define BIRCD_H

# include <sys/select.h>
# include "libft/libft.h"
# include "server.h"

# define FD_FREE	0
# define FD_SERV	1
# define FD_CLIENT	2

# define BUF_SIZE	4096

# define Xv(err,res,str) (x_void(err,res,str,__FILE__,__LINE__))
# define X(err,res,str) (x_int(err,res,str,__FILE__,__LINE__))
# define MAX(a,b)	((a > b) ? a : b)

# define USAGE		"Usage: %s port\n"
# define CL_USAGE   "Usage: %s [hostname [port]]\n"

enum				e_arg_type
{
	NONE = 0, SINGLE = 1, OPTIONAL = 2, MULTI = 3
};

typedef struct		s_server_command
{
	char			*irc_cmd;
	enum e_arg_type	arg1;
	enum e_arg_type	arg2;
	enum e_arg_type	arg3;
	enum e_arg_type	arg4;
}					t_server_command;

typedef struct		s_client_command
{
	char			*client_cmd;
	char			*irc_cmd;
	enum e_arg_type	arg1;
	enum e_arg_type	arg2;
	enum e_arg_type	arg3;
	enum e_arg_type	arg4;
	char			*usage;
}					t_client_command;

extern const t_client_command g_client_commands[];
extern const t_server_command g_server_commands[];

typedef struct		s_fd
{
	int				type;
	void			(*fct_read)();
	void			(*fct_write)();
	char			buf_read[BUF_SIZE + 1];
	char			buf_write[BUF_SIZE + 1];
	char			*hostname;
	char			*nick;
	char			*user;
	int				has_login;
}					t_fd;

typedef struct		s_env
{
	t_serv			*serv;
	t_fd			*fds;
	int				port;
	int				maxfd;
	int				max;
	int				r;
	fd_set			fd_read;
	fd_set			fd_write;
	char			*hostname;
}					t_env;

typedef struct		s_env_client
{
	t_fd			stdin_fd;
	t_fd			server_fd;
	int				server_soc;
	int				port;
	int				max;
	int				r;
	int				connected;
	fd_set			fd_read;
	int				running;
}					t_env_client;

void				main_loop(t_env *e);
void				srv_create(t_env *e, int port);
void				cli_create(t_env_client *e, const char *addr, int port);
void				srv_accept(t_env *e, int s);

void				write_to_client(t_env *e, int clientsocket);
void				write_msg_to_client(char *msg, int cs);
void				write_to_server(t_env_client *e, char *buffer);
int					get_client_fd(t_env *e, char *nick);

void				read_from_client(t_env *e, int clientsocket);
void				read_from_server(t_env_client *e);
void				clean_fd(t_fd *fd);
int					x_int(int err, int res, char *str, char *file, int line);
void				*x_void(void *err, void *res, char *str, char *file,
						int line);
void				init_fd(t_env *e);
void				init_fd_client(t_env_client *e);
void				do_select(t_env *e);
void				check_fd_server(t_env *e);
void				check_fd_client(t_env_client *e);

char				*get_request(t_env_client *e, char *cmd);

int					arg_with_colon(t_client_command cli_cmd);
int					contain_irc_command(char *str);
int					get_client_command_index(char *str);
int					get_server_command_index(char *str);
int					is_valid_client_command(t_client_command cli_cmd,
						char **split);
int					is_valid_server_command(t_server_command cli_cmd,
						char **split);

char				*server_evalmsg(t_env *e, t_fd *fd);
void				clear_server(t_env *e);
void				print_serv(t_env *e);

char				*client_evalmsg(t_env_client *e, char *cmd);

t_user				*prefix_to_user(char *prefix);
char				*user_to_prefix(t_user *user);


char				*rpl_welcome(t_env *e, t_user *user);
char				*rpl_nickinuse(t_env *e, t_user *user);

void				broadcast_msg_channel(t_env *e, t_chan *chan, char *msg);
void				broadcast_msg_users_channel(t_env *e, char *nick, char *msg);
void				broadcast_msg_server(t_env *e, char *msg);

#endif
