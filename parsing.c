/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: famendes <famendes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 13:06:26 by famendes          #+#    #+#             */
/*   Updated: 2025/01/22 16:58:29 by famendes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int input_parser(t_data *data)
{
	char **inputs;
	int i = 0;

	if (!check_for_quotes(data->input))
	{
		perror("Wrong input\n");
		return (0);
	}
	inputs = ft_splits(data->input);
	//tokenizar o que recebo
}

bool	check_for_quotes(char *input)
{
	int	i;
	bool	one_quote;
	bool	double_quote;

	i = 0;
	one_quote = false;
	double_quote = false;

	while ()
}

