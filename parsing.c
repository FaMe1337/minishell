/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: famendes <famendes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 13:06:26 by famendes          #+#    #+#             */
/*   Updated: 2025/02/16 22:18:04 by famendes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	parse_pipe(t_token *token)
{
	if (!token->previous || !token->next
		|| token->next->token_type == PIPE)
		{
			write(2, "syntax error near ", 18);
			write(2, "unexpected token \'|\'\n", 22);
			return (true);
		}
	return (false);
}

static bool	parse_red(t_token *token)
{
	if (token->next == NULL)
	{
		ft_putstr_fd("syntax error near unexpected token 'newline'\n", 2);
		return (true);
	}
	else if (token->next->token_type != WORD)
	{
		write(2, "syntax error near unexpected token '", 37);
		write(2, token->next->value, ft_strlen(token->next->value));
		write(2, "'\n", 2);
		return (true);
	}
	return (false);
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
		return (true);
	return (false);
}

int input_parser(t_data *data)
{
	char **inputs;
	int i = 0;

	if (ft_strncmp(data->input, "exit", 4) == 0)
		exit(1);
	if (!check_for_open_quotes(data->input))
	{
		ft_putstr_fd("Wrong input\n", 2);
		return (0);
	}
	inputs = ft_splits(data->input);
	first_tokenazor(data, inputs); 	//tokenizar o que recebo
	if (!data->token)
		return (0);
	second_tokenazor(&data->token);//primeira tokenizaçao feita, ir para segunda
	if (parsing_operators(data->token)) //checkar por inputs errados a volta dos operadores
		return (0);
	//segunda feita, vamos para a criaçao de pipes
	data->pipe_list = pipe_lst_creation(data->token);
	//remove_quotes(data->pipe_list);
	free(data->input);
	return (1);
}
