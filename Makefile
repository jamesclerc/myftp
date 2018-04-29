##
## EPITECH PROJECT, 2018
## myftp
## File description:
## Makefile
##

NAME	= server

CC	= gcc

RM	= rm -f

SRCS	=	./serveur/dir_command.c \
		./serveur/do_client.c \
		./serveur/get_next_line.c \
		./serveur/handle_client.c \
		./serveur/list.c \
		./serveur/main.c \
		./serveur/pasv_mod.c \
		./serveur/retr.c \
		./serveur/simple_command.c \
		./serveur/simple_command2.c \
		./serveur/str_to_word_tab.c \
		./serveur/stor.c \
		./serveur/port.c \
		./serveur/utils_port.c

OBJS	= $(SRCS:.c=.o)

CFLAGS = -I ./include/
CFLAGS += -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(OBJS) -o $(NAME) $(LDFLAGS)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
