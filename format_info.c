#include <stdlib.h>
#include "main.h"

/**
 * init_format_info - initializes a format info struct with the.
 * @spec: The format info to initialize the format info struct.
 */
void init_format_info(fmt_info_t *spec)
{

	if (spec)
	{
		spec->prec = 1;
		spec->width = 0;
		spec->spec = FALSE;
		spec->is_long_double = FALSE;
		spec->is_long_long = FALSE;
		spec->is_long = FALSE;
		spec->is_short = FALSE;
		spec->is_char = FALSE;
		spec->is_precision_set = FALSE;
		spec->is_width_set = FALSE;
		spec->alt = FALSE;
		spec->space = FALSE;
		spec->left = FALSE;
		spec->show_sign = FALSE;
		spec->group = FALSE;
		spec->pad = ' ';
	}
}


/**
 * new_format_info - Creates a new format info structure and.
 *
 * Return: The pointer to the newly created format.
 */
fmt_info_t *new_format_info()
{
	fmt_info_t *spec_ed;

	spec_ed = malloc(sizeof(fmt_info_t));
	if (spec_ed)
		init_format_info(spec_ed);
	return (spec_ed);
}

/**
 * new_float_info - Creates a new float_info struct and it.
 * @exponent_size: The number of bits in the exponent and.
 * @mantissa_size: The number of bits in the mantissa and it.
 *
 * Return: The pointer to the newly created struct, otherwise NULL
 */
float_info_t *new_float_info(ushort_t exponent_size, ushort_t mantissa_size)
{
	float_info_t *float_info_ed;

	float_info_ed = malloc(sizeof(float_info_t));
	if (float_info_ed != NULL)
	{
		float_info_ed->exponent = malloc(sizeof(char) * (exponent_size + 1));
		if (float_info_ed->exponent == NULL)
			free(float_info_ed);
		float_info_ed->mantissa = malloc(sizeof(char) * (mantissa_size + 1));
		if (float_info_ed->mantissa == NULL)
		{
			free(float_info_ed->exponent);
			free(float_info_ed);
		}
	}
	return (float_info_ed);
}

/**
 * free_float_info - Frees the memory allocated to.
 * @flt_info: The pointer to free the memory allocated.
 */
void free_float_info(float_info_t *flt_info)
{
	if (flt_info != NULL)
	{
		if (flt_info->exponent != NULL)
			{
				free(flt_info->exponent);
			}
		if (flt_info->mantissa != NULL)
			{
				free(flt_info->mantissa);
			}
		free(flt_info);
	}
}
