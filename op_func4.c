#include "monty.h"

/**
 * opcode_stack - does nothing
 * @stack: Double pointer to the top of the stack.
 * @line_number: Line number where the opcode is encountered.
 */

void opcode_stack(stack_t **stack, unsigned int line_number)
{
	(void)stack;
	(void)line_number;
}

/**
 * opcode_queue - if the stack has at least two elements, it adjusts the
 * pointers to switch the front and top elements, effectively converting
 * the data structure to a queue (FIFO).
 * @stack: Double pointer to the top of the stack.
 * @line_number: Line number where the opcode is encountered.
 */

void opcode_queue(stack_t **stack, unsigned int line_number)
{
	stack_t *current;

	(void)line_number;

	if (*stack == NULL || (*stack)->next == NULL)
	{
		return;
	}

	current = *stack;
	while (current->next != NULL)
	{
		current = current->next;
	}

	current->next = *stack;
	(*stack)->prev = current;
	*stack = (*stack)->next;
	(*stack)->prev = NULL;
	current->next->next = NULL;
}

