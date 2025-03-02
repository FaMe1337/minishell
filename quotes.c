/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: famendes <famendes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 14:35:28 by famendes          #+#    #+#             */
/*   Updated: 2025/03/02 23:15:00 by famendes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	in_quotes(const char *str, int index)
{
    int		i;
    bool	one_quote;
    bool	double_quote;

	i = 0;
	one_quote = false;
	double_quote = false;
    while (str[i] && i < index)
	{
        if (str[i] == '\'' && !double_quote)
            one_quote = !one_quote;
        else if (str[i] == '\"' && !one_quote)
            double_quote = !double_quote;
        i++;
    }
    return (one_quote || double_quote);
}

bool	single_quote(const char *str, int index)
{
    int		i;
    bool	one_quote;

	i = 0;
	one_quote = false;
    while (str[i] && i < index)
	{
        if (str[i] == '\'')
            one_quote = !one_quote;
        i++;
    }
    return (one_quote);
}

bool	double_quotes(const char *str, int index)
{
    int		i;
    bool	double_quote;

	i = 0;
	double_quote = false;
    while (str[i] && i < index)
	{
        if (str[i] == '\"')
            double_quote = !double_quote;
        i++;
    }
    return (double_quote);
}

void	remove_quotes_from_cmd(t_pipe *tree)
{
	int	i;
	int	j;
	char	*result;

	i = 0;
	while (tree->cmd[i])
	{
		result = safe_malloc(ft_strlen(tree->cmd[i]));
		j = 0;
		while (tree->cmd[i][j])
		{
			if (ft_isquote(tree->cmd[i][j]))
				j++;
			result[j] = tree->cmd[i][j];
			j++;
		}
		result[j] = 0;
		free(tree->cmd[i]);
		tree->cmd[i] = ft_strdup(result);
		free(result);
		i++;
	}
}

void	remove_quotes_from_red(t_pipe *tree)
{
	int	i;
	int	j;
	char	*result;

	i = 0;
	while (tree->red[i])
	{
		result = safe_malloc(ft_strlen(tree->red[i]));
		j = 0;
		while (tree->red[i][j])
		{
			if (ft_isquote(tree->red[i][j]))
				j++;
			result[j] = tree->red[i][j];
			j++;
		}
		result[j] = 0;
		free(tree->red[i]);
		tree->red[i] = ft_strdup(result);
		free(result);
		i++;
	}
}
