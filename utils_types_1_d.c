#include <stdio.h>
#include <stdlib.h>
#include "main.h"

/**
 * set_float_parts - Sets the float_info fields to th
 * \ parts of a given float
 * @num: The given float
 * @exponent_size: The number of bits in the  part
 * @mantissa_size: The number of bits in the  part
 * @float_info: The float_info struct
 */
void set_float_parts(double num,	uchar_t exponent_size,
	uchar_t mantissa_size, float_info_t *float_info)
{
	int i;
	char *str_d;
	uchar_t size = exponent_size + mantissa_size + 1;
	size_t tmp = *((size_t *)&num);

	if (float_info == NULL)
		return;
	str_d = malloc(sizeof(char) * (size + 1));
	if (str_d != NULL)
	{
		for (i = 0; i < size; i++)
			*(str_d + i) = ((tmp >> i) & 1)  + '0';
		*(str_d + size) = '\0';
		rev_string(str_d);
		float_info->sign = *str_d;
		for (i = 0; i < exponent_size; i++)
			*(float_info->exponent + i) = *(str_d + i + 1);
		*(float_info->exponent + i) = '\0';
		for (i = 0; i < mantissa_size; i++)
			*(float_info->mantissa + i) = *(str_d + i + exponent_size + 1);
		*(float_info->mantissa + i) = '\0';
		free(str_d);
	}
}

/**
 * mantissa_to_dec_fraction - Converts the mantissa of a float t
 * @mantissa: The mantissa to 
 * @frac_len: The maximum  of the decimal fraction
 *
 * Return: The converted fraction
 */
char *mantissa_to_dec_fraction(char *mantissa, unsigned short frac_len)
{
	char *str_d, i, *pow2_d;
	int length = str_len(mantissa);

	str_d = malloc(sizeof(char) * (frac_len + 3));
	if (str_d != NULL)
	{
		mem_set(str_d, frac_len + 2, '0');
		*(str_d + 1) = '.';
		*(str_d + frac_len + 2) = '\0';
		for (i = 0 - 1; i >= 0 - length; i--)
		{
			if (*(mantissa + ABS(i) - 1) == '1')
			{
				pow2_d = two_exp(i);
				str_d = add_float(pow2_d, str_d, TRUE);
			}
		}
	}
	return (str_d);
}

/**
 * float_to_str - Converts an IEEE 754 float to its string 
 * @flt_info: The information about the fl
 * @can_free: Specifies whether the numbers can be freed
 *
 * Return: The string  of the float, otherwise NULL
 */
char *float_to_str(float_info_t *flt_info, char can_free)
{
	uchar_t exponent_size_d = str_len(flt_info->exponent);
	short bias_d = two_pexp(exponent_size_d) / 2 - 1, exponent;
	char *power_d, *fract, *product_d, *float_num_d, *pow_frac_dd;
	unsigned short frac_len = 22;/* Only doubles are supported */

	exponent = bin_to_int(flt_info->exponent) - bias_d;
	power_d = two_exp(exponent);
	fract = mantissa_to_dec_fraction(flt_info->mantissa, frac_len);
	fract[0] = '1';
	if (exponent >= 0)
	{
		pow_frac_dd = malloc(sizeof(char) * 3);
		if (pow_frac_dd)
		{
			*(pow_frac_dd + 0) = '.';
			*(pow_frac_dd + 1) = '0';
			*(pow_frac_dd + 2) = '\0';
			power_d = str_cat(power_d, pow_frac_dd, TRUE);
		}
	}
	product_d = mul_float(fract, power_d, TRUE);
	float_num_d = str_cat(flt_info->sign == '1' ? "-" : "", product_d, FALSE);
	free(product_d);
	if (can_free)
		free_float_info(flt_info);
	return (float_num_d);
}
