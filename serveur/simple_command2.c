/*
** EPITECH PROJECT, 2018
** myftp
** File description:
** simple_command2.c
*/

#include "server.h"

void pwd(char **tab, t_client *clt)
{
	char *path;

	(void)tab;
	if (clt->log <= 0) {
		dprintf(clt->fd, "530 Please login with USER and PASS.\n");
	} else {
		path = malloc(sizeof(char) * 100);
		getcwd(path, 100);
		dprintf(clt->fd, "257 \"%s\"\n", path);
		free(path);
	}
}

void delet(char **tab, t_client *clt)
{
	if (clt->log <= 0) {
		dprintf(clt->fd, "530 Please login with USER and PASS.\n");
	} else if (tab[1] && remove(tab[1]) == 0){
		dprintf(clt->fd, "250 file deleted\n");
	} else {
		dprintf(clt->fd, "550 file not found\n");
	}
}

void noop(char **tab, t_client *clt)
{
	(void)tab;
	if (clt->log <= 0) {
		dprintf(clt->fd, "530 Please login with USER and PASS.\n");
	} else {
		dprintf(clt->fd, "200 NOOP ok.\n");
	}
}