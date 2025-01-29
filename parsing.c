/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: famendes <famendes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 13:06:26 by famendes          #+#    #+#             */
/*   Updated: 2025/01/29 21:09:28 by famendes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int input_parser(t_data *data)
{
	char **inputs;
	int i = 0;

	if (ft_strncmp(data->input, "exit", 4) == 0)
		exit(1);
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
	second_tokenazor(data->token);
	while (data->token) {
	printf("value: %s\n", data->token->value);
	printf("type: %d\n", data->token->token_type);
	printf("index: %d\n", data->token->index);
		data->token = data->token->next;
	}
	return (1);
}

