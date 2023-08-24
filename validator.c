#include "monty.h"

/**
 * is_valid_integer - Checks if a string is a valid integer.
 * @str: String to be checked.
 * Return: Returns 1 if valid integer, else 0.
 */

int is_valid_integer(const char *str)
{
	if (*str == '-' || *str == '+')
		str++;

	while (*str != '\0')
	{
		if (!isdigit(*str))
			return (0);
		str++;
	}
	return (1);
}
