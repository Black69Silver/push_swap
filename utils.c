/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggeorgie <ggeorgie@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 01:21:22 by ggeorgie          #+#    #+#             */
/*   Updated: 2024/04/29 02:58:37 by ggeorgie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/**
 * Counts the number of characters in 'str' string.
 * @return	The 'i': number of characters in 'str'.
 */
int	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i] != '\0')
		i++;
	return (i);
}

char	*ft_substr_end(char *substr, int len_substr, char const *s,
	unsigned int start)
{
	int	i;

	i = 0;
	if (substr != NULL)
	{
		while (i < len_substr)
		{
			substr[i] = s[start + i];
			i++;
		}
		substr[i] = '\0';
	}
	return (substr);
}

/** 
 * Copy in 'substr' string 'len' characters from 's' string starting at 'start'. 
 * @param	char	*s: string to be copied from.
 * @param	int		start: position to start copying from.
 * @param	int		len: maximum length of the slot.
 * @param	int		len_str: length of 's' string.
 * @param	int		len_substr: length of 'substr' string.
 * @return	char	*substr: newly created string, or NULL if allocation fails.
*/
char	*ft_substr(char const *s, int start, int len)
{
	int		len_str;
	int		len_substr;
	char	*substr;

	len_str = ft_strlen(s);
	if (*s == '\0' || start > len_str)
	{
		substr = malloc(sizeof(char *) * 1);
		if (substr != NULL)
			substr[0] = '\0';
		return (substr);
	}
	if (len_str == 0)
		return ("");
	if (start + len <= len_str)
		len_substr = len;
	else
		len_substr = len_str - start;
	substr = malloc(sizeof(char) * (len_substr + 1));
	return (ft_substr_end(substr, len_substr, s, start));
}

/**
 * Sorts the array of integers in ascending order using bubble sort algorithm.
 * @param	int		*array_copy: array of integers to be sorted.
 * @param	int		*num_count: number of elements in 'array_copy'.
 * @param	int		i & j: counters.
 * @param	int		temp: temporary variable for swapping.
 * @return	Sorted array.
 */
int	*bubble_sort(int *array_copy, int *num_count)
{
	int	i;
	int	j;
	int	temp;

	j = 0;
	while (j < *num_count - 1)
	{
		i = 0;
		while (i < *num_count - j - 2)
		{
			if (array_copy[i] > array_copy[i + 1])
			{
				temp = array_copy[i];
				array_copy[i] = array_copy[i + 1];
				array_copy[i + 1] = temp;
			}
			i++;
		}
		j++;
	}
	return (array_copy);
}
