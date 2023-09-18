#include <stdarg.h>
#include <stdlib.h>
#include "main.h"

/**
 * convert_fmt_b - Prints the binary format of an .
 * @args_list: The arguments list to convert.
 * @fmt_info: The format info to print.
 */
void convert_fmt_b(va_list *args_list, fmt_info_t *fmt_info)
{
	int i, size_ed = 32, len_ed = 0;
	unsigned int num_ed = va_arg(*args_list, unsigned int), tmp_ed;
	char *str_ed;

	str_ed = malloc(sizeof(char) * (size_ed + 1));
	if (str_ed)
	{
		mem_set(str_ed, size_ed, '\0');
		tmp_ed = num_ed;
		for (i = 0; i < size_ed && tmp_ed > 0; i++, len_ed++)
		{
			*(str_ed + i) = (tmp_ed % 2) + '0';
			tmp_ed /= 2;
		}
		if (!fmt_info->left)
			for (i = 0; i < MAX(len_ed, fmt_info->width) - len_ed; i++)
				_putchar(fmt_info->pad);
		for (i = size_ed - 1; i >= 0; i--)
			if (*(str_ed + i) != '\0')
				_putchar(*(str_ed + i));
		if (num_ed == 0)
			{
			_putchar('0');
			}
		if (fmt_info->left)
		{
			for (i = 0; i < MAX(len_ed, fmt_info->width) - len_ed; i++)
				_putchar(' ');
		}
	}
}

/**
 * convert_fmt_S - Prints a string and the.
 * \ non-printable characters are ignored.
 * @args_list: The arguments list to print.
 * @fmt_info: The format info to print.
 *
 * Return: The number of characters written to the output.
 */
void convert_fmt_S(va_list *args_list, fmt_info_t *fmt_info)
{
	int i, len_ed;
	char *str_ed = va_arg(*args_list, char *);

	if (str_ed)
	{
		len_ed = str_len(str_ed);
		if (!fmt_info->left)
			for (i = 0; i < MAX(len_ed, fmt_info->width) - len_ed; i++)
				_putchar(fmt_info->pad);
		for (i = 0; *(str_ed + i) != '\0'; i++)
		{
			if (*(str_ed + i) < 32 || *(str_ed + i) >= 127)
			{
				_putchar('\\');
				_putchar('x');
				_putchar(TO_UPPER(hex_digit(*(str_ed + i) / 16)));
				_putchar(TO_UPPER(hex_digit(*(str_ed + i) % 16)));
			}
			else
				_putchar(*(str_ed + i));
		}
		if (fmt_info->left)
			for (i = 0; i < MAX(len_ed, fmt_info->width) - len_ed; i++)
				_putchar(fmt_info->pad);
	}
	else
	{
		_putstr("(null)");
	}
}

/**
 * convert_fmt_R - Prints the rot13'ed string to the.
 * @args_list: The arguments list to convert.
 * @fmt_info: The format info to print.
 *
 * Return: The number of characters written to the output.
 */
void convert_fmt_R(va_list *args_list, fmt_info_t *fmt_info)
{
	int i, len_ed, is_low_1, is_low_2, is_upper, is_lower;
	char *str_ed = va_arg(*args_list, char *);

	if (str_ed)
	{
		len_ed = str_len(str_ed);
		if (!fmt_info->left)
			for (i = 0; i < MAX(len_ed, fmt_info->width) - len_ed; i++)
				_putchar(fmt_info->pad);
		for (i = 0; str_ed && *(str_ed + i) != '\0'; i++)
		{
			is_low_1 = *(str_ed + i) >= 'a' && *(str_ed + i) <= 'm';
			is_low_2 = *(str_ed + i) >= 'A' && *(str_ed + i) <= 'M';
			is_upper = *(str_ed + i) >= 'A' && *(str_ed + i) <= 'Z';
			is_lower = *(str_ed + i) >= 'a' && *(str_ed + i) <= 'z';

			if (is_lower || is_upper)
            {
				_putchar(((is_low_1 + is_low_2) * (*(str_ed + i) + 13))
					+ ((1 - is_low_1 - is_low_2) * (*(str_ed + i) - 13)));
			}
			else
				_putchar(*(str_ed + i));
		}
		if (fmt_info->left)
			for (i = 0; i < MAX(len_ed, fmt_info->width) - len_ed; i++)
				_putchar(fmt_info->pad);
	}
}

/**
 * convert_fmt_r - Prints the reversed string or.
 * @args_list: The arguments list or.
 * @fmt_info: The format info and.
 *
 * Return: The number of characters written
 */
void convert_fmt_r(va_list *args_list, fmt_info_t *fmt_info)
{
	int i, len_ed;
	char *str_ed = va_arg(*args_list, char *);

	if (str_ed)
	{
		len_ed = str_len(str_ed);
		if (!fmt_info->left)
			for (i = 0; i < MAX(len_ed, fmt_info->width) - len_ed; i++)
				_putchar(fmt_info->pad);
		for (i = len_ed - 1; i >= 0; i--)
		{
			_putchar(*(str_ed + i));
		}
		if (fmt_info->left)
		{
			for (i = 0; i < MAX(len_ed, fmt_info->width) - len_ed; i++)
				_putchar(fmt_info->pad);
		}
	}
}
