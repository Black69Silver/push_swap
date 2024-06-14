/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggeorgie <ggeorgie@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 15:27:40 by ggeorgie          #+#    #+#             */
/*   Updated: 2024/04/29 17:58:43 by ggeorgie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/**
 * Checks if there are duplicate elements in the array.
 * @param	int		*num_count: number of arguments passed to the function.
 * @param	int		*array[0]: Pointer to array row 0, to be checked.
 * @param	int		i & j: counters.
 * @return	EXIT_SUCCESS if there are no duplicates, EXIT_FAILURE otherwise.
 */
int	duplicates_check(int num_count, int *array[0])
{
	int	i;
	int	j;

	if (!array)
		return (EXIT_FAILURE);
	i = 0;
	while (i < num_count - 2)
	{
		j = i + 1;
		while (j < num_count - 1)
		{
			if (array[0][i] == array[0][j])
				return (EXIT_FAILURE);
			j++;
		}
		i++;
	}
	return (EXIT_SUCCESS);
}

/**
 * Converts an ASCII string to an integer and checks if it exceeds the limits.
 * @param	char input_str[]: The evaluated number/substring.
 * @param	int	*i: Pointer to the index of the current character.
 * @param	int	sign: Sign of the evaluated number/substring.
 * @return	The signed integer value of the evaluated number/substring.
 */
int	push_swap_atoi(char input_str[], int *i, int sign, int **array)
{
	signed long long	nbr;

	nbr = 0;
	while (input_str[*i] != '\0')
	{
		if (((nbr * 10 + (input_str[*i] - '0')) * sign) < INT_MIN
			|| ((nbr * 10 + (input_str[*i] - '0')) * sign) > INT_MAX)
		{
			write(2, "Error\n", 6);
			free_array(array);
			exit (EXIT_FAILURE);
		}
		else
			nbr = nbr * 10 + (input_str[*i] - '0');
		(*i)++;
	}
	return (nbr * sign);
}

/**
 * Checks if input is a sign, and returns the sign.
 * @param	char	input_str: The evaluated character.
 * @param	int		*i: Pointer to the sign of the current number/substring.
 * @return	1 if the sign is '+', -1 if the sign is '-'.
 */
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
	return (sign);
}

/**
 * Checks if the input is valid char's - a digit, or +/- followed by a digit.
 * @param	char	**input_str: Pointer to strings passed to the function.
 * @param	int 	**array: Pointer to the 2D array to be created.
 * @param	int		i & j: counters.
 * @return	exits the program if the input is not valid.
 */
int	is_digit(char **input_str, int **array)
{
	int	i;
	int	j;

	i = 1;
	while (input_str[i] != NULL)
	{
		j = 0;
		while (input_str[i][j] != '\0')
		{
			if (!((input_str[i][j] >= '0' && input_str[i][j] <= '9')
			|| ((input_str[i][j] == '-' || (input_str[i][j] == '+'))
			&& input_str[i][j + 1] >= '0' && input_str[i][j + 1] <= '9'
			&& (j == 0 || input_str[i][j - 1] == ' '))))
			{
				free_array(array);
				write(2, "Error\n", 6);
				exit (EXIT_FAILURE);
			}
			j++;
		}
		i++;
	}
	return (EXIT_FAILURE);
}

/**
 * Checks if the input ASCII arguments are valid, converts them to integers,
 * and fills the first row of the array.
 * Assumed there are no white spaces in argv.
 * @param	int		*num_count: number of arguments passed to the function.
 * @param	char	**input_str: Pointer to strings passed to the function.
 * @param	int 	**array: Pointer to the 2D array to be created.
 * @param	int		i_nbr: Index of the current number/substring.
 * @param	int		i_char: Index of current character of current substring.
 * @param	int		sign: Sign of the current number/substring.
 * @param	int		nbr: The current number/substring.
 * @return	A pointer to the newly created array. Throws errors in case of
 * non-numerical symbols in argv (except +/-), or integers exceeding limits.
 */
int	**parse_input(int num_count, char **input_str, int **array)
{
	int	i_nbr;
	int	i_char;
	int	sign;
	int	nbr;

	i_nbr = 1;
	if (is_digit(input_str, array))
	{
		while (i_nbr < num_count)
		{
			i_char = 0;
			nbr = 0;
			sign = ascii_sign(input_str[i_nbr][i_char], &i_char);
			nbr = push_swap_atoi(input_str[i_nbr], &i_char, sign, array);
			array[0][i_nbr - 1] = nbr;
			i_nbr++;
		}
	}
	return (array);
}
