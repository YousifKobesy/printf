#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include "main.h"

/**
 * convert_fmt_di - Prints a signed integer to stdout.
 * @args_list: The arguments list to convert
 * @fmt_info: The format info to print.
 *
 * Return: The number of characters writte.
 */
void convert_fmt_di(va_list *args_list, fmt_info_t *fmt_info)
{
	int i, len_ed = 0, zeros_count_ed = 0, num_len_ed;
	long num_ed;
	char *str, inv_plus_ed;

	if (fmt_info->is_long)
		num_ed = va_arg(*args_list, long);
	else if (fmt_info->is_short)
		num_ed = (short)va_arg(*args_list, long);
	else
		{
			num_ed = va_arg(*args_list, int);
		}
	str = long_to_str(num_ed);
	if (str)
	{
		inv_plus_ed = num_ed >= 0 && (fmt_info->show_sign || fmt_info->space) ? 1 : 0;
		if (fmt_info->is_precision_set && !fmt_info->prec && !num_ed)
			print_repeat(' ', fmt_info->width);
		else
		{
			num_len_ed = str_len(str) + (inv_plus_ed ? 1 : 0);
			if (fmt_info->is_precision_set)
				zeros_count_ed = MAX(fmt_info->prec + (inv_plus_ed || num_ed < 0 ? 1 : 0),
					num_len_ed) - num_len_ed;
			else
				zeros_count_ed = fmt_info->pad == '0' ? MAX(fmt_info->width,
					num_len_ed) - num_len_ed : 0;
			if (fmt_info->is_width_set)
				len_ed = (MAX(fmt_info->width, num_len_ed) - num_len_ed) - zeros_count_ed;
			for (i = 0; !fmt_info->left && i < len_ed; i++)
				_putchar(' ');
			if (num_ed < 0 || inv_plus_ed)
				_putchar(num_ed < 0 ? '-'
					: (fmt_info->space && !fmt_info->show_sign ? ' ' : '+'));
			put_num(zeros_count_ed, num_ed, str);
			for (i = 0; fmt_info->left && i < len_ed; i++)
				_putchar(' ');
		}
		free(str);
	}
}

/**
 * convert_fmt_xX - Prints the hexadecimal format of an.
 * @args_list: The arguments .
 * @fmt_info: The format info to convert.
 *
 * Return: The number of written
 */
void convert_fmt_xX(va_list *args_list, fmt_info_t *fmt_info)
{
	int i, len = 0, zeros_count_ed = 0, max_w_ed, max_p_ed, num_len_ed;
	unsigned long num;
	char *str_ed;

	if (fmt_info->is_short)
		{
			num = (va_arg(*args_list, unsigned long) << 2 * 8) >> 2 * 8;
		}
	else if (fmt_info->is_long)
		{
			num = va_arg(*args_list, unsigned long);
		}
	else
		num = va_arg(*args_list, unsigned int);
	str_ed = u_long_to_hex(num, fmt_info->spec == 'X');
	if (str_ed)
	{
		if (fmt_info->is_precision_set && !fmt_info->prec && !num)
			print_repeat(' ', fmt_info->width);
		else
		{
			num_len_ed = str_len(str_ed) + (num ? fmt_info->alt * 2 : 0);
			max_w_ed = MAX(fmt_info->width, num_len_ed), max_p_ed = MAX(fmt_info->prec, num_len_ed);
			zeros_count_ed = (max_p_ed - num_len_ed) * !fmt_info->left;
			len = max_w_ed - (NO_NEG(zeros_count_ed) + num_len_ed);
			for (i = 0; !fmt_info->left && i < len; i++)
				_putchar(fmt_info->pad);
			if (fmt_info->alt && num)
				_putstr(fmt_info->spec == 'X' ? "0X" : "0x");
			for (i = 0; i < zeros_count_ed; i++)
				_putchar('0');
			for (i = 0; *(str_ed + i) != '\0'; i++)
			{
				_putchar(*(str_ed + i));
			}
			for (i = 0; fmt_info->left && i < len; i++)
				_putchar(' ');
		}
		free(str_ed);
	}
}

/**
 * convert_fmt_o - Prints the octadecimal format of a ment.
 * @args_list: The arguments list of the format.
 * @fmt_info: The format info of the format.
 *
 * Return: The number of characters written in the format.
 */
void convert_fmt_o(va_list *args_list, fmt_info_t *fmt_info)
{
	int i = 0, zeros_count_ed = 0, num_len_ed = 0, len = 0, max_w_ed, max_p_ed;
	unsigned long num;
	char *str_ed;

	if (fmt_info->is_long)
		{
			num = va_arg(*args_list, unsigned long);
		}
	else if (fmt_info->is_short)
		{
		num = (va_arg(*args_list, unsigned long) << 2 * 8) >> 2 * 8;
		}
	else
		num = va_arg(*args_list, unsigned int);
	str_ed = long_to_oct(num);
	if (str_ed)
	{
		if (fmt_info->is_precision_set && !fmt_info->prec && !num)
			print_repeat(' ', fmt_info->width);
		else
		{
			num_len_ed = NO_LESS(str_len(str_ed), 1);
			max_w_ed = MAX(fmt_info->width, num_len_ed);
			max_p_ed = MAX(fmt_info->prec, num_len_ed);
			zeros_count_ed = (max_p_ed - num_len_ed) * !fmt_info->left;
			len = max_w_ed - (NO_NEG(zeros_count_ed) + num_len_ed);
			for (i = 0; !fmt_info->left && i < len; i++)
				_putchar(fmt_info->pad);
			if (fmt_info->alt && zeros_count_ed == 0 && num)
				_putchar('0');
			for (i = 0; i < zeros_count_ed; i++)
				_putchar('0');
			for (i = 0; *(str_ed + i) != '\0'; i++)
				_putchar(*(str_ed + i));
			for (i = 0; fmt_info->left && i < len; i++)
				_putchar(' ');
		}
		free(str_ed);
	}
}

/**
 * convert_fmt_u - Prints an unsigned integer in the format.
 * @args_list: The arguments list to convert.
 * @fmt_info: The format info to print to.
 */
void convert_fmt_u(va_list *args_list, fmt_info_t *fmt_info)
{
	int i, len = 0, zeros_count_ed = 0, num_len_ed;
	unsigned long num, max_w_ed, max_p_ed;
	char *str_ed;

	if (fmt_info->is_long)
		{
			num = va_arg(*args_list, unsigned long);
		}
	else if (fmt_info->is_short)
		{
			num = (va_arg(*args_list, unsigned int) << 2 * 8) >> 2 * 8;
		}
	else
		{
			num = va_arg(*args_list, unsigned int);
		}
	str_ed = u_long_to_str(num);
	if (str_ed)
	{
		if (FMT_PREC_EMPTY(fmt_info) && !num)
			print_repeat(' ', fmt_info->width);
		else
		{
			num_len_ed = str_len(str_ed);
			max_w_ed = MAX(fmt_info->width, num_len_ed);
			max_p_ed = MAX(fmt_info->prec, num_len_ed);
			zeros_count_ed = (max_p_ed - num_len_ed) * !fmt_info->left;
			len = max_w_ed - (NO_NEG(zeros_count_ed) + num_len_ed);
			for (i = 0; !fmt_info->left && i < len; i++)
				_putchar(fmt_info->pad);
			for (i = 0; i < zeros_count_ed; i++)
				_putchar('0');
			for (i = 0; *(str_ed + i) != '\0'; i++)
				_putchar(*(str_ed + i));
			for (i = 0; fmt_info->left && i < len; i++)
				_putchar(' ');
		}
		free(str_ed);
	}
}
