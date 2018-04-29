/*
** EPITECH PROJECT, 2018
** str_to_wordtab
** File description:
** str_to_word
*/

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

char **str_wordtab(char *str, char *tok)
{
	int i = 0;
	char **tab = malloc(sizeof(char *));
	char *token = strtok(str, tok);

	if (!str || !tab || !token)
		return (NULL);
	while (1) {
		tab[i] = strdup(token);
		i = i + 1;
		tab = realloc(tab, (sizeof(char *) * (i + 1)));
		token = strtok(NULL, tok);
		if (token == NULL){
			tab[i] = token;
			break;
		}
	}
	free(token);
	return (tab);
}

void print_tab(char **tab)
{
	int i = 0;

	while (tab[i]) {
		printf("%s\n", tab[i]);
		i++;
	}
}

void free_tab(char **tab)
{
	int i = -1;

	while (tab[++i])
		free(tab[i]);
	free(tab);
}
