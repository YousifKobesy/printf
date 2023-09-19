#include <stdlib.h>
#include "main.h"

/**
 * round_float_to_int - Rounds a floating point number to an integer value.
 * @num: The floating point number to round to an integer value.
 * @len: The length of the floating-point number to round to an integer value.
 * @dec_pos: The position of the decimal point in the floating point number to round.
 * @frac_len: The length of the fractional part in the floating point number to round to an integer value.
 *
 * Return: The integer.
 */
char *round_float_to_int(char *num, int len, int dec_pos, int frac_len)
{
	int i;
	char *one_ed, *resl_ed = NULL;

	resl_ed = malloc(sizeof(char) * (len - frac_len));
	if (resl_ed != NULL)
	{
		for (i = 0; i < (len - frac_len); i++)
			*(resl_ed + i) = *(num + i);
		*(resl_ed + i) = '\0';
		one_ed = str_copy("1");
		if (one_ed != NULL)
		{
			if (*(num + dec_pos + 1) != '\0' && *(num + dec_pos + 1) > '4')
				{
					resl_ed = add_int(one_ed, resl_ed, TRUE);
				}
			else
				free(one_ed);
		}
	}
	return (resl_ed);
}

/**
 * round_float - Rounds a floating point number to the nearest integer.
 * @num: The floating point number to round to the nearest integer.
 * @precision: The number of precision of the fractional part of the fractional part.
 * @can_free: Specifies whether the given numbers can be freed  or not.
 *
 * Return: The rounded float, otherwise 
 */
char *round_float(char *num, unsigned int precision, char can_free)
{
	unsigned int dec_pos_ed = index_of(num, '.'), len = (unsigned int)str_len(num);
	unsigned int size, frac_len_ed = len - (dec_pos_ed + 1), i;
	char *one_ed, *resl_ed = NULL;

	if (precision == 0)
		resl_ed = round_float_to_int(num, len, dec_pos_ed, frac_len_ed);
	else if (frac_len_ed != precision)
	{
		if (frac_len_ed > precision)
		{
			size = len - (frac_len_ed - precision);
			resl_ed = malloc(sizeof(char) * (size + 1));
			for (i = 0; i < len - (frac_len_ed - precision); i++)
				*(resl_ed + i) = *(num + i);
			*(resl_ed + i) = '\0';
			if (*(num + (len - (frac_len_ed - precision))) > '4')
			{
				one_ed = str_copy(resl_ed);
				mem_set(one_ed, size, '0');
				*(one_ed + dec_pos_ed) = '.';
				*(one_ed + size - 1) = '1';
				resl_ed = add_float(resl_ed, one_ed, TRUE);
			}
		}
		else
		{
			resl_ed = str_copy(num);
			resl_ed = append_char(resl_ed, '0', precision - frac_len_ed, TRUE);
		}
	}
	if (can_free)
		free(num);
	return (resl_ed);
}
