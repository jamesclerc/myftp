/*
** EPITECH PROJECT, 2018
** myftp
** File description:
** server.h
*/

#ifndef SERVER_H_
#define SERVER_H_

#include <sys/types.h>
#include <stdio.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/wait.h>
#include <stdbool.h>

typedef struct s_server {
	int fd_srv;
	int fd_clt;
	int port;
	int status;
	char *path;
	struct protoent *pr_e;
	struct sockaddr_in sock_in;
	socklen_t sock_in_size;
} t_server;

typedef struct s_client {
	int fd;
	char *ip;
	char *username;
	char *password;
	int fd_mod;
	int passv_port;
	int passv_mod;
	int log;
	char *path_cl;
	bool quit;
	int ret;
} t_client;

char *get_next_line(int fd);
void handle_client_before(t_server *server);
char **str_wordtab(char *str, char *tok);
void print_tab(char **tab);
void free_tab(char **tab);
void do_client(char **tab, t_client *clt);

void help(char **tab, t_client *clt);
void user(char **tab, t_client *clt);
void pass(char **tab, t_client *clt);
void quit(char **tab, t_client *clt);

void cdup(char **tab, t_client *clt);
void cwd(char **tab, t_client *clt);

void pwd(char **tab, t_client *clt);
void delet(char **tab, t_client *clt);
void noop(char **tab, t_client *clt);

void pasv(char **tab, t_client *clt);
void list(char **tab, t_client *clt);

#endif /* !SERVER_H_ */
