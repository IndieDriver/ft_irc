#ifndef BIRCD_H_
# define BIRCD_H_

# include <sys/select.h>
# include "libft/libft.h"

# define FD_FREE	0
# define FD_SERV	1
# define FD_CLIENT	2

# define BUF_SIZE	4096

# define Xv(err,res,str)	(x_void(err,res,str,__FILE__,__LINE__))
# define X(err,res,str)		(x_int(err,res,str,__FILE__,__LINE__))
# define MAX(a,b)	((a > b) ? a : b)

# define USAGE		"Usage: %s port\n"

typedef struct	s_fd
{
  int	type;
  void	(*fct_read)();
  void	(*fct_write)();
  char	buf_read[BUF_SIZE + 1];
  char	buf_write[BUF_SIZE + 1];
}		t_fd;

typedef struct	s_env
{
  t_fd		*fds;
  int		port;
  int		maxfd;
  int		max;
  int		r;
  fd_set	fd_read;
  fd_set	fd_write;
}           t_env;

typedef struct  s_env_client
{
  t_fd          *stdin_fd;
  t_fd          *server_fd;
  int           server_soc;
  int           port;
  int           max;
  int           r;
  fd_set        fd_read;
}               t_env_client;

void	main_loop(t_env *e);
void	srv_create(t_env *e, int port);
void	cli_create(t_env_client *e, const char *addr, int port);
void	srv_accept(t_env *e, int s);
void	write_to_client(t_env *e, int clientsocket);
void    write_to_server(t_env_client *e, char *buffer);
void	read_from_client(t_env *e, int clientsocket);
void    read_from_server(t_env_client *e);
void	clean_fd(t_fd *fd);
int     x_int(int err, int res, char *str, char *file, int line);
void	*x_void(void *err, void *res, char *str, char *file, int line);
void	init_fd(t_env *e);
void	init_fd_client(t_env_client *e);
void	do_select(t_env *e);
void	check_fd_server(t_env *e);
void	check_fd_client(t_env_client *e);

#endif
