/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sorting.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggeorgie <ggeorgie@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 19:03:08 by ggeorgie          #+#    #+#             */
/*   Updated: 2024/04/28 16:51:57 by ggeorgie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	sort_3(struct s_stack *stack_a)
{
	if (!stack_a || (*stack_a).head == NULL
		|| (*(*stack_a).head).next == (*stack_a).head)							// Check that stack_a is not empty, has a valid sentinel node, which is no the only element.
	{
		exit(EXIT_FAILURE);														// Is this the correct way to handle this error, or we should go freeing all allocated memory?
//		return (write(2, "Error\n", 6), EXIT_FAILURE);							// This has to be changed, but function output is 'void'.
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

void	sort_small_stack(struct s_stack *stack_a, struct s_stack *stack_b,
						struct s_element *current, int stack_a_size)
{
	while ((*stack_a).size > 3)
	{
		// printf("\n(*current).nbr: %i\n", (*current).nbr);
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
		// printf("stack_a ");
		// print_stack(stack_a);
	}
	sort_3(stack_a);
	if ((*stack_b).size == 2 && (*(*(*stack_b).head).next).nbr
		< (*(*(*(*stack_b).head).next).next).nbr)
	{
		swap(stack_b);
		// printf("\n");
		// printf("stack_a ");
		// print_stack(stack_a);
		write(1, "sb\n", 3);
	}
	while ((*stack_b).size > 0)
	{
		push(stack_b, stack_a);
		// printf("\n");
		// printf("stack_a ");
		// print_stack(stack_a);
		write(1, "pa\n", 3);
	}
}

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
		// printf("chkr: %i,\t number to be moved: %i\n", chkr, (*current).nbr);
		if ((*current).nbr & chkr)
		{
//			printf("The digit of %i-th number is 1 > rotate in stack_a\n", i_a);
			rotate(stack_a);
		}
		else
		{
//			printf("The digit of %i-th number is 0 > push to stack_b\n", i_a);
			push(stack_a, stack_b);
			write(1, "pb\n", 3);
		}
		current = (*(*stack_a).head).next;
		i_a++;
		// printf("\n");
		// printf("stack_a ");
		// print_stack(stack_a);
		// printf("stack_b ");
		// print_stack(stack_b);
	}
	//  printf("\nfunction to push stack_b[%d] to stack_a\n", (*stack_b).size);
	while ((*stack_b).size > 0)
	{
		push(stack_b, stack_a);
		write(1, "pa\n", 3);
	}
}

// <https://www.exploringbinary.com/decimal-binary-conversion-table/>
void	sort(struct s_stack *stack_a)
{
	struct s_stack		*stack_b;
	int					chkr;
	struct s_element	*current;
	int					stack_a_size;

	stack_b = initialize_stack();
	if (!stack_b)
	{
		printf("initialize_stack_b error\n");
//		return (write(2, "Error\n", 6), EXIT_FAILURE);							// This has to be changed, but function output is 'void'.
	}
	if ((*stack_a).size > 5)
	{
		chkr = 1;
		while (chkr < (*stack_a).size)
		{
			// printf("\n");
			// printf("stack_a ");
			// print_stack(stack_a);
			sort_digit(stack_a, stack_b, chkr);
			chkr = chkr * 2;
		}
		if (chkr == (*stack_a).size)
			rotate(stack_a);			
	}
	else
	{
		current = (*(*stack_a).head).next;
		stack_a_size = (*stack_a).size;
		sort_small_stack(stack_a, stack_b, current, stack_a_size);
	}
	free_stack(stack_b);														// This is useful.
}
