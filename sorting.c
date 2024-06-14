/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sorting.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggeorgie <ggeorgie@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 19:03:08 by ggeorgie          #+#    #+#             */
/*   Updated: 2024/04/29 01:52:24 by ggeorgie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/**
 * Sorts stack_a when it has 3 elements, pushing the largest element to the end.
 * @param	struct s_stack	*stack_a: The stack which is being sorted.
 * @return	Sorted stack.
 */
void	sort_3(struct s_stack *stack_a)
{
	if (!stack_a || (*stack_a).head == NULL
		|| (*(*stack_a).head).next == (*stack_a).head)
	{
		exit(EXIT_FAILURE);
	}
	if ((*(*(*(*stack_a).head).next).next).nbr > (*(*(*stack_a).head).next).nbr
		&& (*(*(*(*stack_a).head).next).next).nbr
		> (*(*(*(*(*stack_a).head).next).next).next).nbr)
	{
		reverse_rotate(stack_a);
	}
	if ((*(*(*stack_a).head).next).nbr > (*(*(*(*stack_a).head).next).next).nbr
		&& (*(*(*stack_a).head).next).nbr
		> (*(*(*(*(*stack_a).head).next).next).next).nbr)
	{
		rotate(stack_a);
	}
	if ((*(*(*stack_a).head).next).nbr > (*(*(*(*stack_a).head).next).next).nbr)
	{
		swap(stack_a);
		write(1, "sa\n", 3);
	}
}

/**
 * Pushes the smallest elements to 'stack_b'.
 * @param	struct s_stack	*stack_a: The stack which is being sorted.
 * @param	struct s_stack	*stack_: The auxiliary stack.
 * @param	int stack_a_size: The size of 'stack_a'.
 * @param	struct s_element	*current: Temporary element.
 * @return	'stack_a' with 3 elements, while the rest are in 'stack_b'.
 */
void	reduce_to_3(struct s_stack *stack_a, struct s_stack *stack_b,
					int stack_a_size)
{
	struct s_element	*current;

	current = (*(*stack_a).head).next;
	if ((*current).nbr <= stack_a_size - 3)
	{
		current = (*current).next;
		push(stack_a, stack_b);
		write(1, "pb\n", 3);
	}
	else
	{
		rotate(stack_a);
		current = (*(*current).next).next;
	}
}

/**
 * Sorts a stack with 5 or fewer elements.
 * @param	struct s_stack	*stack_a: The stack which is being sorted.
 * @param	struct s_stack	*stack_: The auxiliary stack.
 * @param	int stack_a_size: The size of 'stack_a'.
 * @return	Sorted stack.
 */
void	sort_small_stack(struct s_stack *stack_a, struct s_stack *stack_b)
{
	int	stack_a_size;

	stack_a_size = (*stack_a).size;
	while ((*stack_a).size > 3)
		reduce_to_3(stack_a, stack_b, stack_a_size);
	sort_3(stack_a);
	if ((*stack_b).size == 2 && (*(*(*stack_b).head).next).nbr
		< (*(*(*(*stack_b).head).next).next).nbr)
	{
		swap(stack_b);
		write(1, "sb\n", 3);
	}
	while ((*stack_b).size > 0)
	{
		push(stack_b, stack_a);
		write(1, "pa\n", 3);
	}
}

/**
 * Sorts the stack by comparing the binary representation of the elements with 
 * chkr. '1's are rotated to end of 'stack_a'. '0's are pushed to 'stack_b'
 * and pushed back at the end.
 * @param	struct s_stack	*stack_a: The main stack.
 * @param	struct s_stack	*stack_: The auxiliary stack.
 * @param	int	chkr: The number to compare the elements with.
 * @param	struct s_element	*current: Temporary element.
 * @param	int	i_a: Counter for the elements in 'stack_a'.
 * @param	int	stack_a_size: The size of 'stack_a'.
 * @return	Sorted bit of numbers in 'stack_a'.
 */
void	sort_digit(struct s_stack *stack_a, struct s_stack *stack_b, int chkr)
{
	struct s_element	*current;
	int					i_a;
	int					stack_a_size;

	current = (*(*stack_a).head).next;
	i_a = 1;
	stack_a_size = (*stack_a).size;
	while (i_a <= stack_a_size)
	{
		if ((*current).nbr & chkr)
			rotate(stack_a);
		else
		{
			push(stack_a, stack_b);
			write(1, "pb\n", 3);
		}
		current = (*(*stack_a).head).next;
		i_a++;
	}
	while ((*stack_b).size > 0)
	{
		push(stack_b, stack_a);
		write(1, "pa\n", 3);
	}
}

/**
 * Sorts stack_a using the Radix method.
 * @param	struct s_stack	*stack_a: The stack being sorted.
 * @param	struct s_stack	*stack_b: The auxiliary stack.
 * @param	int	chkr: The number to compare the elements with.
 * <https://www.exploringbinary.com/decimal-binary-conversion-table/>
 * @return	Sorted stack.
 */
void	sort(struct s_stack *stack_a)
{
	struct s_stack		*stack_b;
	int					chkr;

	stack_b = initialize_stack();
	if (!stack_b)
		return ;
	if ((*stack_a).size > 5)
	{
		chkr = 1;
		while (chkr < (*stack_a).size)
		{
			sort_digit(stack_a, stack_b, chkr);
			chkr = chkr * 2;
		}
		if (chkr == (*stack_a).size)
			rotate(stack_a);
	}
	else
		sort_small_stack(stack_a, stack_b);
	free_stack(stack_b);
}
