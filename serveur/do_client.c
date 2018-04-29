/*
** EPITECH PROJECT, 2018
** myftp
** File description:
** do_client.c
*/

#include "server.h"

void function(char **tab, t_client *clt, int i)
{
	static void (*function[14])(char **tab, t_client *clt) =
		{&user, &pass, &quit, &cwd, &cdup, &pwd, &delet, \
		&help, &noop, &pasv, &list, &retr, &stor, &port};

	(*function[i])(tab, clt);
}

int do_cmd(char **tab, t_client *clt)
{
	static const char *func[15] = {"USER", "PASS", "QUIT", "CWD", "CDUP", \
			"PWD", "DELE", "HELP", "NOOP", "PASV", "LIST", \
			"RETR", "STOR", "PORT", NULL};

	for (int i = 0; func[i] != NULL ; i++){
		if (strcasecmp(tab[0], func[i]) == 0) {
			print_tab(tab);
			function(tab, clt, i);
			return (0);
		}
	}
	return (1);
}

void do_client(char **tab, t_client *clt)
{
	if (tab == NULL)
		dprintf(clt->fd, "500 Unknow command.\n");
	else if (do_cmd(tab, clt) == 0) {
		return;
	} else {
		dprintf(clt->fd, "500 Unknow command.\n");
		return;
	}
}
