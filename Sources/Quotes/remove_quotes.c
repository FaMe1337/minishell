/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fabio <fabio@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 22:11:50 by famendes          #+#    #+#             */
/*   Updated: 2025/03/21 20:15:04 by fabio            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static char	*remove_double_quotes(char *str)
{
	char	*result;
	int		i;
	int		j;

	i = 0;
	j = 0;
	result = malloc(ft_strlen(str));
	while (str[i])
	{
		if (str[i] == '\"')
		{
			if (!str[i + 1])
				break ;
			i++;
		}
		else
			result[j++] = str[i++];
	}
	result[j] = 0;
	free(str);
	return (result);
}

static char	*remove_single_quote(char *str)
{
	char	*result;
	int		i;
	int		j;

	i = 0;
	j = 0;
	result = malloc(ft_strlen(str));
	while (str[i])
	{
		if (str[i] == '\'')
		{
			if (!str[i + 1])
				break ;
			i++;
		}
		else
			result[j++] = str[i++];
	}
	result[j] = 0;
	free(str);
	return (result);
}

static void	remove_quotes_from_cmd(char **strs)
{
	int	i;
	int j;

	i = 0;
	while (strs[i])
	{
		printf("a str é: %s\n", strs[i]);
		if (in_quotes(strs[i], 1))
		{
			if (strs[i][0] == '\"')
				strs[i] = remove_double_quotes(strs[i]);
			else if (strs[i][0] == '\'')
				strs[i] = remove_single_quote(strs[i]);
			j = 0;
			while (strs[i][++j])
			{
				if (strs[i][j] == '\'')
					strs[i] = remove_single_quote(strs[i]);
			}
		}
		i++;
	}
}

static void	remove_quotes_from_red(char **strs)
{
	int	i;

	i = 0;
	while (strs[i])
	{
		if (in_quotes(strs[i], 5))
		{
			if (strs[i][4] == '\"')
				strs[i] = remove_double_quotes(strs[i]);
			else
				strs[i] = remove_single_quote(strs[i]);
		}
		i++;
	}
}

void	remove_quotes(t_pipe *tree)
{
	while (tree)
	{
		if (tree->cmd)
			remove_quotes_from_cmd(tree->cmd);
		if (tree->red)
			remove_quotes_from_red(tree->red);
		tree = tree->next;
	}
}
