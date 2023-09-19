#include <stdlib.h>
#include "main.h"

/**
 * sub_str - Makes a copy of a subset of a string and returns
 * @str: The string containing the subset of characters
 * @i: The starting position of the subset of characters
 * @can_free: Specifies if the given string can be
 *
 * Return: The string subset, otherwise 
 */
char *sub_str(char *str, int i, char can_free)
{
	char *new_str_d;
	int length = str_len(str);
	char start_dd = i < 0 ? length + i : i;
	int size_s = i < 0 ? -i : length - start_dd;
	int j;

	new_str_d = malloc(sizeof(char) * (size_s + 1));
	if (str)
	{
		for (j = 0; *(str + start_dd) != 0; j++)
		{
			*(new_str_d + j) = *(str + start_dd);
			start_dd++;
		}
		*(new_str_d + j) = '\0';
	}
	if (can_free)
		{
			free(str);
		}
	return (new_str_d);
}

/**
 * trim_start - Makes a trimmed copy of a string starting at
 * @str: The string whose beginning is to be trimmed starting
 * @c: The character to strip from the beginning of the g
 * @can_free: Specifies if the given string can be freed or not
 *
 * Return: The trimmed copy, otherwise NULL
 */
char *trim_start(char *str, char c, char can_free)
{
	int i, j, length;
	char *new_str_d;

	for (i = 0; *(str + i) != '\0' && *(str + i) == c; i++)
		;
	length = str_len(str) - i;
	new_str_d = malloc(sizeof(char) * (length + 1));
	if (new_str_d)
	{
		for (j = 0; *(str + i) != '\0'; i++)
		{
			*(new_str_d + j) = *(str + i);
			j++;
		}
		*(new_str_d + j) = '\0';
		if (can_free)
			free(str);
	}
	return (new_str_d);
}

/**
 * trim_end - Makes a trimmed copy of a string and returns
 * @str: The string whose ending is to be trimmed off
 * @c: The character to strip from the end of the string @str
 * @can_free: Specifies if the given string can be freed or not
 *
 * Return: The trimmed copy, otherwise NULL
 */
char *trim_end(char *str, char c, char can_free)
{
	char *new_str_d;
	int length = str_len(str);
	int i, j;

	for (i = length - 1; i >= 0 && *(str + i) == c; i--)
		;
	new_str_d = malloc(sizeof(char) * (length + 1));
	if (new_str_d)
	{
		for (j = 0; j <= i; j++)
			{
				*(new_str_d + j) = *(str + j);
			}
		*(new_str_d + j) = '\0';
		if (can_free)
			free(str);
	}
	return (new_str_d);
}

/**
 * str_copy - Makes a copy of a string and returns
 * @str: The string to copy to @str
 *
 * Return: The copied string, otherwise NULL
 */
char *str_copy(char *str)
{
	char *new_str_d;
	int i;
	int length = str_len(str);

	new_str_d = malloc(sizeof(char) * (length + 1));
	if (new_str_d)
	{
		for (i = 0; i < length; i++)
			{
				*(new_str_d + i) = *(str + i);
			}
		*(new_str_d + i) = '\0';
	}
	return (new_str_d);
}
