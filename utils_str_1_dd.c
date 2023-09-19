#include <stdlib.h>
#include <stdio.h>
#include "main.h"

/**
 * append_char - iple copies of a given character to the
 * \ end of a string
 * @str: The ng whose ending is to be trimmed
 * @c: aracter to add at the end of the string
 * @n: The number of  the character should be added
 * @can_free: es if the given string can be freed
 *
 * Return: The new  the string, otherwise NULL
 */
char *append_char(char *str, char c, int n, char can_free)
{
	int i, size_d;
	char *new_str_ss;

	size_d = str ? str_len(str) : 0;
	new_str_ss = malloc(sizeof(char) * (size_d + n + 1));
	if (new_str_ss)
	{
		for (i = 0; i < (size_d + n); i++)
			{
				new_str_ss[i] = i < size_d ? str[i] : c;
			}
		new_str_ss[i] = '\0';
	}
	if (can_free)
		{
			free(str);
		}
	return (new_str_ss);
}

/**
 * delete_char - Removes copies of a given  
 * @str: The string containing  the characters
 * @c: The character from the string .
 * @can_free:  if the given string  be freed
 *
 * Return: The new copy of the string NULL
 */
char *delete_char(char *str, char c, char can_free)
{
	char *new_str_ss;
	int length = str_len(str), i;

	new_str_ss = malloc(sizeof(char) * (length - count_char(str, c) + 1));
	if (new_str_ss)
	{
		for (i = 0, length = 0; *(str + i) != '\0'; i++)
		{
			if (*(str + i) != c)
				{
					*(new_str_ss + length++) = *(str + i);
				}
		}
		*(new_str_ss + length) = '\0';
	}
	if (can_free)
		free(str);
	return (new_str_ss);
}

/**
 * insert_char - Inserts a character into a string and returns a pointer to
 * @str: The source string to insert the character into
 * @pos: The insertion position of the character in the string to be inserted
 * @c: The character to insert into the string (must be a valid character
 * @can_free: Specifies if the given string can be d terminated
 *
 * Return: The trimmed copy, otherwise 
 */
char *insert_char(char *str, int pos, char c, char can_free)
{
	char *new_str_ss;
	int i, j, length;

	length = str_len(str);
	new_str_ss = malloc(sizeof(char) * (length + 2));
	if (new_str_ss != NULL)
	{
		for (i = 0, j = 0; i < length; i++)
		{
			if (i == pos)
				*(new_str_ss + j++) = c;
			*(new_str_ss + j) = *(str + i);
			j++;
		}
		*(new_str_ss + length + 1) = '\0';
		if (can_free)
			{
				free(str);
			}
	}
	return (new_str_ss);
}

/**
 * count_char - Counts the number of copies of a 
 * @str: The source string  ssa/.
 * @c: The character to look for ssds.
 *
 * Return: The number of times the racter was found
 */
int count_char(char *str, char c)
{
	int count_rf = 0, i;

	for (i = 0; str != NULL && *(str + i) != '\0'; i++)
		count_rf += *(str + i) == c ? 1 : 0;
	return (count_rf);
}

/**
 * str_cat - Concatenates two strings and returns
 * @left: The left string to concaten
 * @right: The right string to concatenate
 * @can_free: Specifies if the given strings can be freed or not
 *
 * Return: A pointer to the concatenated string
 */
char *str_cat(char *left, char *right, char can_free)
{
	int left_len = str_len(left);
	int right_len = str_len(right);
	int i;
	char *str;

	if (left == NULL && right == NULL)
		{
			return (NULL);
		}
	str = malloc(sizeof(char) * (left_len + right_len + 1));
	if (str != NULL)
	{
		for (i = 0; *(left + i) != '\0'; i++)
			{
				*(str + i) = *(left + i);
			}
		for (i = 0; *(right + i) != '\0'; i++)
			*(str + left_len + i) = *(right + i);
		*(str + left_len + right_len) = '\0';
	}
	if (can_free)
	{
		free(left);
		free(right);
	}
	return (str);
}
