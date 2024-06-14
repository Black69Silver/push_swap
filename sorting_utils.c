/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sorting_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggeorgie <ggeorgie@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 19:56:18 by ggeorgie          #+#    #+#             */
/*   Updated: 2024/04/29 02:02:19 by ggeorgie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/**
 * Checks if 'stack_a' is sorted.
 * @param	struct s_stack	*stack_a: The stack which is being checked.
 * @param	struct s_element	*current: Temporary element.
 * @return	EXIT_SUCCESS if the stack is sorted, EXIT_FAILURE - otherwise.
 */
int	not_sorted(struct s_stack *stack_a)
{
	struct s_element	*current;

	current = (*(*stack_a).head).next;
	while (current != (*stack_a).head)
	{
		if ((*current).next && (*(*current).next).nbr != 0
			&& (*current).nbr > (*(*current).next).nbr)
			return (EXIT_FAILURE);
		current = (*current).next;
	}
	return (EXIT_SUCCESS);
}

/**
 * Swaps the first two elements of the stack.
 * @param	struct s_stack *stack: The stack which is being manipulated.
 * @param	struct s_element	*swapped_1: The first element in the stack.
 * @param	struct s_element	*swapped_2: The second element in the stack.
 * @return	The stack with the swapped elements.
 */
void	swap(struct s_stack *stack)
{
	struct s_element	*swapped_1;
	struct s_element	*swapped_2;

	if (!stack || (*stack).head == NULL
		|| (*(*stack).head).next == (*stack).head)
	{
		exit(EXIT_FAILURE);
	}
	swapped_1 = (*(*stack).head).next;
	swapped_2 = (*swapped_1).next;
	(*(*stack).head).next = swapped_2;
	(*swapped_1).next = (*swapped_2).next;
	(*swapped_2).next = swapped_1;
}

/**
 * Pushes the first element of 'stack_1' to 'stack_2'.
 * @param	struct s_stack *stack_1: The stack from which the element is taken.
 * @param	struct s_stack *stack_2: The stack to which the element is pushed.
 * @param	struct s_element	*pushed: The element which is pushed.
 * @return Adjusted stacks.
 */
void	push(struct s_stack *stack_1, struct s_stack *stack_2)
{
	struct s_element	*pushed;

	if (!stack_1 || (*stack_1).head == NULL
		|| (*(*stack_1).head).next == (*stack_1).head
		|| !stack_2 || (*stack_2).head == NULL)
	{
		exit(EXIT_FAILURE);
	}
	pushed = (*(*stack_1).head).next;
	(*(*stack_1).head).next = (*pushed).next;
	(*pushed).next = (*(*stack_2).head).next;
	(*(*stack_2).head).next = pushed;
	(*stack_1).size--;
	(*stack_2).size++;
}

/**
 * Rotates the first element of stack_a to the end.
 * @param	struct s_stack	*stack_a: The stack which is being manipulated.
 * @param	struct s_element	*current: Temporary element.
 * @param	struct s_element	*rotated: The element which is rotated.
 * @return	The adjusted stack.
 */
void	rotate(struct s_stack *stack_a)
{
	struct s_element	*current;
	struct s_element	*rotated;

	if (!stack_a || (*stack_a).head == NULL
		|| (*(*stack_a).head).next == (*stack_a).head)
	{
		exit(EXIT_FAILURE);
	}
	current = (*stack_a).head;
	rotated = (*current).next;
	(*current).next = (*rotated).next;
	(*rotated).next = (*stack_a).head;
	while (current && (*current).next != (*stack_a).head)
		current = (*current).next;
	(*current).next = rotated;
	write(1, "ra\n", 3);
}

/**
 * Rotates the last element of stack_a to the top.
 * @param	struct s_stack	*stack_a: The stack which is being manipulated.
 * @param	struct s_element	*current: Temporary element.
 * @param	struct s_element	*rotated: The element which is rotated.
 * @return	The adjusted stack.
 */
void	reverse_rotate(struct s_stack *stack_a)
{
	struct s_element	*current;
	struct s_element	*rotated;

	if (!stack_a || (*stack_a).head == NULL
		|| (*(*stack_a).head).next == (*stack_a).head)
	{
		exit(EXIT_FAILURE);
	}
	current = (*stack_a).head;
	while (current && (*(*current).next).next != (*stack_a).head)
		current = (*current).next;
	rotated = (*current).next;
	(*rotated).next = (*(*stack_a).head).next;
	(*current).next = (*stack_a).head;
	(*(*stack_a).head).next = rotated;
	write(1, "rra\n", 4);
}
