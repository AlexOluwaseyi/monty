#include "monty.h"

/**
 * main - The main monty programme
 * @argc: number of CLI arguments
 * @argv: array of CLI arguments
 * Return: 0 on success and 1 otherwise
 */

int main(int argc, char *argv[])
{
	FILE *file;
	char line[MAX_LINE_LENGTH], *opcode;
	unsigned int line_number = 0, found = 0, i;
	stack_t *stack;
	OpcodeMapping *opcode_mappings = get_opcode_mappings();

	if (argc != 2)
	{
		fprintf(stderr, "USAGE: monty file\n");
		exit(EXIT_FAILURE);
	} file = fopen(argv[1], "r");
	if (!file)
	{
		fprintf(stderr, "Error: Can't open file %s\n", argv[1]);
		exit(EXIT_FAILURE);
	} stack = NULL;
	while (fgets(line, sizeof(line), file))
	{
		line_number++;
		line[strcspn(line, "\n")] = '\0';
		opcode = strtok(line, " ");
		for (i = 0; opcode_mappings[i].opcode; i++)
		{
			if (strcmp(opcode, opcode_mappings[i].opcode) == 0)
			{
				if (strcmp(opcode, "push") == 0)
					opcode_push(&stack, line_number);
				else
					opcode_mappings[i].function(&stack, line_number);
				found = 1;
				break;
			}
		}
		if (!found)
		{
			fprintf(stderr, "L%u: unknown instruction %s\n", line_number, opcode);
			fclose(file);
			exit(EXIT_FAILURE);
		} found = 0;
	} fclose(file);
	return (0);
}
