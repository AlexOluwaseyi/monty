#ifndef MONTY_H
#define MONTY_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAX_LINE_LENGTH 1024

/* Structures */

typedef struct stack_s
{
	int n;
	struct stack_s *prev;
	struct stack_s *next;
} stack_t;

typedef struct instruction_s
{
	char *opcode;
	void (*f)(stack_t **stack, unsigned int line_number);
} instruction_t;

typedef struct op_mapping
{
	const char *opcode;
	void (*function)(stack_t **, unsigned int);
} OpcodeMapping;

/* Function Prototypes */
void opcode_push(stack_t **stack, unsigned int line_number);
void opcode_pop(stack_t **stack, unsigned int line_number);
void opcode_pall(stack_t **stack, unsigned int line_number);
int is_valid_opcode(const char *opcode);
OpcodeMapping *get_opcode_mappings(void);

#endif /* #ifndef MONTY_H */

#include "monty.h"

const char *valid_opcodes[] = {
	"push", "pop", "pall", "pint", "swap",
	"add", "sub", "mul", "div", "mod",
	"nop", "pchar", "pstr", "rotl", "rotr",
	"stack", "queue", NULL
};

/* Opcode Functions */
void opcode_push(stack_t **stack, unsigned int line_number)
{
	int value;
	char *value_str = strtok(NULL, " ");
	stack_t *new_node;

	if (value_str == NULL)
	{
		fprintf(stderr, "L%u: usage: push integer\n", line_number);
		exit(EXIT_FAILURE);
	}

	value = atoi(value_str);

	new_node = malloc(sizeof(stack_t));
	if (new_node == NULL)
	{
		fprintf(stderr, "Error: malloc failed\n");
		exit(EXIT_FAILURE);
	}

	new_node->n = value;
	new_node->prev = NULL;
	new_node->next = *stack;

	if (*stack != NULL)
	{
		(*stack)->prev = new_node;
	}

	*stack = new_node;
}

void opcode_pop(stack_t **stack, unsigned int line_number)
{
	stack_t *temp;
	if (*stack == NULL)
	{
		fprintf(stderr, "L%u: can't pop an empty stack\n", line_number);
		exit(EXIT_FAILURE);
	}

	temp = *stack;
	*stack = (*stack)->next;

	if (*stack != NULL)
	{
		(*stack)->prev = NULL;
	}

	free(temp);
}

void opcode_pall(stack_t **stack, unsigned int line_number)
{
	stack_t *current = *stack;

	(void) line_number;
	while (current != NULL)
	{
		printf("%d\n", current->n);
		current = current->next;
	}
}
int is_valid_opcode(const char *opcode)
{
	int i;
	for (i = 0; valid_opcodes[i] != NULL; i++)
	{
		if (strcmp(opcode, valid_opcodes[i]) == 0)
		{
			return 1;
		}
	}
	return 0;
}

OpcodeMapping *get_opcode_mappings(void)
{
	static OpcodeMapping opcode_mappings[] = {
		{"push", opcode_push},
		{"pop", opcode_pop},
		{"pall", opcode_pall},
		/* ... Other opcode mappings ... */
		{NULL, NULL}
	};
	return opcode_mappings;
}

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
				fclose(file);
				exit(EXIT_FAILURE);
			}
		}

		found = 0;
	}

	fclose(file);
	return 0;
}

