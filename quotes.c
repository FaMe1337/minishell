/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: famendes <famendes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 14:35:28 by famendes          #+#    #+#             */
/*   Updated: 2025/01/28 15:00:18 by famendes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	check_for_open_quotes(char *str)
{
	int	i;
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
