/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: famendes <famendes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 13:06:26 by famendes          #+#    #+#             */
/*   Updated: 2025/02/02 20:57:36 by famendes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	parse_pipe(t_token *token)
{
	if (!token->previous || !token->next
		|| token->next->token_type == PIPE)
		{
			perror("syntax error near unexpected token \"|\"\n");
			return (true);
		}
	return (false);
}

static bool	parse_red(t_token *token)
{
	if (!token->next)
	{
		perror("syntax error near unexpected token 'newline'\n");
		return (true);
	}
	if (token->next->token_type != WORD)
	{
		perror("syntax error near unexpected token");
		write(2, token->next->value, ft_strlen(token->next->value));
		write(2, "\"\n", 2);
		return (true);
	}
}
static bool	parsing_operators(t_token *token)
{
	bool	error;

	error = false;
	while (token && !error)
	{
		if (token->token_type == PIPE)
			error = parse_pipe(token);
		else if (token->token_type != PIPE
				&& token->token_type != WORD)
			error = parse_red(token);
		token = token->next;
	}
	if (error)
		return (false);
	return (true);
}

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
	second_tokenazor(&data->token);
	while (data->token) {
	printf("value: %s\n", data->token->value);
	printf("type: %d\n", data->token->token_type);
	printf("index: %d\n", data->token->index);
		data->token = data->token->next;
	}
	return (1);
}

