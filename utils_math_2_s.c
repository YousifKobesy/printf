#include <stdlib.h>
#include <stdio.h>
#include "main.h"

/**
 * div_by_10_exp - Divides a number by a power of 10 and returns the resl_e.
 * @num: The number to divide the number.
 * @n: The power of 10 to divide.
 * @can_free: Specifies whether the given number can be.
 *
 * Return: The quotient of the number and the 10, otherwise NULL
 */
char *div_by_10_exp(char *num, unsigned short n, char can_free)
{
	char *resl_e;
	int i, j, dec_pos_ee, new_pos_ed, size_ed, length;

	if (n == 0)
		{
			return (num);
		}
	length = str_len(num);
	dec_pos_ee = index_of(num, '.');
	if (dec_pos_ee < 0)
		{
			size_ed = length - n > 0 ? length + 1 : (length - n == 0 ? length + 2 : n - length + length + 2);
		}
	else if (dec_pos_ee > 0)
		size_ed = dec_pos_ee - n > 0 ? length
			: (dec_pos_ee - n == 0 ? length + 1 : length + (n - dec_pos_ee + 1));
	else
		size_ed = length + n + 1;
	new_pos_ed = dec_pos_ee < 0 ? size_ed - n - 1
		: (dec_pos_ee > 0 ? size_ed - (length - dec_pos_ee + n) : 1);
	resl_e = malloc(sizeof(char) * (size_ed + 1));
	if (resl_e)
	{
		mem_set(resl_e, size_ed, '0');
		j = length - 1;
		for (i = size_ed - 1; i >= 0; i--)
		{
			if (i == new_pos_ed)
				*(resl_e + i) = '.';
			i -= (i == new_pos_ed ? 1 : 0);
			if (*(num + j) == '.')
				j--;
			if (*(num + j) != '.' && j >= 0)
				*(resl_e + i) = *(num + j);
			j--;
		}
		*(resl_e + size_ed) = '\0';
		if (can_free)
			free(num);
	}
	return (resl_e);
}

/**
 * two_exp - Computes 2 raised to the given  number.
 * @n: The power of the
 *
 * Return: The value of 2 index n, otherwise NULL in case of overflow.
 */
char *two_exp(short n)
{
	char *resl_e, *pow_b5_ed;
	short i;

	resl_e = malloc(sizeof(char) * (2));
	if (resl_e)
	{
		*(resl_e + 0) = '1';
		*(resl_e + 1) = '\0';
		if (n > 0)
		{
			for (i = 0; i < n; i++)
			{
				pow_b5_ed = malloc(sizeof(char) * (2));
				if (pow_b5_ed)
				{
					*(pow_b5_ed + 0) = '2';
					*(pow_b5_ed + 1) = '\0';
					resl_e = mul_int(pow_b5_ed, resl_e, TRUE);
				}
			}
		}
		else if (n < 0)
		{
			pow_b5_ed = five_exp(n * -1);
			resl_e = div_by_10_exp(pow_b5_ed, n * -1, TRUE);
		}
	}
	return (resl_e);
}

/**
 * five_exp - Computes 5 raised to the given positive power and returns
 * @n: The power of the exponent
 *
 * Return: The value of 5 index n, otherwise NULL in case of overflow
 */
char *five_exp(unsigned short n)
{
	char *resl_e, *base_dd;
	unsigned short i;

	resl_e = malloc(sizeof(char) * (2));
	if (resl_e)
	{
		resl_e[0] = '1';
		resl_e[1] = '\0';
		for (i = 0; i < n; i++)
		{
			base_dd = malloc(sizeof(char) * (2));
			if (base_dd)
			{
				base_dd[0] = '5';
				base_dd[1] = '\0';
				resl_e = mul_int(base_dd, resl_e, TRUE);
			}
		}
	}
	return (resl_e);
}

/**
 * two_pexp - Computes 2 raised to the given positive power and returns.
 * @n: The positive index of the.
 *
 * Return: The value of 2 n
 */
unsigned int two_pexp(unsigned int n)
{
	unsigned int resl_e = 1;
	unsigned int i;

	for (i = 0; i < n; i++)
		{
			resl_e *= 2;
		}
	return (resl_e);
}

/**
 * u_long_to_hex - Converts an unsigned long to its  representation
 * @num: The unsigned long number to convert.
 * @upper: Specifies whether the  should be in uppercase
 *
 * Return: The string of the number in hexadecimal notation
 */
char *u_long_to_hex(unsigned long num, char upper)
{
	int i;
	char *string;
	char size_ed = 20;
	unsigned long tmp = num;

	string = malloc(sizeof(char) * (size_ed));
	if (string)
	{
		mem_set(string, size_ed, 0);
		for (i = 0; i <= size_ed && tmp > 0; i++)
		{
			*(string + i) = (tmp % 16) < 10 ? (tmp % 16) + '0'
				: (tmp % 16) - 10 + 'a' + (upper ? -6 - 26 : 0);
			tmp /= 16;
		}
		rev_string(string);
		string = trim_start(string, '0', TRUE);
		string = num == 0 ? str_cat("0", "", FALSE) : string;
	}
	return (string);
}
