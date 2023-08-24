#include "monty.h"

/**
 * is_valid_opcode - check for valid opcode
 * @opcode: the opcode to check for in list of valid opcodes
 *
 * Return: 0 on success and 1 if otherwise.
 */

int is_valid_opcode(const char *opcode)
{
	int i;

	for (i = 0; valid_opcodes[i] != NULL; i++)
	{
		if (strcmp(opcode, valid_opcodes[i]) == 0)
		{
			return (1);
		}
	}
	return (0);
}

/**
 * get_opcode_mappings - Get the opcode mappings.
 *
 * Return: The array of opcode mappings.
 */

OpcodeMapping *get_opcode_mappings(void)
{
	static OpcodeMapping opcode_mappings[] = {
		{"push", opcode_push},
		{"pop", opcode_pop},
		{"pall", opcode_pall},
		/* ... Other opcode mappings ... */
		{NULL, NULL}
	};
	return (opcode_mappings);
}