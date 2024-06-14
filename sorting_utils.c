/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sorting_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggeorgie <ggeorgie@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 19:56:18 by ggeorgie          #+#    #+#             */
/*   Updated: 2024/04/28 16:52:00 by ggeorgie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	not_sorted(struct s_stack *stack_a)
{
	struct s_element	*current;

	current = (*(*stack_a).head).next;											// This must be the same as 	current = (*stack_a).head;	+	current = (*current).next;
	while (current != (*stack_a).head)
	{
//		printf("(*current).nbr: %i, (*(*current).next).nbr: %i\n", (*current).nbr, (*(*current).next).nbr);
		if ((*current).next && (*(*current).next).nbr != 0
			&& (*current).nbr > (*(*current).next).nbr)
			return (EXIT_FAILURE);
		current = (*current).next;
	}
	return (EXIT_SUCCESS);
}

void	swap(struct s_stack *stack)
{
	struct s_element	*swapped_1;
	struct s_element	*swapped_2;

	if (!stack || (*stack).head == NULL
		|| (*(*stack).head).next == (*stack).head)								// Check that stack_a is not empty, has a valid sentinel node, which is no the only element.
	{
		exit(EXIT_FAILURE);														// Is this the correct way to handle this error, or we should go freeing all allocated memory?
//		return (write(2, "Error\n", 6), EXIT_FAILURE);							// This has to be changed, but function output is 'void'.
	}
	swapped_1 = (*(*stack).head).next;
	swapped_2 = (*swapped_1).next;
	(*(*stack).head).next = swapped_2;
	(*swapped_1).next = (*swapped_2).next;
	(*swapped_2).next = swapped_1;
}

void	push(struct s_stack *stack_1, struct s_stack *stack_2)
{
	struct s_element	*pushed;

	if (!stack_1 || (*stack_1).head == NULL
		|| (*(*stack_1).head).next == (*stack_1).head
		|| !stack_2 || (*stack_2).head == NULL)									// Check that stacks are not empty, have valid sentinel nodes, which are no their only element.
	{
		exit(EXIT_FAILURE);														// Is this the correct way to handle this error, or we should go freeing all allocated memory?
//		return (write(2, "Error\n", 6), EXIT_FAILURE);							// This has to be changed, but function output is 'void'.
	}
	pushed = (*(*stack_1).head).next;
//	printf("(*pushed).nbr: %i\n", (*pushed).nbr);
	(*(*stack_1).head).next = (*pushed).next;
//	printf("(*(*stack_1).head).next: %i\n", (*(*(*stack_1).head).next).nbr);
	(*pushed).next = (*(*stack_2).head).next;
//	printf("(*pushed).next: %i\n", (*(*pushed).next).nbr);
	(*(*stack_2).head).next = pushed;
//	printf("(*(*stack_2).head).next: %i\n", (*(*(*stack_2).head).next).nbr);
	(*stack_1).size--;
	(*stack_2).size++;
}

void	rotate(struct s_stack *stack_a)
{
	struct s_element	*current;
	struct s_element	*rotated;

	if (!stack_a || (*stack_a).head == NULL
		|| (*(*stack_a).head).next == (*stack_a).head)							// Check that stack_a is not empty, has a valid sentinel node, which is no the only element.
	{
		exit(EXIT_FAILURE);														// Is this the correct way to handle this error, or we should go freeing all allocated memory?
//		return (write(2, "Error\n", 6), EXIT_FAILURE);							// This has to be changed, but function output is 'void'.
	}
	current = (*stack_a).head;
//	printf("(*current).nbr: %i\n", (*current).nbr);
	rotated = (*current).next;
	// printf("(*rotated).nbr: %i\n", (*rotated).nbr);
	(*current).next = (*rotated).next;
	// printf("(*(*current).next).nbr: %i\n", (*(*current).next).nbr);
	(*rotated).next = (*stack_a).head;
	// printf("(*rotated).next: %i\n", (*(*rotated).next).nbr);
//	while ((*(*current).next).next != (*stack_a).head)
	while (current && (*current).next != (*stack_a).head)
	{
		current = (*current).next;
//		printf("in loop (*current).nbr: %i\n", (*current).nbr);
	}
	(*current).next = rotated;
	// printf("(*(*current).next).nbr: %i\n", (*(*current).next).nbr);
	write(1, "ra\n", 3);
}

void	reverse_rotate(struct s_stack *stack_a)
{
	struct s_element	*current;
	struct s_element	*rotated;

	if (!stack_a || (*stack_a).head == NULL
		|| (*(*stack_a).head).next == (*stack_a).head)							// Check that stack_a is not empty, has a valid sentinel node, which is no the only element.
	{
		exit(EXIT_FAILURE);														// Is this the correct way to handle this error, or we should go freeing all allocated memory?
//		return (write(2, "Error\n", 6), EXIT_FAILURE);							// This has to be changed, but function output is 'void'.
	}
	current = (*stack_a).head;
//	printf("(*current).nbr: %i\n", (*current).nbr);
	while (current && (*(*current).next).next != (*stack_a).head)
	{
		current = (*current).next;
//		printf("in loop (*current).nbr: %i\n", (*current).nbr);
	}
	rotated = (*current).next;
	// printf("(*rotated).nbr: %i\n", (*rotated).nbr);
	(*rotated).next = (*(*stack_a).head).next;
	// printf("(*rotated).next: %i\n", (*(*rotated).next).nbr);
	(*current).next = (*stack_a).head;
	// printf("(*(*current).next).nbr: %i\n", (*(*current).next).nbr);
	(*(*stack_a).head).next = rotated;
	// printf("(*(*(*stack_a).head).next).nbr: %i\n", (*(*(*stack_a).head).next).nbr);
	write(1, "rra\n", 4);
}
