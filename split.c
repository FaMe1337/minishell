/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: famendes <famendes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 16:57:46 by famendes          #+#    #+#             */
/*   Updated: 2025/01/29 15:13:17 by famendes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toferrei <toferrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 13:30:28 by toferrei          #+#    #+#             */
/*   Updated: 2024/04/24 12:17:32 by toferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	safe_malloc(char **res, int position, size_t buffer)
{
	res[position] = malloc(buffer);
	if (!res[position])
	{
		while (position > 0)
		{
			free(res[position]);
			position--;
		}
		free(res);
		return (1);
	}
	return (0);
}

static int	fill(char **res, char const *s)
{
	int	i;
	int	len;
	bool quote;
	char const *start;

	i = 0;
	while (*s)
	{
		len = 0;
		while (*s && *s <= 32)
			s++;
		start = s;
		while (*s && (*s > 32 || (*s <= 32 && in_quotes(start, len))))
		{
			len++;
			s++;
		}
		if (len)
		{
			if (safe_malloc(res, i, len + 1))
				return (1);
			ft_strlcpy(res[i++], s - len, len + 1);
		}
	}
	return (0);
}

static int	word_counter(char const *s)
{
	int	count;
	int i;

	i = 0;
	count = 0;
	while (s[i])
	{
		if (s[i] > 32 || (s[i] <= 32 && in_quotes(s, i)))
		{
			count++;
			while (s[i] && (s[i] > 32 || (s[i] <= 32 && in_quotes(s, i))))
				i++;
		}
		else if (s[i] <= 32 && !in_quotes(s, i))
			i++;
	}
	return (count);
}

char	**ft_splits(char *s)
{
	char	**res;
	int		words;

	words = word_counter(s);
	res = malloc(sizeof * res * (words + 1));
	if (!res)
		return (0);
	res[words] = NULL;
	if (fill (res, s))
		return (NULL);
	return (res);
}
