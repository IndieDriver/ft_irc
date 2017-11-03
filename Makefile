# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: amathias <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/12/03 11:09:29 by amathias          #+#    #+#              #
#    Updated: 2017/11/03 18:52:47 by amathias         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCSERVER =	main_server.c		\
			get_opt.c			\
			server_io.c			\
			x.c					\
			init_fd.c			\
			srv_create.c		\
			srv_accept.c		\
			irc_cmd.c			\
			server.c			\
			channel.c			\
			channel_utils.c		\
			users.c				\
			users_utils.c		\
			server_evalmsg.c	\
			prefix.c			\
			irc_reply.c			\
			broadcast.c			\
			ring_buffer.c		\
			ring_buffer_utils.c	\
			server_cmd.c		\
			server_cmd2.c		\

SRCCLIENT =	main_client.c		\
			get_opt.c			\
			client_io.c			\
			x.c					\
			cli_create.c		\
			init_fd.c			\
			do_select.c			\
			cli_evalcmd.c		\
			irc_cmd.c			\
			cli_evalres.c		\
			prefix.c			\
			server.c			\
			channel.c			\
			channel_utils.c		\
			users.c				\
			users_utils.c		\
			ring_buffer.c		\
			ring_buffer_utils.c	\

OBJSERVER = $(SRCSERVER:.c=.o)
OBJCLIENT = $(SRCCLIENT:.c=.o)
SERVER = serveur
CLIENT = client
CC = clang
RM = rm -f
CFLAGS = -Wall -Werror -Wextra -pedantic -g -fsanitize=undefined

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
