/*
** EPITECH PROJECT, 2018
** myftp
** File description:
** retr.c
*/

#include "server.h"

int aff_retr(char **tab, int fd_new, t_client *clt)
{
	FILE *file = fopen(tab[1], "r+");
	char str[4096];

	if (file == NULL) {
		close(fd_new);
		fclose(file);
		return (1);
	}
	else {
		dprintf(clt->fd, "150 Opening BINARY mode data connection.\n");
		while (fgets(str, 4096, file))
			dprintf(fd_new, "%s", str);
		fclose(file);
		dprintf(clt->fd, "226 Transfer complete.\n");
		clt->passv_mod = 0;
		close(fd_new);
		return (0);
	}
}

void do_retr(char **tab, t_client *clt)
{
	struct sockaddr_in s_in;
	socklen_t size = sizeof(s_in);
	int fd_new = (clt->passv_mod = 2) ? clt->fd_mod : \
		accept(clt->fd_mod, (struct sockaddr *)&s_in, &size);

	if (fd_new == -1)
		dprintf(clt->fd, "425 problem with connection.\n");
	else {
		if (aff_retr(tab, fd_new, clt) == 1)
			dprintf(clt->fd, "550 Failed to open file.\n");
	}
}

void retr(char **tab, t_client *clt)
{
	if (clt->log < 42)
		dprintf(clt->fd, "530 Please login with USER and PASS.\n");
	else {
		if (clt->passv_mod == 0)
			dprintf(clt->fd, "425 Use PORT or PASV first.\n");
		else
			do_retr(tab, clt);
	}
}
