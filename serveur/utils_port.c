/*
** EPITECH PROJECT, 2018
** myftp
** File description:
** utils_port.c
*/

#include "server.h"

char *get_ip(char **tab)
{
	char *str = malloc(sizeof(char) * (strlen(tab[0]) + strlen(tab[1]) + \
			strlen(tab[2]) + strlen(tab[3]) + 5));
	int i = 0;
	int j = 0;
	int k = 0;

	while (tab[i] && i != 4) {
		while (tab[i][j] != '\0'){
			str[k] = tab[i][j];
			j++;
			k++;
		}
		str[k] = '.';
		k++;
		j = 0;
		i++;
	}
	str[k - 1] = '\0';
	return (str);
}

int check_number(char *str)
{
	int i = 0;

	while (str[i]) {
		if (isdigit(str[i]) == 0)
			return (1);
		i++;
	}
	return (0);
}

int valid_cmd(char **tab)
{
	int i = 0;

	while (tab[i]) {
		check_number(tab[i]);
		i++;
	}
	if (i < 6)
		return (1);
	return (0);
}

