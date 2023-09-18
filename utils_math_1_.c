#include <stdlib.h>
#include <stdio.h>
#include "main.h"

/**
 * multiply - Computes the product of a number and.
 * @num: The first number   to multiply.
 * @multiple: The second number.
 *
 * Return: A the result_ed, otherwise program fails
 */
char *multiply(char *num, char *multiple)
{
	int size_s, mult_len_ed, num_len_s, i, j;
	char *resl, rem_ed, carry_ed = 0;

	mult_len_ed = str_len(multiple);
	num_len_s = str_len(num);
	size_s = mult_len_ed + num_len_s;
	resl = malloc(sizeof(char) * (size_s + 1));
	if (resl != NULL)
	{
		mem_set(resl, size_s, '0');
		*(resl + size_s) = '\0';
		mult_len_ed--;
		j = size_s - mult_len_ed - 1;
		for (i = 1; i <= mult_len_ed; i++)
			{
				*(resl + size_s - i) = '0';
			}
		for (i = num_len_s - 1; i >= 0; i--)
		{
			if (!(*(num + i) >= '0' && *(num + i) <= '9'))
				break;
			if (!(*multiple >= '0' && *multiple <= '9'))
			{
				break;
			}
			rem_ed = ((*(num + i) - '0') * (*multiple - '0') + carry_ed) % 10;
			carry_ed = ((*(num + i) - '0') * (*multiple - '0') + carry_ed) / 10;
			*(resl + j) = rem_ed + '0';
			j--;
		}
		if (carry_ed > 0)
			*(resl + j) = carry_ed + '0';
		return (resl);
	}
	return (NULL);
}

/**
 * add_int - Adds two positive integersvss.
 * @left: The first number to be added.
 * @right: The second number to be added.
 * @can_free: Specifies whether the given be freed
 *
 * Return: The sum of the two, otherwise NULL
 */
char *add_int(char *left, char *right, int can_free)
{
	int i, size_ed, len1_ed, len2_ed;
	char dig1_ed, dig2_d, carry_ed, rem_ed, *result_ed;

	len1_ed = str_len(left);
	len2_ed = str_len(right);
	size_ed = MAX(len1_ed, len2_ed) + 1;
	result_ed = malloc(sizeof(char) * (size_ed + 1));
	if (result_ed)
	{
		mem_set(result_ed, size_ed, '0');
		carry_ed = 0;
		i = size_ed - 1;
		len1_ed--;
		len2_ed--;
		for (; i >= 0; i--)
		{
			dig1_ed = len1_ed >= 0 ? *(left + len1_ed) - '0' : 0;
			dig2_d = len2_ed >= 0 ? *(right + len2_ed) - '0' : 0;
			rem_ed = (dig1_ed + dig2_d + carry_ed) % 10;
			carry_ed = (dig1_ed + dig2_d + carry_ed) / 10;
			*(result_ed + i) = rem_ed + '0';
			len1_ed--;
			len2_ed--;
		}
		*(result_ed + size_ed) = '\0';
		result_ed = trim_start(result_ed, '0', TRUE);
		if (can_free)
		{
			free(left);
			free(right);
		}
	}
	return (result_ed);
}

/**
 * add_float - Adds two positive floating point numbers to the result.
 * @left: The first number to be added.
 * @right: The second number to be added.
 * @can_free: Specifies whether  numbers can be freed
 *
 * Return: The sum of the, otherwise NULL
 */
char *add_float(char *left, char *right, char can_free)
{
	int len1_ed, len2_ed, dec_pos1, dec_pos2, frac_len1_ed, frac_len2_ed, size_ed;
	int i, rem_ed, carry_ed, dig1_ed, dig2_d, dec_pos;
	char *sum, trim;

	for (len1_ed = 0; *(left + len1_ed) != '\0'; len1_ed++)
		{
			dec_pos1 = *(left + len1_ed) == '.' ? len1_ed : dec_pos1;
		}
	for (len2_ed = 0; *(right + len2_ed) != '\0'; len2_ed++)
		dec_pos2 = *(right + len2_ed) == '.' ? len2_ed : dec_pos2;
	frac_len1_ed = len1_ed - dec_pos1 - 1, frac_len2_ed = len2_ed - dec_pos2 - 1;
	dec_pos = frac_len1_ed > frac_len2_ed ? dec_pos1 : dec_pos2;
	size_ed = MAX(len1_ed, len2_ed) + 1, sum = malloc(sizeof(char) * (size_ed + 1));
	if (sum == NULL)
		{
			return (NULL);
		}
	mem_set(sum, size_ed, '0'), carry_ed = 0, len1_ed--, len2_ed--;
	for (i = size_ed - 1; i >= 0; i--)
	{
		frac_len1_ed = len1_ed - dec_pos1 - 1, frac_len2_ed = len2_ed - dec_pos2 - 1;
		dig1_ed = len1_ed > dec_pos1
			? ((len1_ed - dec_pos1 - 1) >= frac_len2_ed ? *(left + len1_ed) - '0' : 0)
			: ((len1_ed == dec_pos1) || (len1_ed < 0) ? 0 : *(left + len1_ed) - '0');
		len1_ed -= (len1_ed > dec_pos1
			? ((len1_ed - dec_pos1 - 1) >= frac_len2_ed ? 1 : 0)
			: (len2_ed <= dec_pos2 ? 1 : 0));
		dig2_d = len2_ed > dec_pos2
			? ((len2_ed - dec_pos2 - 1) >= frac_len1_ed ? *(right + len2_ed) - '0' : 0)
			: ((len2_ed == dec_pos2) || (len2_ed < 0) ? 0 : *(right + len2_ed) - '0');
		len2_ed -= (len2_ed > dec_pos2
			? ((len2_ed - dec_pos2 - 1) >= frac_len1_ed ? 1 : 0)
			: (len1_ed <= dec_pos1 ? 1 : 0));
		rem_ed = (dig1_ed + dig2_d + carry_ed) % 10, carry_ed = (dig1_ed + dig2_d + carry_ed) / 10;
		*(sum + i) = (i - 1 == dec_pos) ? '.' : rem_ed + '0';
	}
	*(sum + size_ed) = '\0';
	if ((can_free >> 0) & TRUE)
		{
			free(left);
		}
	if ((can_free >> 1) & TRUE)
		{
			free(right);
		}
	trim = (size_ed > 1) && (sum[0] == '0');
	return (trim ? sub_str(sum, 1, 01) : sum);
}

/**
 * mul_int - Computes the product of two positive integers and returns
 * @left: The first number to multiply
 * @right: The second number to multiply
 * @can_free: Specifies whether the  can be freed
 *
 * Return: The product of, otherwise NULL
 */
char *mul_int(char *left, char *right, char can_free)
{
	char *result_ed, *product;
	int size_ed, i, len2_ed;

	size_ed = str_len(left);
	len2_ed = str_len(right);
	size_ed += len2_ed;
	result_ed = malloc(sizeof(char) * (size_ed + 1));
	if (result_ed != NULL)
	{
		mem_set(result_ed, size_ed, '0');
		*(result_ed + size_ed) = '\0';
		for (i = 0; i < len2_ed; i++)
		{
			product = multiply(left, right + i);
			result_ed = add_int(product, result_ed, TRUE);
		}
		while (*result_ed == '0' && *(result_ed + 1) != '\0')
			{
				left_shift(result_ed, size_ed);
			}
		if (can_free)
		{
			free(left);
			free(right);
		}
	}
	return (result_ed);
}

/**
 * mul_float - Computes the product of two positive floats and returns
 * @left: The first number to multiply
 * @right: The second number to multiply
 * @can_free: Specifies whether the  numbers can be freed
 *
 * Return: The product of the, otherwise NULL
 */
char *mul_float(char *left, char *right, char can_free)
{
	char *left_c = str_copy(left);
	char *right_c = str_copy(right);
	int len1_ed, len2_ed, dec_pos1, dec_pos2, frac_len1_ed, frac_len2_ed, size_ed, old_size;
	char *product_ee;

	len1_ed = str_len(left_c);
	len2_ed = str_len(right_c);
	dec_pos1 = index_of(left_c, '.');
	dec_pos2 = index_of(right_c, '.');
	frac_len1_ed = len1_ed - (dec_pos1 + 1);
	frac_len2_ed = len2_ed - (dec_pos2 + 1);
	if (frac_len1_ed < frac_len2_ed)
		left_c = append_char(left_c, '0', frac_len2_ed - frac_len1_ed, TRUE);
	if (frac_len2_ed < frac_len1_ed)
		right_c = append_char(right_c, '0', frac_len1_ed - frac_len2_ed, TRUE);
	size_ed = MAX(len1_ed, len2_ed);
	product_ee = malloc(sizeof(char) * (size_ed + 1));
	if (product_ee)
	{
		mem_set(product_ee, size_ed, '0');
		left_c = delete_char(left_c, '.', TRUE);
		right_c = delete_char(right_c, '.', TRUE);
		old_size = size_ed - 1;
		product_ee = mul_int(left_c, right_c, TRUE);
		size_ed = str_len(product_ee) - old_size;
		product_ee = insert_char(product_ee,
			size_ed - MAX(frac_len1_ed, frac_len2_ed) + 1, '.', TRUE);
		product_ee = trim_end(product_ee, '0', TRUE);
		if (can_free)
		{
			free(left);
			free(right);
		}
	}
	return (product_ee);
}
