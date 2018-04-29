/*
** EPITECH PROJECT, 2018
** myftp
** File description:
** handle_client.c
*/

#include "server.h"

t_client *create_new_client(t_server *server, char *ip)
{
	t_client *new = malloc(sizeof(t_client));

	if (new == NULL)
		return NULL;
	new->passv_mod = 0;
	new->passv_port = -42;
	new->fd_mod = -1;
	new->fd = server->fd_clt;
	new->ip = ip;
	new->quit = false;
	new->username = NULL;
	new->password = NULL;
	new->ret = 0;
	new->log = -42;
	return new;
}

void handle_eve2_client(t_client *clt, char *line)
{
	char **tab;

	if (line != NULL) {
		if (strlen(line) > 0) {
			tab = str_wordtab(line, "  \t\n\r");
			(tab != NULL) ? do_client(tab, clt) : \
				dprintf(clt->fd, "500 Unknow command.\n");
			(tab != NULL) ? free_tab(tab) : 0;
		}
		free(line);
	}
}

void handle_eve_client(t_server *server, char *ip)
{
	char *line = NULL;
	t_client *clt = create_new_client(server, ip);

	if (!clt)
		return;
	dprintf(clt->fd, "220 (vsFTPd 3.0.0)\n");
	while (1) {
		line = get_next_line(clt->fd);
		handle_eve2_client(clt, line);
		if (clt->ret == -1)
			break;
	}
	free_client(clt);
}

int handle_client(t_server *server, struct sockaddr_in client)
{
	while (1) {
		server->fd_clt = accept(server->fd_srv, (struct sockaddr *)
			&client, &server->sock_in_size);
		if (server->fd_clt != -1) {
			if (fork() == 0) {
				handle_eve_client(server,
					inet_ntoa(client.sin_addr));
				close(server->fd_srv);
				exit(0);
			} else {
				close(server->fd_clt);
			}
		}
	}
	close(server->fd_srv);
	return (0);
}

void handle_client_before(t_server *server)
{
	struct sockaddr_in s_in_client;

	handle_client(server, s_in_client);
}
