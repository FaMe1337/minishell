/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toferrei <toferrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 14:35:28 by famendes          #+#    #+#             */
/*   Updated: 2025/03/20 16:06:53 by toferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

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

bool	check_for_open_quotes(char *str)
{
	int		i;
	bool	one_quote;
	bool	double_quote;

	i = 0;
	one_quote = false;
	double_quote = false;
	while (str[i])
	{
		if (str[i] == '\'' && !double_quote)
			one_quote = !one_quote;
		else if (str[i] == '\"' && !one_quote)
			double_quote = !double_quote;
		i++;
	}
	if (one_quote || double_quote)
		return (false);
	return (true);
}
