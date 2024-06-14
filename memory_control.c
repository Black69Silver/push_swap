/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_control.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggeorgie <ggeorgie@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 03:37:03 by ggeorgie          #+#    #+#             */
/*   Updated: 2024/04/29 02:41:52 by ggeorgie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/**
 * Frees a pointer and prevent double-freeing.
 * @param	char	*variable: a pointer to heap memory address.
 * @return	NULL.
 */
void	fn_free(char *variable)
{
	if (variable)
	{
		free(variable);
		variable = NULL;
	}
}

/**
 * Frees a double pointer and the pointers it points to.
 * @param	char	**ptr: a pointer to pointers.
 * @return	NULL.
 */
void	fn_free_ptr(char **ptr)
{
	int	i;

	if (ptr)
	{
		i = 0;
		while (ptr[i])
		{
			fn_free(ptr[i]);
			i++;
		}
		fn_free((char *)ptr);
	}
}

/**
 * Frees each sub-array of array and the array itself
 * @param	int	**array: a pointer to a 2D array to be freed.
 * @param	int	i: the index of the sub-array to be freed.
 * @param	int	rows: the number of rows in the array.
 * @return	NULL.
 */
void	free_array(int **array)
{
	int	i;
	int	rows;

	i = 0;
	rows = 2;
	if (array)
	{
		while (i < rows)
		{
			if (array[i])
				fn_free((char *)array[i]);
			i++;
		}
		fn_free((char *)array);
	}
}

/**
 * Frees the stack, including all its elements.
 * @param	struct s_stack	*stack: Pointer to the stack.
 * @param	struct s_element	*current: Pointer to the current element.
 * @param	struct s_element	*next: Pointer to the next element.
 * @return	Void.
 */
void	free_stack(struct s_stack *stack)
{
	struct s_element	*current;
	struct s_element	*next;

	if (stack)
	{
		current = (*(*stack).head).next;
		while (current != (*stack).head)
		{
			next = (*current).next;
			fn_free((char *)current);
			current = next;
		}
		fn_free((char *)(*stack).head);
		fn_free((char *)stack);
	}
}
