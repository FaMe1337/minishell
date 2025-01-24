/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: famendes <famendes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 13:06:26 by famendes          #+#    #+#             */
/*   Updated: 2025/01/24 18:36:09 by famendes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int input_parser(t_data *data)
{
	char **inputs;
	int i = 0;

	if (!check_for_open_quotes(data->input))
	{
		perror("Wrong input\n");
		return (0);
	}
	inputs = ft_splits(data->input);
	//tokenizar o que recebo
	first_tokenazor(data, inputs);
	if (!data->token)
		return (0);
	//primeira tokenizaçao feita, ir para segunda
	return (1);
}

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

