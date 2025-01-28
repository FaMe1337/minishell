/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: famendes <famendes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 13:06:26 by famendes          #+#    #+#             */
/*   Updated: 2025/01/28 14:41:21 by famendes         ###   ########.fr       */
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
	while (data->token) {
	printf("value: %s\n", data->token->value);
	printf("type: %d\n", data->token->token_type);
	printf("index: %d\n", data->token->index);
		data->token = data->token->next;
	}
	//primeira tokenizaçao feita, ir para segunda
	return (1);
}

