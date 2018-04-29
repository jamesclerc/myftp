/*
** EPITECH PROJECT, 2018
** myftp
** File description:
** port.c
*/

#include "server.h"

int init_port2(t_client *clt, char **tab, struct sockaddr_in *sock_in)
{
	char *ip = get_ip(tab);
	socklen_t size = sizeof(*sock_in);

	sock_in->sin_port = htons(atoi(tab[4]) * 256 + atoi(tab[5]));
	sock_in->sin_family = AF_INET;
	sock_in->sin_addr.s_addr = inet_addr(ip);
	if (connect(clt->fd_mod, (struct sockaddr *)sock_in, size) == -1)
		return (1);
	free_tab(tab);
	dprintf(clt->fd, "200 PORT command sucess.\n");
	clt->passv_mod = 2;
	free(ip);
	return (0);
}

int init_port(char **tab, t_client *clt, struct protoent *pr_e)
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
	return (init_port2(clt, tab, &sock_in));
}

void do_port(char **tab, t_client *clt, struct protoent *pr_e)
{
	char **cmd = str_wordtab(tab[1], ",\n");

	if (!cmd || valid_cmd(cmd) == 1)
		dprintf(clt->fd, "500 Illegal PORT command.\n");
	else {
		if (init_port(cmd, clt, pr_e) == 1)
			dprintf(clt->fd, "500 Illegal PORT command.\n");
	}
}

void port(char **tab, t_client *clt)
{
	struct protoent *pr_e = NULL;

	if (clt->log < 42) {
		dprintf(clt->fd, "530 Please login with USER and PASS.\n");
	} else {
		if (!tab[1])
			dprintf(clt->fd, "500 Illegal PORT command.\n");
		else
			do_port(tab, clt, pr_e);
	}
}
