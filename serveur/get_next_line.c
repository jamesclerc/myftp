/*
** EPITECH PROJECT, 2018
** myftp
** File description:
** get_next_line
*/

#include "get_next_line.h"
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

void condition_read(int fd, int *readd, int *taille, char *save)
{
	if (*readd <= *taille) {
		*readd = read(fd, save, READ_SIZE);
		*taille = 0;
	}
}

void add_charact(char *ret, char *save, int *taille, int *comp)
{
	ret[*comp] = save[*taille];
	*comp = *comp + 1;
	*taille = *taille + 1;
}

char end_prog(char *ret, int readd, int *taille, int comp)
{
	if (comp == 0 && readd == 0)
		return (0);
	else {
		*taille = *taille + 1;
		ret[comp] = '\0';
		return (1);
	}
}

char	*get_next_line(const int fd)
{
	static char	save[READ_SIZE + 2];
	static int	taille = 1;
	static int	readd = 1;
	static int	comp = 0;
	char	*ret;
	int	size_of_malloc;

	if (fd == -1 || READ_SIZE <= 0)
		return (NULL);
	size_of_malloc = 100;
	comp = 0;
	ret = malloc(sizeof(char) * size_of_malloc);
	if (ret == NULL)
		return (NULL);
	while (readd != 0 && save[taille] != '\n') {
		condition_read(fd, &readd, &taille, save);
		while (readd > taille && save[taille] != '\n')
			add_charact(ret, save, &taille, &comp);
	}
	return (end_prog(ret, readd, &taille, comp) == 0 ? NULL : ret);
}
