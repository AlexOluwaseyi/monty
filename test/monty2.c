#include "monty.h"

/**
 * main - The main monty programme, I think
 * @argc: the number of CLI arguments
 * @argv: the CLI arguments
 *
 * Return: 0 on success
 */

int main(int argc, char *argv[])
{
	FILE *file;
	char line[MAX_LINE_LENGTH], *opcode;
	unsigned int line_number = 0;
	int found = 0;
	stack_t *stack;
	OpcodeMapping *opcode_mappings = get_opcode_mappings();
	size_t i;

	if (argc != 2)
	{
		fprintf(stderr, "USAGE: monty file\n");
		exit(EXIT_FAILURE);
	}
	file = fopen(argv[1], "r");
	if (file == NULL)
	{
		fprintf(stderr, "Error: Can't open file %s\n", argv[1]);
		exit(EXIT_FAILURE);
	}
	stack = NULL;
	while (fgets(line, sizeof(line), file) != NULL)
	{
		line_number++;
		line[strcspn(line, "\n")] = '\0';
		opcode = strtok(line, " ");
		if (opcode[0] == '#')
			continue;
		if (opcode != NULL)
		{
			for (i = 0; opcode_mappings[i].opcode != NULL; i++)
			{
				if (strcmp(opcode, opcode_mappings[i].opcode) == 0)
				{
					opcode_mappings[i].function(&stack, line_number);
					found = 1;
					break;
				}
			}
			if (!found)
			{
				fprintf(stderr, "L%u: unknown instruction %s\n", line_number, opcode);
				free_stack(stack);
				fclose(file);
				exit(EXIT_FAILURE);
			}
		}
		found = 0;
	}
	free_stack(stack);
	fclose(file);
	return (0);
}

/**
 * free_stack - Frees the stack list
 * @stack: pointer to stack memory allocation
 */

void free_stack(stack_t *stack)
{
	stack_t *current_node;

	while (stack != NULL)
	{
		current_node = stack;
		stack = stack->next;
		free(current_node);
	}
	free(stack);
}
