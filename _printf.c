#include <stdarg.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "main.h"

/**
 * _printf - produces output according to a format specified by.
 * @format: The specified format string.
 *
 * Return: The number of characters that were .
 */
int _printf(const char *format, ...)
{
	int i = 0, tmp_ed, processing_ed = FALSE, err = 1, last_tok_ed;
	fmt_info_t fmt_info_ed;
	va_list args_ed;

	if (!format || (format[0] == '%' && format[1] == '\0'))
		{
			return (-1);
		}
	va_start(args_ed, format);
	write_to_buffer(0, -1);
	for (i = 0; format && *(format + i) != '\0'; i++)
	{
		if (processing_ed)
		{
			tmp_ed = read_format_info(format + i, args_ed, &fmt_info_ed, &last_tok_ed);
			processing_ed = FALSE;
			set_format_error(format, &i, tmp_ed, last_tok_ed, &err);
			if (is_specifier(fmt_info_ed.spec))
				{
					write_format(&args_ed, &fmt_info_ed);
				}
			i += (is_specifier(fmt_info_ed.spec) ? tmp_ed : 0);
		}
		else
		{
			if (*(format + i) == '%')
				{
					processing_ed = TRUE;
				}
			else
				{
					_putchar(*(format + i));
				}
		}
	}
	write_to_buffer(0, 1);
	va_end(args_ed);
	return (err <= 0 ? err : write_to_buffer('\0', -2));
}

/**
 * write_format - Writes data formatted against some parameters in the format.
 * @args_list: The arguments list of the format.
 * @fmt_info: The format info parameters that were read from the.
 */
void write_format(va_list *args_list, fmt_info_t *fmt_info)
{
	int i;
	spec_printer_t spec_printers_ed[] = {
		{'%', convert_fmt_percent},
		{'p', convert_fmt_p},
		{'c', convert_fmt_c},
		{'s', convert_fmt_s},
		{'d', convert_fmt_di},
		{'i', convert_fmt_di},
		{'X', convert_fmt_xX},
		{'x', convert_fmt_xX},
		{'o', convert_fmt_o},
		{'u', convert_fmt_u},
		/* #begin custom specifiers */
		{'b', convert_fmt_b},
		{'R', convert_fmt_R},
		{'r', convert_fmt_r},
		{'S', convert_fmt_S},
		/* #end */
		{'F', convert_fmt_fF},
		{'f', convert_fmt_fF},
	};

	for (i = 0; i < 23 && spec_printers_ed[i].spec != '\0'; i++)
	{
		if (fmt_info->spec == spec_printers_ed[i].spec)
		{
			spec_printers_ed[i].print_arg(args_list, fmt_info);
			break;
		}
	}
}

/**
 * _putstr - writes the given string to the buffer pointed to by.
 * @str: The string to write to the buffer pointed to by.
 *
 * Return: On success 1 on success, 0 on failure.
 * On error, -1 is returned, and errno is set .
 */
int _putstr(char *str)
{
	int i, out_ed;

	for (i = 0; str && *(str + i) != 0; i++)
		out_ed = _putchar(*(str + i));
	return (out_ed);
}

/**
 * _putchar - writes the character c to the buffer pointed to.
 * @c: The character to print   string pointed.
 *
 * Return: On success 1 and.
 * On error, -1 is returned, and errno is set .
 */
int _putchar(char c)
{
	return (write_to_buffer(c, 0));
}

/**
 * write_to_buffer - Writes a char to the buffer based on an .
 * @c: The character to write and .
 * @action: The action (
 * -1-> reset the static variables s
 * 0-> write char to buffer s
 * 1-> don't write character to buffer but empty buffer onto stdout d
 * -2-> the number of characters written to stdout
 * )
 *
 * Return: On success 1 and.
 * On error, -1 is returned, and errno is set .
 */
int write_to_buffer(char c, char action)
{
	static int i;
	static int chars_coun_ed;
	static char buf_ed[1024];
	static char out_ed;

	if (i < 1024 && action == 0)
	{
		out_ed = chars_coun_ed < 1 ? 1 : out_ed;
		buf_ed[i] = c;
		i++;
		chars_coun_ed++;
	}
	if (i >= 1024 || action == 1)
	{
		out_ed = write(1, buf_ed, i);
		fflush(stdout);
		i = 0;
		mem_set(buf_ed, 1024, 0);
	}
	if (action == -1)
	{
		i = 0;
		chars_coun_ed = 0;
		mem_set(buf_ed, 1024, 0);
	}
	if (action == -2)
	{
		return (chars_coun_ed);
	}
	return (out_ed);
}
