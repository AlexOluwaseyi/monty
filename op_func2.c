#include "monty.h"

/**
 * opcode_add - checks if the stack has at least two elements before
 * attempting to perform the addition
 * @stack: Double pointer to the top of the stack.
 * @line_number: Line number where the opcode is encountered.
 */

void opcode_add(stack_t **stack, unsigned int line_number)
{
	if (*stack == NULL || (*stack)->next == NULL)
	{
		fprintf(stderr, "L%u: can't add, stack too short\n", line_number);
		exit(EXIT_FAILURE);
	}

	(*stack)->next->n += (*stack)->n;
	opcode_pop(stack, line_number);
}

/**
 * opcode_nop - function does nothing
 * @stack: Double pointer to the top of the stack.
 * @line_number: Line number where the opcode is encountered.
 */

void opcode_nop(stack_t **stack, unsigned int line_number)
{
	(void)stack;
	(void)line_number;
}
