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

#include "libft.h"

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

static int	fill(char **res, char const *s, char c)
{
	int	i;
	int	len;

	i = 0;
	while (*s)
	{
		len = 0;
		while (*s == c && *s)
			s++;
		while (*s != c && *s)
		{
			len++;
			s++;
		}
		if (len)
		{
			if (safe_malloc(res, i, len + 1))
				return (1);
			ft_strlcpy(res[i], s - len, len + 1);
		}
		i++;
	}
	return (0);
}

static int	word_counter(char const *s, char c)
{
	int	count;
	int	x;

	x = 0;
	count = 0;
	while (*s)
	{
		if (*s != c && x == 0)
		{
			x = 1;
			count++;
		}
		else if (*s == c)
			x = 0;
		s++;
	}
	return (count);
}

char	**ft_split(char const *s, char c)
{
	char	**res;
	int		words;

	words = word_counter(s, c);
	res = malloc(sizeof * res * (words + 1));
	if (!res)
		return (0);
	res[words] = NULL;
	if (fill (res, s, c))
		return (NULL);
	return (res);
}

/* void	ft_print_result(char const *s)
{
	int		len;

	len = 0;
	while (s[len])
		len++;
	write(1, s, len);
} */

/* int main(void)
{
	int i = 0;
	char **res = ft_split("I want to have cat 
	but i already have a pussy of a bf", 'h');
	
	while (res[i] != NULL)
	{
		ft_print_result(res[i]);
		write(1, "\n", 1);
		i++;
	}
} */