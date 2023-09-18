#include <stdlib.h>
#include "main.h"

/**
 * hex_digit - converts a decimal less than 16 to.
 * @c: The decimal point to convert.
 *
 * Return: The hexadecimal digit, otherwise '\0' is returned..
 */
char hex_digit(char c)
{
	char digits_ed[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9',
		'a', 'b', 'c', 'd', 'e', 'f'
	};

	return (c >= 0 && c <= 15 ? *(digits_ed + c) : '\0');
}

/**
 * cmp_nums - Compares the left number to the.
 * @left: The left number to compare.
 * @right: The right number to compare.
 *
 * Return: 1 if left is > right, -1 if left < right, otherwise 0.
 */
char cmp_nums(char *left, char *right)
{
	char *num1_opt = left;
	char *num2_opt = right;
	int len1_opt = str_len(num1_opt) - 1, len2 = str_len(num2_opt) - 1, i = 0;

	for (i = 0; (*(num1_opt + i) == '0' && *(num1_opt + i + 1) != '\0') && i < len1_opt; i++)
		;
	num1_opt = num1_opt + i;
	len1_opt = str_len(num1_opt);
	for (i = 0; (*(num2_opt + i) == '0' && *(num2_opt + i + 1) != '\0') && i < len2; i++)
		;
	num2_opt = num2_opt + i;
	len2 = str_len(num2_opt);
	if (len1_opt > len2)
		return (1);
	else if (len1_opt < len2)
		return (-1);
	else
	{
		for (i = 0; i < len1_opt; i++)
		{
			if (*(num1_opt + i) > *(num2_opt + i))
				return (1);
			if (*(num1_opt + i) < *(num2_opt + i))
				return (-1);
		}
		return (0);
	}
}

/**
 * str_to_int - Converts a string to an int and returns.
 * @num: The string to convert to an int.
 *
 * Return: The converted number as an int.
 */
int str_to_int(char *num)
{
	int i = 1, len_ed, exp_e = 1;
	int res_e = 0;

	len_ed = str_len(num);
	for (i = len_ed - 1; i >= 0; i--)
	{
		if (*(num + i) == '-')
			res_e *= -1;
		else if (is_digit(*(num + i)))
		{
			res_e += (*(num + i) - '0') * exp_e;
			exp_e *= 10;
		}
	}
	return (res_e);
}

/**
 * bin_to_int - Converts an array of bits to an int and returns.
 * @bin_str: The array of bits to convert.
 *
 * Return: The decimal equivalent of the array of bits to convert..
 */
int bin_to_int(char *bin_str)
{
	int len_ed = str_len(bin_str);
	int i;
	int exp_e = 1;
	int resl = 0;

	for (i = len_ed - 1; i >= 0 && *(bin_str + i) != '\0'; i--)
	{
		if (*(bin_str + i) == '0' || *(bin_str + i) == '1')
		{
			resl += (*(bin_str + i) - '0') * exp_e;
			exp_e *= 2;
		}
	}
	return (resl);
}

/**
 * long_to_oct - Converts a long integer to its octal 
 * @num: The number to convert to an octal representation
 *
 * Return: The octal representation of the number.
 */
char *long_to_oct(unsigned long num)
{
	int i = 0, size = num == 0 ? 2 : 21;
	unsigned long num_c_s = num;
	char *string;

	string = malloc(sizeof(char) * (size));
	if (string)
	{
		mem_set(string, size, 0);
		if (num == 0)
		{
			*(string + i) = '0';
			return (string);
		}
		for (i = 0; i <= size; i++)
		{
			*(string + i) = (num_c_s % 8) + '0';
			num_c_s /= 8;
		}
		rev_string(string);
		string = trim_start(string, '0', TRUE);
		string = num == 0 ? str_cat("0", "", FALSE) : string;
	}
	return (string);
}
