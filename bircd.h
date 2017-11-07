/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bircd.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amathias <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/25 11:12:24 by amathias          #+#    #+#             */
/*   Updated: 2017/11/07 16:43:49 by amathias         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BIRCD_H
# define BIRCD_H

# include <sys/select.h>
# include "libft/libft.h"
# include <assert.h>
# include "server.h"

# define FD_FREE	0
# define FD_SERV	1
# define FD_CLIENT	2

# define BUF_SIZE	512

# define XV(err,res,str) (x_void(err,res,str,__FILE__))
# define X(err,res,str) (x_int(err,res,str,__FILE__))
# define MAX(a,b)	((a > b) ? a : b)

# define USAGE		"Usage: ./server [port]"
# define CL_USAGE   "Usage: ./client [hostname [port]]"

enum				e_arg_type
{
	NONE = 0, SINGLE = 1, OPTIONAL = 2, MULTI = 3
};

typedef struct		s_ring_buffer
{
	char			**buffer;
	size_t			head;
	size_t			tail;
	size_t			size;
}					t_ring_buffer;

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
	t_ring_buffer	rbuffer_write;
	t_ring_buffer	rbuffer_read;
	t_user			user;
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
	fd_set			fd_write;
	int				running;
}					t_env_client;

typedef struct		s_server_response
{
	t_fd			*fd;
	char			**split;
	char			*raw_msg;
}					t_server_response;

void				get_opt_server(t_env *e, int ac, char **av);
char				*get_opt_client(t_env_client *e, int ac, char **av);
int					is_valid_port(char *str);

void				main_loop(t_env *e);
void				srv_create(t_env *e, int port);
void				cli_create(t_env_client *e, const char *addr, int port);
void				srv_accept(t_env *e, int s);

void				write_to_client(t_env *e, int clientsocket);
void				append_msg_client(t_env *e, char *msg, int cs);
void				write_to_server(t_env_client *e, char *buffer);
void				append_msg_server(t_env_client *e, char *msg);

int					get_client_fd(t_env *e, char *nick);
char				*ft_fgets(char *str, int bytes);

void				read_from_client(t_env *e, int clientsocket);
void				read_from_server(t_env_client *e);
void				clean_fd(t_fd *fd);

int					x_int(int err, int res, char *str, char *file);
void				*x_void(void *err, void *res, char *str, char *file);

void				init_fd(t_env *e);
void				init_fd_client(t_env_client *e);
void				do_select(t_env *e);
void				check_fd_server(t_env *e);
void				check_fd_client(t_env_client *e);

void				register_connection(t_env_client *e, char *nick);
char				*get_request(t_env_client *e, char *cmd);

int					arg_with_colon(t_client_command cli_cmd);
int					contain_irc_command(char *str);
int					get_client_command_index(char *str);
int					get_server_command_index(char *str);
int					is_valid_client_command(t_client_command cli_cmd,
						char **split);
int					is_valid_server_command(t_server_command cli_cmd,
						char **split);

char				*server_evalmsg(t_env *e, t_fd *fd, char *msg);
void				clear_server(t_env *e);
void				rename_user(t_env *e, char *old_nick, char *new_nick);

char				*client_evalmsg(t_env_client *e, char *cmd);

t_user				*prefix_to_user(char *prefix);
char				*user_to_prefix(t_user *user);

char				*rpl_welcome(t_env *e, t_fd *fd, t_user *user);
char				*rpl_nickinuse(t_env *e, t_fd *fd, char *nick);

void				broadcast_msg_channel(t_env *e, t_chan *chan, char *msg);
void				broadcast_msg_users_channel(t_env *e, char *nick,
						char *msg);
void				broadcast_msg_server(t_env *e, char *msg);
void				broadcast_msg(t_env *e, char *dest, char *msg, char *sender);

int					rb_contain_message(t_ring_buffer *buffer);
char				*rb_get_message(t_ring_buffer *buffer);
int					rb_reset(t_ring_buffer *buffer);
int					rb_empty(t_ring_buffer *buffer);
int					rb_full(t_ring_buffer *buffer);
t_ring_buffer		*rb_init(t_ring_buffer *buffer, size_t size);
int					rb_put(t_ring_buffer *buffer, char *data);
char				*rb_get(t_ring_buffer *buffer);
void				rb_pop(t_ring_buffer *buffer);

char				*server_cmd_user(t_env *e, t_server_response *response,
						t_server_command server_cmd);
char				*server_cmd_nick(t_env *e, t_server_response *response,
						t_server_command server_cmd);
char				*server_cmd_privmsg(t_env *e, t_server_response *response,
						t_server_command server_cmd);
char				*server_cmd_join(t_env *e, t_server_response *response,
						t_server_command server_cmd);
char				*server_cmd_part(t_env *e, t_server_response *response,
						t_server_command server_cmd);
char				*server_cmd_users(t_env *e, t_server_response *response,
						t_server_command server_cmd);
char				*server_cmd_who(t_env *e, t_server_response *response,
						t_server_command server_cmd);

#endif
