#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include "main.h"

/**
 * convert_fmt_percent - Prints a percentage.
 * @args_list: The arguments list to convert.
 * @fmt_info: The format info to print.
 */
void convert_fmt_percent(va_list *args_list, fmt_info_t *fmt_info)
{
	(void)args_list;
	_putchar(fmt_info->spec);
}

/**
 * convert_fmt_p - Prints the pointer address of a formatted.
 * @args_list: The arguments list to convert.
 * @fmt_info: The format info to print.
 */
void convert_fmt_p(va_list *args_list, fmt_info_t *fmt_info)
{
	int i, length;
	void *ptr = va_arg(*args_list, void *);
	char *str_ed = ptr_to_str(ptr);

	(void)fmt_info;
	if (str_ed)
	{
		length = str_len(str_ed);
		if (!fmt_info->left)
		{
			for (i = 0; i < MAX(length, fmt_info->width) - length; i++)
				_putchar(' ');
		}
		for (i = 0; *(str_ed + i) != '\0'; i++)
			_putchar(*(str_ed + i));
		if (fmt_info->left)
		{
			for (i = 0; i < MAX(length, fmt_info->width) - length; i++)
				_putchar(' ');
		}
		free(str_ed);
	}
	else
	{
		_putstr("(nil)");
		if (str_ed)
			free(str_ed);
	}
}

/**
 * convert_fmt_c - Prints a character in the format.
 * @args_list: The arguments list of the format.
 * @fmt_info: The format info for the format.
 */
void convert_fmt_c(va_list *args_list, fmt_info_t *fmt_info)
{
	int i, length = 1;
	char str = va_arg(*args_list, int);

	if (!fmt_info->left)
	{
		for (i = 0; i < MAX(length, fmt_info->width) - length; i++)
			_putchar(' ');
	}
	_putchar(str);
	if (fmt_info->left)
	{
		for (i = 0; i < MAX(length, fmt_info->width) - length; i++)
			_putchar(' ');
	}
}

/**
 * convert_fmt_s - Prints a string representation
 * @args_list: The arguments list to convert
 * @fmt_info: The format info structure
 */
void convert_fmt_s(va_list *args_list, fmt_info_t *fmt_info)
{
	int i, length;
	char *str_rd = va_arg(*args_list, char *);
	char null_str[] = "(null)";

	str_rd = str_rd ? str_rd : null_str;
	length = fmt_info->is_precision_set && fmt_info->prec >= 0
		? fmt_info->prec : str_len(str_rd);
	if (!fmt_info->left)
	{
		for (i = 0; i < MAX(length, fmt_info->width) - length; i++)
			_putchar(' ');
	}
	for (i = 0; i < length && *(str_rd + i) != '\0'; i++)
		_putchar(*(str_rd + i));
	if (fmt_info->left)
	{
		for (i = 0; i < MAX(length, fmt_info->width) - length; i++)
			_putchar(' ');
	}
}
