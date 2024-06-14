/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggeorgie <ggeorgie@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 16:25:04 by ggeorgie          #+#    #+#             */
/*   Updated: 2024/04/28 16:25:07 by ggeorgie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	word_count(char const *str, char c)
{
	int	count;
	int	in_word;

	count = 0;
	in_word = 0;
	while (*str)
	{
		if (*str == c)
		{
			in_word = 0;
		}
		else if (!in_word)
		{
			in_word = 1;
			count++;
		}
		str++;
	}
	return (count);
}

static int	find_start(const char *s, char c, int i)
{
	while (s[i] == c && s[i] != '\0')
		i++;
	return (i);
}

static int	find_end(const char *s, char c, int i)
{
	while (s[i] != c && s[i] != '\0')
		i++;
	return (i);
}

static void	free_memory(char ***arr, int index)
{
	while (index > 0)
	{
		index--;
		free((*arr)[index]);
	}
	free(*arr);
	*arr = NULL;
}

/**
 * Splits string ’s’ into an array of sub-strings using ’c’ delimiter.
 * @param	char	*s : string to be split.
 * @param	char	c : delimiter character.
 * @param	int		arr : array for 4 counters.
 * @param	int		arr[0] : position within 's' string.
 * @param	int		arr[1] : index for the start of the word.
 * @param	int		arr[2] : index for the end of the word.
 * @param	int		arr[3] : index for the word/sub-string/pointers.
 * @return	A string of pointers to the new strings resulting from the split.
 */
char	**ft_split(char const *s, char c)
{
	char	**pointers;
	int		arr[4];

	arr[0] = 0;
	pointers = malloc(sizeof(char *) * (word_count(s, c) + 2));				// + 1 for file name substitute, + 1 for NULL-terminator
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
				return (free_memory(&pointers, arr[3]), NULL);
			arr[3]++;
		}
		arr[0] = arr[2];
	}
	pointers[arr[3]] = NULL;
	return (pointers);
}
