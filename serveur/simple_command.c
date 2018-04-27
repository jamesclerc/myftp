/*
** EPITECH PROJECT, 2018
** myftp
** File description:
** simple_command.c
*/

#include "server.h"

void help(char **tab, t_client *clt)
{
	if (clt->log <= 0) {
		dprintf(clt->fd, "530 Please login with USER and PASS.\n");
	} else {
		dprintf(clt->fd, "214-The following commands are recognize" \
			"d.\n ABOR ACCT ALLO APPE CDUP CWD  DELE EPRT EPSV" \
			"FEAT HELP LIST MDTM MKD "\
			"\n MODE NLST NOOP OPTS PASS PASV PORT PWD  QUIT" \
			"REIN REST RETR RMD  RNFR\n RNTO SITE SIZE SMNT" \
			"STAT STOR STOU STRU SYST TYPE USER XCUP XCWD XMKD" \
			"\n XPWD RMD\n");
		dprintf(clt->fd, "214 Help OK.\n");
	}
	(void)tab;
}

static void log_me_in(char **tab, t_client *clt)
{
	if (clt->log == 42) {
		dprintf(clt->fd, "230 Already logged in.\n");
	} else if (strcmp(clt->username, "Anonymous")) {
		dprintf(clt->fd, "530 Login incorrect.\n");
	} else {
		free(clt->password);
		dprintf(clt->fd, "230 Login successful.\n");
		if (tab[1] != NULL)
			clt->password = strdup(tab[1]);
		clt->log = 42;
	}
}

void user(char **tab, t_client *clt)
{
	if (tab[0] && !tab[1] && clt->log != 42)
		dprintf(clt->fd, "530 Permission denied.\n");
	else if (clt->log == 42) {
		dprintf(clt->fd, "530 Can't change from guest user.\n");
	} else {
		free(clt->username);
		clt->log = 0;
		clt->username = strdup(tab[1]);
		dprintf(clt->fd, "331 Please specify the password.\n");
	}
}

void pass(char **tab, t_client *clt)
{
	if (clt->log != -42)
		log_me_in(tab, clt);
	else
		dprintf(clt->fd, "503 Login with USER first.\n");
}

void quit(char **tab, t_client *clt)
{
	if (tab[0]) {
		dprintf(clt->fd, "221 Goodbye.\n");
		clt->ret = -1;
	}
}