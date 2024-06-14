/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggeorgie <ggeorgie@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 20:04:03 by ggeorgie          #+#    #+#             */
/*   Updated: 2024/04/29 19:18:38 by ggeorgie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

// void	print_array(int num_count, int **array, int row)
// {
// 	int	i;

// 	if (row == 0)
// 		printf("original input:\t");
// 	if (row == 1)
// 		printf("   stack input:\t");
// 	i = 0;
// 	while (i < num_count - 1)
// 	{
// //		printf("array[0][%d] = %d, array[1][%d] = %d\n",
// //								i, array[0][i], i, array[1][i]);
// //		printf("array[0][%d] = %d\n", i, array[0][i]);
// 		printf("%d,\t", array[row][i]);
// 		i++;
// 	}
// 	printf("\n");
// }

/**
 * 2D array initialization.
 * @param	int	cols : the number of columns in the array 
 * 			= num_count: the number of elements in the stack.
 * @param	int	rows : the number of rows in the array = 2:
 *			- 0-th - the original values of the elements in the stack,
 *			- 1-st - the index of the elements in the stack after sorting.
 * @return	int	**array : pointer to 2D array of integers and their indexes.
 */
int	**initialize_2d_array(int cols)
{
	int	**array;
	int	rows;
	int	i;

	rows = 2;
	array = malloc((rows + 1) * sizeof(int *));
	if (!array)
		return (NULL);
	i = 0;
	while (i < rows)
	{
		array[i] = malloc(cols * sizeof(int));
		if (!array[i])
		{
			free_array(array);
			return (NULL);
		}
		i++;
	}
	array[rows] = (NULL);
	return (array);
}

/**
 * Fills array row 1 with the values based on index created during bubble sort.
 * @param	int		*array_copy: a copy of the original array.
 * @param	int		*num_count: number of arguments passed to the function.
 * @param	int		i & j: counters.
 * @return	int	**array : pointer to 2D array of integers and their indexes.
 */
int	**fill_array1(int **array, int *array_copy, int *num_count)
{
	int	i;
	int	j;

	i = 0;
	while (i < *num_count - 1)
	{
		j = 0;
		while (j < *num_count)
		{
			if (array[0][i] == array_copy[j])
			{
				array[1][i] = j + 1;
				break ;
			}
			j++;
		}
		i++;
	}
	return (array);
}

/**
 * Takes the user input, sorts it, and fills the array row 1 with the values.
 * @param	int		*num_count: number of arguments passed to the function.
 * @param	char	*argv[] : pointer to each argument passed by the user.
 * @return	int	**array : pointer to 2D array of integers and their indexes.
 */
int	**index_array(int *num_count, int **array)
{
	int	*array_copy;
	int	i;

	if (!array || !*array)
		return (NULL);
	array_copy = malloc(*num_count * sizeof(int));
	if (!array_copy)
		return (NULL);
	i = 0;
	while (i < *num_count)
	{
		array_copy[i] = array[0][i];
		i++;
	}
	array_copy = bubble_sort(array_copy, num_count);
	array = fill_array1(array, array_copy, num_count);
	fn_free((char *)array_copy);
	return (array);
}

/**
 * Takes the user input in quotation marks, splits it, counts the # of numbers,
 * and fills the array with the values.
 * @param	char	*argv[] : pointer to each argument passed by the user.
 * @param	char	**input_str : double pointer to parsed input.
 * @return	int	**array : pointer to 2D array of integers and their indexes.
 * @return	int	*num_count: number of arguments passed by the user.
 */
int	**handle_quotes(int *num_count, char **argv)
{
	char	**input_str;
	int		**array;

	input_str = ft_split(argv[1], ' ');
	if (!input_str)
		return ((int **)EXIT_FAILURE);
	*num_count = 0;
	while (input_str[*num_count])
		(*num_count)++;
	array = initialize_2d_array(*num_count);
	if (!array)
	{
		fn_free_ptr(input_str);
		return ((int **)EXIT_FAILURE);
	}
	array = parse_input(*num_count, input_str, array);
	fn_free_ptr(input_str);
	if (!array)
		return ((int **)EXIT_FAILURE);
	return (array);
}

/**
 * Takes the user input, parses it, and fills the array with the values.
 * @param	int		*num_count: number of arguments passed by the user.
 * @param	char	*argv[] : pointer to each argument passed by the user.
 * @return	int	**array : pointer to 2D array of integers and their indexes.
 */
int	**make_index_array(int *num_count, char **argv)
{
	int		**array;

	if (*num_count == 2)
	{
		if (ft_strlen(argv[1]) == 0)
		{
			write(2, "Error\n", 6);
			exit (EXIT_FAILURE);
		}
		array = handle_quotes(num_count, argv);
	}
	else
	{
		array = initialize_2d_array(*num_count);
		if (!array)
			return ((int **)EXIT_FAILURE);
		array = parse_input(*num_count, argv, array);
		if (!array)
			return ((int **)EXIT_FAILURE);
	}
	return (array);
}
