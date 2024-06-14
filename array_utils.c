/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggeorgie <ggeorgie@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 20:04:03 by ggeorgie          #+#    #+#             */
/*   Updated: 2024/04/28 16:23:01 by ggeorgie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	print_array(int num_count, int **array, int row)
{
	int	i;

	if (row == 0)
		printf("original input:\t");
	if (row == 1)
		printf("   stack input:\t");
	i = 0;
	while (i < num_count - 1)
	{
//		printf("array[0][%d] = %d, array[1][%d] = %d\n", i, array[0][i], i, array[1][i]);
//		printf("array[0][%d] = %d\n", i, array[0][i]);
		printf("%d,\t", array[row][i]);
		i++;
	}
		printf("\n");
}

/**
 * 2D array initialization.
 * @param	int	cols : the number of columns in the array 
 * 			= num_count: the number of elements in the stack.
 * @param	int	rows : the number of rows in the array = 2:
 *			- 0-th - the original values of the elements in the stack,
 *			- 1-st - the index of the elements in the stack after sorting.
 * @return	int	**array : A double pointer to the array.
 */
int	**initialize_2d_array(int cols)
{
	int	**array;
	int	rows;
	int	i;

	rows = 2;
	array = malloc((rows + 1) * sizeof(int *));									// +1 for NULL-terminator
	if (!array) 
	{
		printf("Memory allocation for array failed.\n");
		return (NULL);
	}
	i = 0;
	while (i < rows)
	{
		array[i] = malloc(cols * sizeof(int));
		if (!array[i])
		{
			free_array(array);
            printf("Failed to allocate memory for array[%d].\n", i);
            return (NULL);
        }
		i++;
	}
    array[rows] = (NULL);														// NULL-terminated array of pointers
    return (array);
}

int	**fill_array1(int **array, int *array_copy, int *num_count)
{
	int	i;
	int	j;

	i = 0;
	while (i < *num_count - 1)
	{
//		printf("array[0][%i]: %i\t", i, array[0][i]);
		j = 0;
		while (j < *num_count)
		{
//			printf("\tarray_copy[%i]: %i", j, array_copy[j]);
			if (array[0][i] == array_copy[j])
			{
				array[1][i] = j + 1;											// The '+ 1' is necessary to avoid the '0' index, which conincides with the sentinel node value.
//				printf("\tarray[1][%i]: %i\n", i, array[1][i]);
				break;
			}
			j++;
		}
		i++;
	}
	return (array);
}

int	*bubble_sort(int *array_copy, int *num_count)
{
	int	i;
	int	j;
	int	temp;

	j = 0;
	while (j < *num_count - 1)
	{
		i = 0;
//		printf("\nloop to: %i\n", *num_count - j - 2);
		while (i < *num_count - j - 2)											// 'while (i < *num_count - 2)' is wrong.
		{
//			printf("j[%i]i[%i]: %i\t", j, i, array_copy[i]);
			if (array_copy[i] > array_copy[i + 1])
			{
				temp = array_copy[i];
				array_copy[i] = array_copy[i + 1];
				array_copy[i + 1] = temp;
			}
//			printf("\tis now: %i\t", array_copy[i]);
			i++;
//			printf("\tarray_copy[%i]: %i\n", i, array_copy[i]);
		}
		j++;
	}
	return (array_copy);
}

/**
 * Takes the user input, sorts it, and fills the array with the values.
 * @param	int		*num_count: number of arguments passed by the user.
 * @param	char	*argv[] : pointer to each argument passed by the user.
 * @param	int		**array : 2D array of integers and their indexes.
 * @param	char	**input_str : double pointer to parsed input,
 * 					which was provided in quotation marks.
 * @return	int	**array : double pointer to the array.
 */
int	**index_array(int *num_count, int **array)
{
	int	*array_copy;
	int	i;

	if (!array || !*array)
	{
		printf("Input array is NULL or not properly allocated.\n");
		return (NULL);
	}
	array_copy = malloc(*num_count * sizeof(int));
	if (!array_copy)
	{
		printf("Memory allocation for array_copy failed.\n");
		return (NULL);
	}
	i = 0;
	while (i < *num_count)
	{
		array_copy[i] = array[0][i];
		i++;
	}
	array_copy = bubble_sort(array_copy, num_count);
//	printf("array_copy\n");
//	print_array(*num_count, &array_copy, 1);
	array = fill_array1(array, array_copy, num_count);
//	print_array(*num_count, array, 1);
	fn_free((char *)array_copy);
	return (array);
}

/**
 * Takes the user input, parses it, and fills the array with the values.
 * @param	int		*num_count: number of arguments passed by the user.
 * @param	char	*argv[] : pointer to each argument passed by the user.
 * @param	int		**array : 2D array of integers and their indexes.
 * @param	char	**input_str : double pointer to parsed input,
 * 					which was provided in quotation marks.
 * @return	int	**array : double pointer to the array.
 */
int	**make_index_array(int *num_count, char **argv)
{
	int		**array;
	char	**input_str;

	if (*num_count == 2)
	{
		// printf("initialize_2d_array in quotation marks\n");
		input_str = ft_split(argv[1], ' ');										// Assuming ft_split properly null-terminates the array
		if (!input_str) 
		{
			printf("No output from split\n");
			return ((int **)EXIT_FAILURE);
        }
		*num_count = 0;
		while (input_str[*num_count])											// Count the number of 'numbers' in 'input_str'
		{
			(*num_count)++;
		}
		// printf("input_str[1]: '%s'\n", input_str[1]);
		array = initialize_2d_array(*num_count);
		if (!array)
		{
			fn_free_ptr(input_str);
			printf("Error: initialize_2d_array in quotation marks\n");
			return ((int **)EXIT_FAILURE);
        }
//		*num_count = *num_count + 1;											// In earlier versions, 'num_count + 1' was useful, but now give a segmentation fault.
		// printf("parse_input in quotation marks\n");
		array = parse_input(*num_count, input_str, array);
		fn_free_ptr(input_str);
		if (!array)
		{
			printf("Error: parse_input in quotation marks\n");
            return (int **)EXIT_FAILURE;
        }
		// printf("make_index_array in quotation marks output\n");
		// print_array(*num_count, array, 0);
    }
	else
	{
        array = initialize_2d_array(*num_count);
        if (!array)
		{
			printf("initialize_2d_array from argv\n");
            return ((int **)EXIT_FAILURE);
        }
		array = parse_input(*num_count, argv, array);
        if (!array)
		{
			printf("parse_input from argv\n");
            return (int **)EXIT_FAILURE;
        }
    }
	return (array);
}
