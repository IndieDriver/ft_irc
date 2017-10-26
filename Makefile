# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: amathias <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/12/03 11:09:29 by amathias          #+#    #+#              #
#    Updated: 2017/10/26 17:04:21 by amathias         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCSERVER =	main_server.c		\
			x.c					\
			main_loop.c			\
			init_fd.c			\
			do_select.c			\
			check_fd.c			\
			srv_create.c		\
			srv_accept.c		\
			client_read.c		\
			client_write.c		\
			cli_evalcmd.c		\
			cli_create.c		\
			irc_cmd.c			\
			server.c			\
			server_evalmsg.c	\

SRCCLIENT =	main_client.c		\
			x.c					\
			cli_create.c		\
			client_read.c		\
			client_write.c		\
			srv_accept.c		\
			main_loop.c			\
			check_fd.c			\
			init_fd.c			\
			do_select.c			\
			cli_evalcmd.c		\
			irc_cmd.c			\
			server_evalmsg.c	\

OBJSERVER = $(SRCSERVER:.c=.o)
OBJCLIENT = $(SRCCLIENT:.c=.o)
SERVER = serveur
CLIENT = client
CC = clang
RM = rm -f
CFLAGS = -Wall -Werror -Wextra -pedantic -g

LIB_PATH = ./libft/
LIB_NAME = -lft
LIB = $(addprefix -L,$(LIB_PATH))
LFLAGS = $(LIB) $(LIB_NAME)

INC_PATH = ./libft/
INC = $(addprefix -I,$(INC_PATH))

all: lib $(SERVER) $(CLIENT)

lib:
	make -C ./libft

$(SERVER): $(OBJSERVER)
	$(CC) $(CFLAGS) $(OBJSERVER) $(LFLAGS) -o $@

$(CLIENT): $(OBJCLIENT)
	$(CC) $(CFLAGS) $(OBJCLIENT) $(LFLAGS) -o $@

%.o: %.c
	$(CC) $(INC) -o $@ -c $^ $(CFLAGS)

clean:
	$(RM) $(OBJSERVER)
	$(RM) $(OBJCLIENT)
	make clean -C ./libft

fclean: clean
	$(RM) $(SERVER)
	$(RM) $(CLIENT)
	make fclean -C ./libft

re: fclean all
