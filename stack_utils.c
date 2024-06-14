/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggeorgie <ggeorgie@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 22:23:54 by ggeorgie          #+#    #+#             */
/*   Updated: 2024/04/28 16:57:18 by ggeorgie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void print_stack(struct s_stack *stack)
{
	struct s_element *current;

	if (stack == NULL) 
	{
		printf("The stack is empty.\n");
		return;
	}
	current = (*stack).head;
	current = (*current).next;
	printf("current order: sentinel node -> ");
	while (current != (*stack).head)
	{
		printf("%d -> ", (*current).nbr);
		current = (*current).next;
	}
	printf("(to je konec, which leads to the head / top / sentinel node)\n");
}

struct s_element	*create_element(int nbr)
{
	struct s_element *new_element;

	new_element = malloc(sizeof(struct s_element));
	if (!new_element) 
	{
        printf("!new_element @ create_element\n");
        return (NULL);
	}
	(*new_element).nbr = nbr;
	(*new_element).next = NULL;
	return (new_element);
}

// Function to insert a node at the end of the circular linked list
struct s_element	*insert_element(int nbr, struct s_stack *stack_a)
{
	struct s_element *current;
	struct s_element *new_element;

	if (!nbr || !stack_a)
//	if (!stack_a)																// Suitable for cases when 'nbr' begins from '0'.
		return (NULL);															// Is this the correct way to handle this error, or we should go freeing all allocated memory?
	current = (*stack_a).head;
//	printf("nbr = %d\n", nbr);
//	printf("current = %p, (*current).next = %p, (*stack_a).head = %p\n", current, (*current).next, (*stack_a).head);
	new_element = create_element(nbr);
	if (!new_element)
		return (NULL);															// Is this the correct way to handle this error, or we should go freeing all allocated memory?
//	printf("new_element = %p\n", new_element);
//	printf("(*new_element).nbr = %d\n", (*new_element).nbr);
	while (current && (*current).next != (*stack_a).head)						// Traverse to the last node while avoiding segmentation fault
		current = (*current).next;												// Next nbr becomes current nbr.
	(*current).next = new_element;
	(*new_element).next = (*stack_a).head;										// Link the last node with the head
	(*stack_a).size++;															// Increment the size of the stack
//	printf("current = %p, (*current).next = %p, new_element = %p\n", current, (*current).next, new_element);
//	printf("(*stack_a).head : %p\n", (*stack_a).head);
//	printf("(*stack_a).size : %d\n", (*stack_a).size);
//	fn_free((char *)new_element);												// If uncommented, this causes segmentation fault.
	return (new_element);
}

struct s_stack	*fill_stack(int num_count, int **array, struct s_stack *stack_a)
{
	int	i;

	i = 0;
	while (i < num_count - 1)
	{
//			printf("array[1][%d] = %d\n", i, array[1][i]);
		insert_element(array[1][i], stack_a);
		i++;
	}
	if (!stack_a)
	{
//		free_stack(stack_a);													// Consider removing: This doesn't seem to make any difference.
		printf("parse_input argv\n");
//		return (write(2, "Error\n", 6), (struct s_stack *)EXIT_FAILURE);
		return (NULL);															// Is this the correct way to handle this error, or we should go freeing all allocated memory?
	}
	return (stack_a);
}

/**
 * Stack initialization, including creation of a head/sentinel node.
 * @param	struct s_element	*head : Pointer to the head/sentinel node.
 * @param	struct s_stack		*stack : Pointer to the stack.
 * @return	A pointer to the newly created stack.
 */
struct s_stack	*initialize_stack(void)
{
	struct s_element	*head;
	struct s_stack		*stack;

//	printf("initialize_stack begins.\n");
	head = create_element(0);
	if (!head)
	{
		printf("!head @ initialize_stack\n");
		return (NULL);
	}
//	printf("head = %p\n", head);
	stack = malloc(sizeof(struct s_stack));
	if (!stack)
	{
		printf("!stack @ initialize_stack\n");
		fn_free((char *)head);
		return (NULL);
	}
	(*stack).head = head;														// Same as 'stack->head'.
	(*head).next = head;														// Same as 'head->next'.
	(*stack).size = 0;															// Same as 'stack->size'.
	return (stack);
}
