/*
** EPITECH PROJECT, 2018
** myftp
** File description:
** main.c
*/

#include "../include/server.h"

void display_help(void)
{
	printf("Usage: ./server [port] [path]\n");
}

t_server *get_data_server(t_server *server, char *port, char *path)
{
	int proto;

	server->pr_e = getprotobyname("TCP");
	server->path = path;
	server->port = atoi(port);
	if (server->pr_e == NULL)
		return NULL;
	proto = server->pr_e->p_proto;
	server->fd_srv = socket(AF_INET, SOCK_STREAM, proto);
	if (server->fd_srv == -1)
		return NULL;
	server->sock_in_size = sizeof(server->sock_in);
	server->sock_in.sin_family = AF_INET;
	server->sock_in.sin_port = htons(server->port);
	server->sock_in.sin_addr.s_addr = INADDR_ANY;
	return ((server->fd_srv == -1) ? NULL : server);
}

int init_server(char *port, char *path, t_server *server)
{
	if (chdir(path) == -1) {
		fprintf(stderr, "Error: Bad path\n");
		return (84);
	}
	server = get_data_server(server, port, path);
	if (server == NULL)
		return (84);
	if (bind(server->fd_srv, (const struct sockaddr *)&server->sock_in,
		sizeof(server->sock_in)) == -1) {
		shutdown(server->fd_srv, 2);
		if (close(server->fd_srv) == -1)
			return (84);
		return (84);
	}
	if (listen(server->fd_srv, 42) == -1){
		if (close(server->fd_srv) == -1)
			return (84);
		return (84);
	}
	return (0);
}

int main(int ac, char **av)
{
	t_server *server = malloc(sizeof(t_server));

	if (server == NULL)
		return (84);
	if (ac != 3)
		display_help();
	else {
		if (init_server(av[1], av[2], server) == 84)
			return (84);
		handle_client_before(server);
		free(server);
	}
	return (0);
}
