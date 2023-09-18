#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include "main.h"

/**
 * convert_fmt_fF - Prints the decimal representation of a double to stdout.
 * @args_list: The arguments list to convert.
 * @fmt_info: The format info to print to stdout.
 *
 * Return: The number of characters written
 */
void convert_fmt_fF(va_list *args_list, fmt_info_t *fmt_info)
{
	int i, len_s, num_len_ed, zeros_count_ed, max_w_ed;
	double num_ed = va_arg(*args_list, double);
	char *str_ed, has_sign_ed = (fmt_info->show_sign && num_ed >= 0) || num_ed < 0;
	ushort_t exp_size_ed = fmt_info->is_long_double ? 15 : 11;
	ushort_t mant_size_ed = fmt_info->is_long_double ? 64 : 52;
	float_info_t *flt_info;

	flt_info = new_float_info(exp_size_ed, mant_size_ed);
	if (flt_info != NULL)
	{
		set_float_parts(num_ed, exp_size_ed, mant_size_ed, flt_info);
		str_ed = is_invalid(flt_info);
		if (str_ed == NULL)
		{
			str_ed = float_to_str(flt_info, FALSE);
			str_ed = round_float(str_ed, fmt_info->is_precision_set ? fmt_info->prec : 6, T);
			num_len_ed = str_len(str_ed) + ((fmt_info->show_sign && num_ed >= 0) ? 1 : 0);
			max_w_ed = MAX(fmt_info->width, num_len_ed);
			zeros_count_ed = (max_w_ed - num_len_ed) * !fmt_info->left * (fmt_info->pad == '0');
			len_s = max_w_ed - (zeros_count_ed + num_len_ed);
			for (i = 0; !fmt_info->left && i < len_s; i++)
				_putchar(' ');
			if (has_sign_ed)
				_putchar(num_ed < 0 ? '-' : '+');
			for (i = 0; !fmt_info->left && i < zeros_count_ed; i++)
				_putchar('0');
			for (i = has_sign_ed ? 1 : 0; *(str_ed + i) != '\0'; i++)
				_putchar(*(str_ed + i));
			for (i = 0; fmt_info->left && i < len_s; i++)
				_putchar(' ');
		}
		else
		{
			for (i = 0; i < str_len(str_ed); i++)
				_putchar(fmt_info->spec == 'f' ? TO_LOWER(str_ed[i]) : TO_UPPER(str_ed[i]));
		}
		if (str_ed != NULL)
			free(str_ed);
		free_float_info(flt_info);
	}
}
