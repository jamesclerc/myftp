/*
** EPITECH PROJECT, 2018
** myftp
** File description:
** dir_command.c
*/

#include "server.h"

static int change_dir(char **tab) {
	char *path = realpath(tab[1], NULL);

	if ((tab[1] && tab[2] != NULL) || (path == NULL)
		|| (chdir(tab[1]) == -1)) {
		return (1);
	}
	return (0);
}

void cwd(char **tab, t_client *clt)
{
	if (clt->log <= 0) {
		dprintf(clt->fd, "530 Please login with USER and PASS.\n");
	} else if (tab[1] == NULL || change_dir(tab) == 1) {
		dprintf(clt->fd, "550 Failed to change directory.\n");
	} else {
		dprintf(clt->fd, "250 Directory successfully changed.\n");
	}
}

static int change_dir_cdup(char *path, char **tab)
{
	(void)tab;
	if (chdir(path) == -1) {
		return (1);
	}
	return (0);
}

void cdup(char **tab, t_client *clt)
{
	if (clt->log <= 0) {
		dprintf(clt->fd, "530 Please login with USER and PASS.\n");
	} else if (change_dir_cdup("../", tab) == 1) {
		dprintf(clt->fd, "550 Failed to change directory.\n");
	} else {
		dprintf(clt->fd, "250 Directory successfully changed.\n");
	}
}