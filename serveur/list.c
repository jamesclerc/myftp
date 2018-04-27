/*
** EPITECH PROJECT, 2018
** myftp
** File description:
** list.c
*/

#include "server.h"

void list_call(t_client *clt)
{
	char str[4096];
	struct sockaddr_in s_in;
	socklen_t size = sizeof(s_in);
	int fd_new = accept(clt->fd_mod, (struct sockaddr *)&s_in, &size);
	FILE *file;

	if (fd_new == -1)
		dprintf(clt->fd, "425 problem with connection.\n");
	else {
		file = popen("ls -la", "r");
		while (fgets(str, 4096, file))
			dprintf(fd_new, "%s", str);
		fclose(file);
		close(clt->fd_mod);
		close(fd_new);
		clt->fd_mod = -1;
	}
}

void list(char **tab, t_client *clt)
{
	if (clt->log < 42) {
		dprintf(clt->fd, "530 Please login with USER and PASS.\n");
	} else {
		if (clt->passv_mod == 0)
			dprintf(clt->fd, "425 Use PORT or PASV first.\n");
		else
			list_call(clt);
		(void)tab;
	}
}