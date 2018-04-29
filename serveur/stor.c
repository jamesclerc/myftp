/*
** EPITECH PROJECT, 2018
** myftp
** File description:
** stor.c
*/

#include "server.h"

int get_stor(char **tab, int fd, t_client *clt)
{
	int file = open(tab[1], O_CREAT | O_WRONLY | O_TRUNC, 0666);
	char str[2048];
	int i;

	if (file == -1)
		return (1);
	dprintf(clt->fd, "150 Opening BINARY mode data connection.\n");
	while (1) {
		i = read(fd, str, 2047);
		if (i <= 0)
			break;
		str[i] = '\0';
		dprintf(file, "%s", str);
	}
	dprintf(clt->fd, "226 Transfer complete.\n");
	close(clt->fd_mod);
	clt->passv_mod = 0;
	close(file);
	return (0);
}

void do_stor(char **tab, t_client *clt)
{
	struct sockaddr_in s_in;
	socklen_t size = sizeof(s_in);
	int fd_new = (clt->passv_mod == 2) ? clt->fd_mod : \
		accept(clt->fd_mod, (struct sockaddr *)&s_in, &size);

	if (fd_new == -1)
		dprintf(clt->fd, "425 problem with connection.\n");
	else {
		if (get_stor(tab, fd_new, clt) == 1)
			dprintf(clt->fd, "550 Failed to open file.\n");
	}
}

void stor(char **tab, t_client *clt)
{
	if (clt->log < 42)
		dprintf(clt->fd, "530 Please login with USER and PASS.\n");
	else {
		if (clt->passv_mod == 0)
			dprintf(clt->fd, "425 Use PORT or PASV first.\n");
		else
			do_stor(tab, clt);
	}
}

void free_client(t_client *clt)
{
	if (close(clt->fd) == -1)
		exit(84);
	if (close(clt->fd_mod) == -1)
		exit(84);
	free(clt->username);
	free(clt->password);
	free(clt);
}
