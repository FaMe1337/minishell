/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_lst_creation_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toferrei <toferrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 15:59:37 by famendes          #+#    #+#             */
/*   Updated: 2025/03/18 01:00:10 by toferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	str_count(char **res)
{
	int	i;

	i = 0;
	while (res[i])
		i++;
	return (i);
}

void	free_char_array(char **res)
{
	int	i;

	if (!res)
		return ;
	i = 0;
	while (res[i])
		free(res[i++]);
	free(res);
}

static char	**word_to_res(char **res, char *word)
{
	int		i;
	char	**result;

	i = 0;
	if (!res)
	{
		result = safe_malloc(sizeof(char *) * 2);
		result[i++] = word;
	}
	else
	{
		result = safe_malloc(sizeof(char *) * (str_count(res) + 2));
		while (res[i])
		{
			result[i] = ft_strdup(res[i]);
			i++;
		}
		result[i++] = word;
	}
	result[i] = 0;
	free_char_array(res);
	return (result);
}

char	**add_prefix(char **res, char *value, char *prefix)
{
	char	*word;

	if (prefix)
		word = ft_strjoin(prefix, value);
	else
		word = ft_strdup(value);
	if (!word)
		return (NULL);
	res = word_to_res(res, word);
	printf("erro provavel %s ou %s", res, word);
	return (res);
}
