#include "bircd.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/resource.h>

void	clean_fd(t_fd *fd)
{
  fd->type = FD_FREE;
  fd->fct_read = NULL;
  fd->fct_write = NULL;
}

void		init_env_client(t_env_client *e)
{
  e->stdin_fd = (t_fd*)Xv(NULL, malloc(sizeof(t_fd*)), "malloc");
  e->server_fd = (t_fd*)Xv(NULL, malloc(sizeof(t_fd*)), "malloc");

  clean_fd(e->stdin_fd);
  clean_fd(e->stdin_fd);
}

char	*get_opt(t_env_client *e, int ac, char **av)
{
  if (ac != 3) //TODO: handle optional parameter
  {
      fprintf(stderr, USAGE, av[0]);
      exit(1);
  }
  e->port = atoi(av[2]);
  return (ft_strdup(av[1]));
}

int	main(int ac, char **av)
{
  t_env_client	e;
  char	*hostname;

  init_env_client(&e);
  hostname = get_opt(&e, ac, av);
  cli_create(&e, hostname,e.port);
  while (1)
  {
    init_fd_client(&e);
    e.r = select(e.max + 1, &e.fd_read, NULL,NULL, NULL);
    check_fd_client(&e);
  }
  free (hostname);
  return (0);
}
