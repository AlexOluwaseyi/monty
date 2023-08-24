#ifndef MONTY_H
#define MONTY_H

/* STANDARD LIBRARY */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <ctype.h>

#define MAX_LINE_LENGTH 1024
extern const char *valid_opcodes[];


/* Structures */

/**
 * struct stack_s - doubly linked list representation of a stack (or queue)
 * @n: integer
 * @prev: points to the previous element of the stack (or queue)
 * @next: points to the next element of the stack (or queue)
 *
 * Description: doubly linked list node structure
 * for stack, queues, LIFO, FIFO
 */

typedef struct stack_s
{
	int n;
	struct stack_s *prev;
	struct stack_s *next;
} stack_t;

/**
 * struct instruction_s - opcode and its function
 * @opcode: the opcode
 * @f: function to handle the opcode
 *
 * Description: opcode and its function
 * for stack, queues, LIFO, FIFO
 */

typedef struct instruction_s
{
	char *opcode;
	void (*f)(stack_t **stack, unsigned int line_number);
} instruction_t;

/**
 * struct op_mapping - Maps opcode strings to opcode functions.
 * @opcode: The opcode string.
 * @function: Pointer to the corresponding opcode function.
 *
 * Description: This structure defines a mapping between an opcode string
 * and its corresponding opcode function. It is used to associate opcodes
 * with their implementation functions for efficient opcode handling.
 */

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
void free_stack(stack_t *stack);
void opcode_pint(stack_t **stack, unsigned int line_number);
void opcode_swap(stack_t **stack, unsigned int line_number);


#endif /* #ifndef MONTY_H */
