##
## EPITECH PROJECT, 2018
## myftp
## File description:
## Makefile
##

NAME	= server

CC	= gcc

RM	= rm -f

SRCS	= 	serveur/main.c \
		serveur/handle_client.c \
		serveur/str_to_word_tab.c \
		serveur/do_client.c \
		serveur/get_next_line.c \
		serveur/simple_command.c \
		serveur/simple_command2.c \
		serveur/dir_command.c \
		serveur/pasv_mod.c \
		serveur/list.c

OBJS	= $(SRCS:.c=.o)

CFLAGS = -I ./include/
CFLAGS += -W -Wall -Wextra -g3 -Werror

all: $(NAME)

$(NAME): $(OBJS)
	 $(CC) $(OBJS) -o $(NAME) $(LDFLAGS)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
