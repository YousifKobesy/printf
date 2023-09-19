#include "main.h"

/**
 * str_len - Computes the length of a string and returns
 * @str: The source string to be
 *
 * Return: The length of the ing.
 */
int str_len(char *str)
{
	int len = 0;

	if (str == NULL)
		return (0);
	while (*(str + len) != '\0')
		len++;
	return (len);
}

/**
 * mem_set - Fills a section of a  character
 * \ (starts from position 0)
 * @str: The string  section to be filled
 * @n: The  the section to fill
 * @c: character to fill the section with
 */
void mem_set(char *str, int n, char c)
{
	int i;

	for (i = 0; str != NULL && i < n; i++)
		{
			*(str + i) = c;
		}
}

/**
 * left_shift - Moves a string n bytes to th
 * @str: The string to sh
 * @n: The number of bs to shift
 */
void left_shift(char *str, int n)
{
	int i;

	for (i = 1; i <= n; i++)
		{
			str[i - 1] = str[i] != '\0' && str[i - 1] != '\0' ? str[i] : '\0';
		}
}

/**
 * index_of - Returns the first index of a  in a string
 * @str: The string that could containcharacter
 * @c: The character to look f
 *
 * Return: The  the character if found, otherwise -1
 */
int index_of(char *str, char c)
{
	int i;

	for (i = 0; *(str + i) != '\0' && *(str + i) != c; i++)
		;
	return (*(str + i) == c ? i : -1);
}

/**
 * rev_string - Reverses a string and returns
 * @s: The string to be reversed from
 */
void rev_string(char *s)
{
	int length = 0;
	int i;

	while (*(s + length) != '\0')
		{
			length++;
		}

	for (i = 0; i < length / 2; i++)
	{
		char temp = *(s + length - i - 1);

		*(s + length - i - 1) = *(s + i);
		*(s + i) = temp;
	}
}
