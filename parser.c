/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggeorgie <ggeorgie@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 15:27:40 by ggeorgie          #+#    #+#             */
/*   Updated: 2024/04/28 18:50:41 by ggeorgie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/**
 * Checks if there are duplicate elements in the array.
 */
int	duplicates_check(int num_count, int *array[0])
{
	int	i;
	int	j;

//	printf("Checking for duplicates.\n");
	if (!array)
	{
		// print error, free allocated memory, of let calling function handle this.
		printf("!inputs @ duplicates_check\n");
		return (EXIT_FAILURE);
	}
	i = 0;
//	while (array[0][i + 1])
	while (i < num_count - 2)
	{
		j = i + 1;
		while (j < num_count - 1)
		{
//			printf("array[0][%d] = %d, array[0][%d] = %d\n", i, array[0][i], j, array[0][j]);
			if (array[0][i] == array[0][j])
			{
//				printf("Hello, duplicate!\n");
				// print error, free allocated memory, of let calling function handle this.
				return (EXIT_FAILURE);
			}
			j++;
//			printf("i = %d, array[0][%d] = %d.\n", i, j, array[0][j]);
		}
		i++;
	}
//	printf("No duplicates.\n");
	return (EXIT_SUCCESS);
}	

int	push_swap_atoi(char input_str[], int *i, int sign)
{
	signed long long	nbr;

	nbr = 0;
	while (input_str[*i] != '\0')
	{
		// printf("input_str[%i] = %c\n", *i, input_str[*i]);
		// if (input_str[*i] < '0' || input_str[*i] > '9'
		// || ((nbr * 10 + (input_str[*i] - '0')) * sign) < INT_MIN
		// || ((nbr * 10 + (input_str[*i] - '0')) * sign) > INT_MAX)
		if (((nbr * 10 + (input_str[*i] - '0')) * sign) < INT_MIN
		|| ((nbr * 10 + (input_str[*i] - '0')) * sign) > INT_MAX)
		{
//			fn_free_ptr((char **)array);										// Causes 'pointer being freed was not allocated' error.
			// printf("Out of integer limits #%i.\n", *i);
//			fn_free_ptr(input_str);
			// write(2, "Error\n", 6);
			return (EXIT_FAILURE);
			// exit (EXIT_FAILURE);												// Maybe we should go freeing all allocated memory too?
//			return (NULL);														// This is not correct way to handle this error - it gives segmentation fault.
		}
//			free_exit(stack_a, integer);										// Think how to handle this.
		else
			nbr = nbr * 10 + (input_str[*i] - '0');
		(*i)++;
	}
	// printf("nbr = %lld\n", nbr);
	return (nbr * sign);
}

int	is_digit(char **input_str, int **array)
{
	int	i;
	int	j;

	i = 1;
	// printf("input_str[%i] = %s\n", i, input_str[i]);
	while (input_str[i] != NULL)
	{
		j = 0;
		while (input_str[i][j] != '\0')
		{	
			// printf("input_str[%i][%i] = %c\n", i, j, input_str[i][j]);
			if (!(input_str[i][j] >= '0' && input_str[i][j] <= '9') && input_str[i][j] != '-' && input_str[i][j] != '+' && input_str[i][j] != ' ')
			{
				free_array(array);
//				printf("Non-numerical symbol: '%c'.\n", input_str[i][j]);
//				fn_free_ptr(input_str);
				write(2, "Error\n", 6);
//				exit (EXIT_SUCCESS);
				exit (EXIT_FAILURE);
			}
			j++;
		}
		i++;
	}
	return (EXIT_FAILURE);
}

int	ascii_sign(char input_str, int *i)
{
	int	sign;

	sign = 1;
	if (input_str == '+' || input_str == '-')
	{
		if (input_str == '-')
			sign = -1;
		(*i)++;
	}
//	printf("sign = %d\n", sign);
	return (sign);
}

/**
 * Converts the input ASCII arguments to integers and checks if they are valid.
 * Assumed there are no white spaces in argv.
 * @param	int		argc : Number of arguments passed to the function.
 * @param	char	**input_str : Pointer to strings passed to the fn.
 * @param	int 	**array : Pointer to the 2D array to be created.
 * @param	int		i_nbr : Index of the current number/substring.
 * @param	int		i_char : Index of current character of current substring.
 * @param	int		sign : Sign of the current number/substring.
 * @param	int		nbr : The current number/substring.
 * @return	A pointer to the newly created array. Throws errors in case of
 * non-numerical symbols in argv (except +/-), or integers exceeding limits.
 */
int	**parse_input(int num_count, char **input_str, int **array)
{
	int	i_nbr;
	int	i_char;
	int	sign;
	int	nbr;

	// printf("\nEmpty array:\n");
	// print_array(num_count, array, 0);
	i_nbr = 1;
	if (is_digit(input_str, array))
	{
		// printf("is_digit passed.\n");
		while (i_nbr < num_count)														// The 0-th argument is the program name, so it is skipped, but the loop should also go though argv[num_count - 1].
		{
			i_char = 0;
			// printf("\ninput_str[%i][%i] = %c, num_count = %i\n", i_nbr, i_char, input_str[i_nbr][i_char], num_count);
			nbr = 0;
			// printf("\nNext number:\n");
			sign = ascii_sign(input_str[i_nbr][i_char], &i_char);
			// printf("sign = %d, i_char = %i\n", sign, i_char);
			// printf("input_str going to push_swap_atoi.\n");
			nbr = push_swap_atoi(input_str[i_nbr], &i_char, sign);
//		printf("nbr = %d with %i digits.\n", nbr, i_char);
			// printf("nbr = %d.\n", nbr);
// 		if (!nbr)
// 		{
// //			fn_free_ptr((char **)array);										// Causes 'pointer being freed was not allocated' error.
// 			printf("Non-numerical symbol or out of integer limits.\n");
// //			fn_free_ptr(input_str);
// 			write(2, "Error\n", 6);
// 			exit (EXIT_FAILURE);												// Maybe we should go freeing all allocated memory too?
// //			return (NULL);														// This is not correct way to handle this error - it gives segmentation fault.
// 		}
			array[0][i_nbr - 1] = nbr;
			// printf("array[0][%i] = %d\n", i_nbr - 1, array[0][i_nbr - 1]);
			i_nbr++;
		// printf("i_nbr: %i\n", i_nbr);
//		printf("input_str[%i][0] = %c, num_count = %i\n", i_nbr, input_str[i_nbr][0], num_count);
//		printf("input_str[i_nbr = %i][i_char = %i] = %c, num_count = %i\n", i_nbr, i_char, input_str[i_nbr][i_char], num_count);
//		printf("(*stack_a).size : %d\n", (*stack_a).size);
		}
	}
	return (array);
}
