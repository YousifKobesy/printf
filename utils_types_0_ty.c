#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include "main.h"

/**
 * u_long_to_str - Converts an unsigned long to  representation
 * @num: The unsigned long integer to convert
 *
 * Return: The string representation of nsigned long integer
 */
char *u_long_to_str(unsigned long num)
{
	char *str_ed;
	unsigned long rem_ed = num;
	char size_ss = 20, j;

	str_ed = malloc(sizeof(char) * (size_ss + 1));
	if (str_ed)
	{
		*(str_ed + size_ss) = '\0';
		mem_set(str_ed, size_ss, '0');
		j = size_ss - 1;
		while (rem_ed > 0)
		{
			*(str_ed + j) = (rem_ed % 10) + '0';
			rem_ed /= 10;
			j--;
		}
		str_ed = trim_start(str_ed, '0', TRUE);
		str_ed = num == 0 ? str_cat("0", "", FALSE) : str_ed;
	}
	return (str_ed);
}

/**
 * long_to_str - Converts a long to its string 
 * @num: The long integer to convert
 *
 * Return: The string  of the long integer
 */
char *long_to_str(long num)
{
	char *str_ed;
	long rem_ed = num;
	char sign_ed = rem_ed < 0 ? -1 : 1;
	char size_ss = 20, j;

	str_ed = malloc(sizeof(char) * (size_ss + 1));
	if (str_ed)
	{
		*(str_ed + size_ss) = '\0';
		mem_set(str_ed, size_ss, '0');
		j = size_ss - 1;
		if (rem_ed == 0)
		{
			*(str_ed + j) = '0';
		}
		while ((sign_ed == -1 && rem_ed < 0) || (sign_ed == 1 && rem_ed > 0))
		{
			*(str_ed + j) = (rem_ed % 10) * sign_ed + '0';
			rem_ed /= 10;
			j--;
		}
		if (sign_ed < 0)
			*(str_ed + j) = '-';
		str_ed = trim_start(str_ed, '0', TRUE);
		str_ed = num == 0 ? str_cat("0", "", FALSE) : str_ed;
	}
	return (str_ed);
}

/**
 * ptr_to_str - Converts a pointer to its string 
 * @ptr: The  pointer to be converted.
 *
 * Return: The string f the pointer
 */
char *ptr_to_str(void *ptr)
{
	int i, size_ss;
	uintptr_t tmep;
	char *str, *str0_ed;

	if (ptr)
	{
		tmep = (uintptr_t)ptr;
		size_ss = sizeof(ptr) * 2;
		str = malloc(sizeof(char) * (size_ss + 1));
		if (str)
		{
			str0_ed = malloc(sizeof(char) * (2 + 1));
			if (str0_ed)
			{
				mem_set(str, size_ss, '0');
				for (i = 0; i < size_ss; i++)
				{
					*(str + i) = (tmep % 16) < 10 ? (tmep % 16) + '0'
						: (tmep % 16) - 10 + 'a';
					tmep /= 16;
				}
				*(str + i) = '\0';
				*(str0_ed + 0) = '0';
				*(str0_ed + 1) = 'x';
				*(str0_ed + 2) = '\0';
				rev_string(str);
				str = trim_start(str, '0', TRUE);
				str = *str == '\0' ? str_cat("0", "", FALSE) : str;
				str = str_cat(str0_ed, str, TRUE);
			}
			if (!str0_ed)
			{
				free(str);
			}
		}
	}
	else
		str = str_copy("(nil)");
	return (str);
}

/**
 * is_invalid - Checks if a given float is invalid and returns
 * @flt_info: The float info struct to check the validity of
 *
 * Return: NULL if it is valid, otherwise inf or nan if it is
 */
char *is_invalid(float_info_t *flt_info)
{
	uchar_t exp_bits_on_ed = 0, exp_all_on_d;
	short mant_bits_on = 0;
	char lsb_on = FALSE, msb_on = FALSE;
	int i;

	if (flt_info != NULL)
	{
		for (i = 0; *(flt_info->exponent + i) != '\0'; i++)
		{
			if (*(flt_info->exponent + i) == '1')
			{
				exp_bits_on_ed++;
			}
		}
		exp_all_on_d = i == exp_bits_on_ed;
		for (i = 0; *(flt_info->mantissa + i) != '\0'; i++)
		{
			msb_on = i == 0 && *(flt_info->mantissa + i) == '1' ? TRUE : msb_on;
			lsb_on = *(flt_info->mantissa + i + 1) == '\0'
				&& *(flt_info->mantissa + i) == '1' ? TRUE : lsb_on;
			if (*(flt_info->mantissa + i) == '1')
			{
				mant_bits_on++;
			}
		}
		if (exp_all_on_d)
		{
			if ((flt_info->sign == '0' && mant_bits_on == 0)
				|| (flt_info->sign == '1' && mant_bits_on == 0))
			{
				return (str_copy("inf"));
			}
			else if ((flt_info->sign == '0' && mant_bits_on == 1 && lsb_on)
				|| (flt_info->sign == '0' && mant_bits_on == 2 && lsb_on && msb_on)
				|| (flt_info->sign == '0' && mant_bits_on == i))
			{
				return (str_copy("nan"));
			}
		}
	}
	return (NULL);
}
