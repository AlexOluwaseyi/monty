#include "monty.h"

/**
 * opcode_mod - checks if the stack has at least two elements
 * before attempting to perform the modulo operation
 * @stack: Double pointer to the top of the stack.
 * @line_number: Line number where the opcode is encountered.
 */

void opcode_mod(stack_t **stack, unsigned int line_number)
{
	if (*stack == NULL || (*stack)->next == NULL)
	{
		fprintf(stderr, "L%u: can't mod, stack too short\n", line_number);
		exit(EXIT_FAILURE);
	}

	if ((*stack)->n == 0)
	{
		fprintf(stderr, "L%u: division by zero\n", line_number);
		exit(EXIT_FAILURE);
	}

	(*stack)->next->n %= (*stack)->n;
	opcode_pop(stack, line_number);
}

/**
 * opcode_pchar - checks if the stack is empty. If it is, it prints
 * the specified error message and exits with the EXIT_FAILURE status.
 * @stack: Double pointer to the top of the stack.
 * @line_number: Line number where the opcode is encountered.
 */

void opcode_pchar(stack_t **stack, unsigned int line_number)
{
	int ascii_value;

	if (*stack == NULL)
	{
		fprintf(stderr, "L%u: can't pchar, stack empty\n",
				line_number);
		exit(EXIT_FAILURE);
	}

	ascii_value = (*stack)->n;
	if (ascii_value < 0 || ascii_value > 127)
	{
		fprintf(stderr, "L%u: can't pchar, value out of range\n",
				line_number);
		exit(EXIT_FAILURE);
	}

	putchar(ascii_value);
	putchar('\n');
}

