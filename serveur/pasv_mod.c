/*
** EPITECH PROJECT, 2018
** myftp
** File description:
** pasv_mod
*/

#include "server.h"

int init_passv(t_client *clt, struct sockaddr_in *sock_in)
{
	socklen_t size = sizeof(sock_in);
	
	sock_in->sin_port = htons(0);
	sock_in->sin_family = AF_INET;
	sock_in->sin_addr.s_addr = INADDR_ANY;
	if (bind(clt->fd_mod, (const struct sockaddr*)sock_in, \
		sizeof(*sock_in)) == -1) {
		return (1);
	}
	if (listen(clt->fd_mod, 1) == -1)
		return (1);
	if (getsockname(clt->fd_mod, (struct sockaddr*)sock_in, &size) == -1)
		return (1);
	clt->passv_port = ntohs(sock_in->sin_port);
	return (0);
}

int pasv_mod(t_client *clt, struct protoent *pr_e)
{
	struct sockaddr_in sock_in;

	if (clt->fd_mod != -1)
		close(clt->fd_mod);
	pr_e = getprotobyname("TCP");
	if (pr_e == NULL)
		return (1);
	clt->fd_mod = socket(AF_INET, SOCK_STREAM, pr_e->p_proto);
	if (clt->fd_mod == -1)
		return (1);
	dprintf(clt->fd, "1\n");
	return (init_passv(clt, &sock_in));
}

void print_pasv(char **tab, t_client *clt)
{
	dprintf(clt->fd, "227 Entering Passive Mode (");
	for (int i = 0; tab[i]; i++) {
		dprintf(clt->fd, "%s, ", tab[i]);
	}
	dprintf(clt->fd, "%d, %d)\n", clt->passv_port / 256, \
		clt->passv_port % 256);
	free_tab(tab);
}

void pasv(char **tab, t_client *clt)
{
	struct protoent *pr_e = NULL;
	char *my_ip;
	char **ip;

	(void)tab;
	if (clt->log < 42) {
		dprintf(clt->fd, "530 Please login with USER and PASS.\n");
	} else {
		if (pasv_mod(clt, pr_e) == 1) {
			dprintf(clt->fd, "Problem in the init.\n");
		} else {
			clt->passv_mod = 1;
			my_ip = strdup(clt->ip);
			ip = str_wordtab(my_ip, ".");
			free(my_ip);
			print_pasv(ip, clt);
		}
	}
}