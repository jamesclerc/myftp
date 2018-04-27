/*
** EPITECH PROJECT, 2018
** myftp
** File description:
** do_client.c
*/

#include "../include/server.h"

/* void stor(char **tab, t_client *clt) */
/* { */
/* 	if (clt->log <= 42) */
/* 		dprintf(clt->fd, "530 Please login with USER and PASS.\n"); */
/* 	else { */
/* 		if (clt->passv_mod == 0) */
/* 			dprintf(clt->fd, "425 Use PORT or PASV first.\n"); */
/* 		else */
/* 			do_stor(tab); */
/* 	} */
/* } */

void function(char **tab, t_client *clt, int i)
{
	void (*function[12])(char **tab, t_client *clt) =
		{&user, &pass, &quit, &cwd, &cdup, &pwd, &delet, \
		&help, &noop, &pasv, &list};

	(*function[i])(tab, clt);
}

int do_cmd(char **tab, t_client *clt)
{
	char *func[12] = {"USER", "PASS", "QUIT", "CWD", "CDUP", \
		"PWD", "DELE", "HELP", "NOOP", "PASV", "LIST", NULL};

	for (int i = 0; func[i] != NULL ; i++){
		if (strcmp(tab[0], func[i]) == 0) {
			function(tab, clt, i);
			return (0);
		}
	}
	return (1);
}

void do_client(char **tab, t_client *clt)
{
	if (tab[0] == NULL)
		dprintf(clt->fd, "500 Unknow command.\n");
	else if (do_cmd(tab, clt) == 0) {
		return;
	} else {
		dprintf(clt->fd, "500 Unknow command.\n");
		return;
	}
}
