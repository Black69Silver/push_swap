/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggeorgie <ggeorgie@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 01:21:22 by ggeorgie          #+#    #+#             */
/*   Updated: 2024/04/27 01:36:13 by ggeorgie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/**
 * @brief	Counts the number of characters in 'str' string.
 * @return	The number of characters in 'str'.
 */
int	ft_strlen(const char *str)												// To be moved to another file, because there are too many functions on this one.
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i] != '\0')
		i++;
	return (i);
}


char	*ft_substr_end(char *substr, size_t len_substr, char const *s,
	unsigned int start)
{
	size_t	i;

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
