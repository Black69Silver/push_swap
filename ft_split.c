/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggeorgie <ggeorgie@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 16:25:04 by ggeorgie          #+#    #+#             */
/*   Updated: 2024/04/29 02:36:20 by ggeorgie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/**
 * Counts the number of words/sub-strings in a string.
 * @param	char	*s: string to be evaluated.
 * @param	char	c: delimiter character.
 * @param	int		in_word: flag for current position being in a word.
 * @return	int		count: The number of words/sub-strings.
 */
int	word_counter(char const *str, char c)
{
	int	count;
	int	in_word;

	count = 0;
	in_word = 0;
	while (*str)
	{
		if (*str == c)
			in_word = 0;
		else if (!in_word)
		{
			in_word = 1;
			count++;
		}
		str++;
	}
	return (count);
}

/**
 * Finds the start of the word/sub-string.
 * @param	char	*s: string to be evaluated.
 * @param	char	c: delimiter character.
 * @param	int		i: index for the beginning of the search.
 * @return	The index for the beginning of the word/sub-string.
 */
int	find_start(const char *s, char c, int i)
{
	while (s[i] == c && s[i] != '\0')
		i++;
	return (i);
}

/**
 * Finds the end of the word/sub-string.
 * @param	char	*s: string to be evaluated.
 * @param	char	c: delimiter character.
 * @param	int		i: index for the start of the word/sub-string.
 * @return	The index for the end of the word/sub-string.
 */
int	find_end(const char *s, char c, int i)
{
	while (s[i] != c && s[i] != '\0')
		i++;
	return (i);
}

/**
 * Frees the memory allocated for '**pointers'. The triple pointer is
 * needed for modification of the original pointer in 'ft_split' function.
 * @param	char ***pointers: string of pointers.
 * @param	int	arr[3]: index for the word/sub-string/pointers.
 * @return	Freed memory.
 */
void	free_memory(char ***pointers, int arr[])
{
	while (arr[3] > 0)
	{
		arr[3]--;
		free((*pointers)[arr[3]]);
	}
	free(*pointers);
	*pointers = NULL;
}

/**
 * Splits string ’s’ into an array of sub-strings using ’c’ delimiter.
 * @param	char	*s: string to be split.
 * @param	char	c: delimiter character.
 * @param	int		arr: array for 4 counters.
 * @param	int		arr[0]: position within 's' string.
 * @param	int		arr[1]: index for the start of the word.
 * @param	int		arr[2]: index for the end of the word.
 * @param	int		arr[3]: index for the word/sub-string/pointers.
 * @return	A string of pointers to the new strings resulting from the split.
 */
char	**ft_split(char const *s, char c)
{
	char	**pointers;
	int		arr[4];

	arr[0] = 0;
	pointers = malloc(sizeof(char *) * (word_counter(s, c) + 2));
	if (!pointers || !s)
		return (NULL);
	pointers[0] = ft_substr(" ", 0, 1);
	arr[3] = 1;
	while (s[arr[0]])
	{
		arr[1] = find_start(s, c, arr[0]);
		arr[2] = find_end(s, c, arr[1]);
		if (arr[2] > arr[1])
		{
			pointers[arr[3]] = ft_substr(s, arr[1], arr[2] - arr[1]);
			if (pointers[arr[3]] == NULL)
				return (free_memory(&pointers, arr), NULL);
			arr[3]++;
		}
		arr[0] = arr[2];
	}
	pointers[arr[3]] = NULL;
	return (pointers);
}
