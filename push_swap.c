/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggeorgie <ggeorgie@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 16:08:16 by ggeorgie          #+#    #+#             */
/*   Updated: 2024/04/28 16:29:12 by ggeorgie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*	Sort the linked list using an auxiliary linked list.
	Print the operations for sorting the linked list.

Create an 'argc-1 * 2' array of integers.
Fill the first half of the array with 'argv'.
Check for duplicates and invalid arguments (< INT_MIN, > INT_MAX, non-digits).
Full the second half of the array with the indexes of the first half.
Make a linked list of the second half of the array.

<https://en.wikipedia.org/wiki/Stack_(abstract_data_type)#Linked_list>
When a stack is implemented as a singly linked list,
the 'top' of the stack is the 'head' of the list, and
the bottom of the stack is the tail of the list.
Overflow is not possible in this implementation.

Write code to execute the permited operations:
sa	(swap a)			:	Swap the first 2 elements at the top of stack 'a'.
							Do nothing if there is only one or no elements.
sb	(swap b)			:	Swap the first 2 elements at the top of stack 'b'.
							Do nothing if there is only one or no elements.
ss 						:	'sa' and 'sb' at the same time.

pa	(push a)			:	Take the first element at the top of 'b' and put
							it at the top of 'a'. Do nothing if 'b' is empty.
pb 	(push b)			:	Take the first element at the top of 'a' and put
							it at the top of 'b'. Do nothing if 'a' is empty.

ra 	(rotate a)			:	The first element of stack 'a' becomes the last one.
							All elements of stack 'a' shift up by 1. 
rb 	(rotate b)			:	The first element of stack 'b' becomes the last one.
							All elements of stack 'b' shift up by 1.
rr 						:	'ra' and 'rb' at the same time.

rra	(reverse rotate a)	:	The last element of stack 'a' becomes the first one.
							All elements of stack 'a' shift down by 1.
rrb	(reverse rotate b)	:	The last element of stack 'b' becomes the first one.
							All elements of stack 'b' shift down by 1.
rrr						:	'rra' and 'rrb' at the same time.

Examples:
$>./push_swap 2 1 3 5 4
stack_a:			stack_a:		stack_a:		stack_b:		stack_a:
original input:		sa:				pb, pb:			pb, pb:			end result:
sentinel node		sentinel node	sentinel node	sentinel node	sentinel
2					1				3				2				1
1					2				5				1				2
3					3				4								3
5					5												4
4					4												5

1	1	2	2	3	3
2	3	3	1	1	2
3	2	1	3	2	1
	rra	rra	sa	ra	ra
	sa				sa

Memory allocations:
 * Anytime there is 'exit' or 'return (EXIT_FAILURE)' in the code, these above should be 'free'd before it.

*/

#include "push_swap.h"

/**
 * Sorts a stack of integers with the smallest number being at the top, 
 * using a minimum number of operations.
 * @param	int				argc : number of arguments passed by the user.
 * @param	char			*argv[] : ptr to each argument passed by the user.
 * @param	int				**array : 2D array of integers and their indexes.
 * @param	struct s_stack	*stack_a : Pointer to the stack to be created.
 * @param	int				num_count : number of arguments.
 * @return	0 if the stack is sorted, 1 if the stack is not sorted.
 */
int	main(int argc, char **argv)
{
	int				**array;
	struct s_stack	*stack_a;
	int				num_count;
//	int				i;

	if (argc < 2)
	{
		printf("Too few arguments.\n");
		return (EXIT_FAILURE);
	}
	else
	{
		num_count = argc;
		array = make_index_array(&num_count, argv);
		// printf("\nArray:\n");
		// print_array(num_count, array, 0);
		// print_array(num_count, array, 1);
		if (duplicates_check(num_count, array))
		{
//			printf("Hello, duplicate!\n");
			free_array(array);
			return (write(2, "Error\n", 6), EXIT_FAILURE);
		}
		array = index_array(&num_count, array);
		// printf("\nArray:\n");
		// print_array(num_count, array, 0);
		// print_array(num_count, array, 1);
		stack_a = initialize_stack();
		if (!stack_a)
		{
			printf("initialize_stack_a\n");
			return (write(2, "4Error\n", 6), EXIT_FAILURE);
		}
		stack_a = fill_stack(num_count, array, stack_a);
		// printf("(*stack_a).size = %d\n", (*stack_a).size);
		// if(argc == 2)
		// 	free_int_array(array);
		while (not_sorted(stack_a))
		{
			sort(stack_a);
		}
		free_stack(stack_a);
	}
	free_array(array);											// Causes 'pointer being freed was not allocated' error.
	return (EXIT_SUCCESS);
}
