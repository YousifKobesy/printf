#include <stdarg.h>
#include <stdlib.h>
#include <stdio.h>
#include "main.h"

/**
 * set_number - Retrieves a number from the given string and returns
 * @str: The string to retrieve the number from @str
 * @number: The pointer to the number   to retrieve
 *
 * Return: The number of positions that were moved from the string
 */
int set_number(const char *str, int *number)
{
	char digits_ed[11] = {0};
	int i, j = 0;

	for (i = 0; str && *(str + i) != '\0'; i++)
	{
		if (j < 10 && is_digit(*(str + i)))
		{
			digits_ed[j] = *(str + i);
			j++;
		}
		else
			break;
	}
	*number = cmp_nums(digits_ed, MAX_WIDTH) <= 0 ? str_to_int(digits_ed) : 0;
	return (i);
}

/**
 * set_length - Sets the length in a format info struct to the given length
 * @cur: The current character in the format info struct
 * @fmt_info: The pointer to the destination fmt_info_t struct that contains
 * @pos: The pointer to the current position in the format string struct
 */
void set_length(char cur, int *pos, fmt_info_t *fmt_info)
{
	fmt_info->is_long = cur == 'l' ? TRUE : fmt_info->is_long;
	fmt_info->is_short = cur == 'h' ? TRUE : fmt_info->is_short;
	(*pos)++;
}

/**
 * set_flags - Sets the flags in a format 
 * @str: The flag character string _flags
 * @fmt_info: The pointer to stination fmt_info_t struct
 *
 * Return: The number of s that were read
 */
int set_flags(const char *str, fmt_info_t *fmt_info)
{
	int i = 0;

	while (*(str + i) != '\0' && is_flag(*(str + i)))
	{
		fmt_info->space = *(str + i) == ' ' ? TRUE : fmt_info->space;
		fmt_info->left = *(str + i) == '-' || fmt_info->left ? TRUE : FALSE;
		fmt_info->show_sign = *(str + i) == '+' || fmt_info->show_sign
			? TRUE : FALSE;
		fmt_info->group = *(str + i) == '\'' || fmt_info->group ? TRUE : FALSE;
		fmt_info->alt = *(str + i) == '#' || fmt_info->alt ? TRUE : FALSE;
		fmt_info->pad = *(str + i) == '0' ? '0' : fmt_info->pad;
		i++;
	}
	return (i);
}

/**
 * set_precision - Reads a  data into the given struct
 * @str: The string  the format tokens
 * @args: The  list
 * @fmt_info:  pointer to the destination fmt_info_t struct
 * @i: The  to the position in the format string
 * @error_status: The  to the error variable
 */
void set_precision(const char *str, va_list args,
	fmt_info_t *fmt_info, int *i, int *error_status)
{
	fmt_info->is_precision_set = TRUE;
	if (*(str + *i) == '*')
	{
		fmt_info->prec = va_arg(args, int);
		(*i)++;
	}
	else if (is_digit(*(str + *i)))
		*i += set_number(str + *i, &(fmt_info->prec));
	else if (is_specifier(*(str + *i)))
	{
		fmt_info->prec = 0;
		/* (*i)--; */
	}
	else
		*error_status = -1;
}

/**
 * read_format_info - Reads a format info data into the 
 * @str: The string contained the 
 * @args: The arguments list
 * @fmt_info: The pointer estination fmt_info_t struct
 * @last_token:  the last token from the format specifier
 *
 * Return: umber of positions to skip after the format character (%)
 * , this s negative when there's an error
 */
int read_format_info(const char *str, va_list args,
	fmt_info_t *fmt_info, int *last_token)
{
	int i = 0, no_error_ed = 1, order_ed = 0;

	init_format_info(fmt_info);
	for (; str && *(str + i) != '\0' && !fmt_info->spec && no_error_ed == 1;)
	{
		if (is_flag(*(str + i)) && order_ed < 1)
			i += set_flags(str + i, fmt_info), order_ed = 1;
		else if ((is_digit(*(str + i)) || *(str + i) == '*') && order_ed < 2)
		{
			if (*(str + i) == '*')
				fmt_info->width = va_arg(args, int), i++;
			else
			{
				i += set_number(str + i, &(fmt_info->width));
			}
			fmt_info->is_width_set = TRUE, order_ed = 2;
		}
		else if (*(str + i) == '.' && order_ed < 3)
		{
			i++;
			set_precision(str, args, fmt_info, &i, &no_error_ed), order_ed = 3;
		}
		else if (is_length(*(str + i)) && order_ed < 4)
			set_length(*(str + i), &i, fmt_info), order_ed = 4;
		else if (is_specifier(*(str + i)) && order_ed < 5)
		{
			fmt_info->spec = *(str + i), i++, order_ed = 5;
			break;
		}
		else
		{
			no_error_ed = -1;
		}
	}
	*last_token = order_ed;
	return (i - 1);
}
