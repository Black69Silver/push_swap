/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_control.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggeorgie <ggeorgie@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 03:37:03 by ggeorgie          #+#    #+#             */
/*   Updated: 2024/04/28 16:24:19 by ggeorgie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/**
 * @brief	Free a pointer and prevent double-freeing.
 * @param	char	*variable : a pointer to heap memory address.
 * @return	NULL.
 */
void fn_free(char *variable)
{
	if (variable)																// Extra ' && *variable' results in leaks. 
	{
		free(variable);
		variable = NULL;
    }
}

/**
 * @brief	Free a double pointer and the pointers it points to.
 * @param	char	**ptr : a pointer to pointers.
 * @return	NULL.
 */
void	fn_free_ptr(char **ptr)
{
	int	i;

	if (ptr)
	{
		i = 0;
//		printf("fn_free_ptr: ptr[%d] = %s\n", i, ptr[i]);
		while (ptr[i])
		{
			fn_free(ptr[i]);
			i++;
		}
		fn_free((char *)ptr);
	}
	return;
//	write(2, "Error\n", 6);
//	exit (EXIT_FAILURE);
}

//	Free each sub-array of array and the array itself
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
	return;
}

/**
 * Frees the stack, including all its elements.
 * @param	struct s_stack	*stack : Pointer to the stack.
 * @return	Void.
 */
void	free_stack(struct s_stack *stack)
{
	struct s_element *current;
	struct s_element *next;

	if (stack)
	{
//		printf("free_stack:\n");
		current = (*(*stack).head).next;
//		printf("\n(*current).nbr: %i\n", (*current).nbr);
		while (current != (*stack).head)
		{
			next = (*current).next;
//			printf("current = %p, next = %p\n", current, next);
			fn_free((char *)current);											// The same result as 'free(current);'.
			current = next;
		}
		fn_free((char *)(*stack).head);
		fn_free((char *)stack);
	}
}

void	*ft_calloc(size_t count, size_t size)
{
	size_t	total_size;
	char	*string;
	size_t	i;

	i = 0;
	total_size = count * size;
	string = malloc(total_size);
	if (string)
	{
		while (i < total_size)
		{
			string[i] = '\0';
			i++;
		}
	}
	return (string);
}
