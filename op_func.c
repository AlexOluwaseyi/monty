#include "monty.h"

const char *valid_opcodes[] = {
	"push", "pop", "pall", "pint", "swap",
	"add", "sub", "mul", "div", "mod",
	"nop", "pchar", "pstr", "rotl", "rotr",
	"stack", "queue", NULL
};

/* Opcode Functions */

/**
 * opcode_push - Pushes an element onto the top of the stack.
 * @stack: Double pointer to the top of the stack.
 * @line_number: Line number where the opcode is encountered.
 */

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
		free(new_node);
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

/**
 * opcode_pop - Removes an element from the top of the stack.
 * @stack: Double pointer to the top of the stack.
 * @line_number: Line number where the opcode is encountered.
 */

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

/**
 * opcode_pall - Prints all elements in the stack.
 * @stack: Double pointer to the top of the stack.
 * @line_number: Line number where the opcode is encountered.
 */

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

/**
 * opcode_pint - print the value at the top of the stack
 * @stack: Double pointer to the top of the stack.
 * @line_number: Line number where the opcode is encountered.
 */

void opcode_pint(stack_t **stack, unsigned int line_number)
{
	if (*stack == NULL)
	{
		fprintf(stderr, "L%u: can't pint, stack empty\n", line_number);
		exit(EXIT_FAILURE);
	}

	printf("%d\n", (*stack)->n);
}

/**
 * opcode_swap - checks if the stack has at least two elements
 * before attempting to swap the top two elements
 * @stack: Double pointer to the top of the stack.
 * @line_number: Line number where the opcode is encountered.
 */

void opcode_swap(stack_t **stack, unsigned int line_number)
{
	int temp;

	if (*stack == NULL || (*stack)->next == NULL)
	{
		fprintf(stderr, "L%u: can't swap, stack too short\n", line_number);
		exit(EXIT_FAILURE);
	}

	temp = (*stack)->n;
	(*stack)->n = (*stack)->next->n;
	(*stack)->next->n = temp;
}
