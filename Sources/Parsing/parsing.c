/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toferrei <toferrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 13:06:26 by famendes          #+#    #+#             */
/*   Updated: 2025/03/28 15:29:07 by toferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static bool	parse_pipe(t_token *token)
{
	if (!token->previous || !token->next \
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
		else if (token->token_type != PIPE \
					&& token->token_type != WORD)
			error = parse_red(token);
		token = token->next;
	}
	if (error)
		return (true);
	return (false);
}

static void	skip_empty_cmd(t_pipe *tree)
{
	int		i;
	int		j;
	char	**result;

	if (!tree->cmd)
		return ;
	i = 0;
	while (tree->cmd[i])
		i++;
	result = safe_malloc(sizeof(char *) * (i + 1));
	i = 0;
	j = 0;
	while (tree->cmd[i])
	{
		if (!tree->cmd[i][0])
			i++;
		else
			result[j++] = ft_strdup(tree->cmd[i++]);
	}
	result[j] = 0;
	free_char_array(tree->cmd);
	tree->cmd = result;
}

int	input_parser(t_data *data)
{
	char	**inputs;

	if (!check_for_open_quotes(data->input))
	{
		ft_putstr_fd("Wrong input\n", 2);
		return (0);
	}
	inputs = ft_splits(data->input);
	first_tokenazor(data, inputs);
	if (!data->token)
		return (0);
	second_tokenazor(&data->token);
	if (parsing_operators(data->token))
		return (0);
	expanse_parse(data);
	data->cmd_tree = cmd_lst_creation(data->token);
	remove_quotes(data->cmd_tree);
	skip_empty_cmd(data->cmd_tree);
	free(data->input);
	return (1);
}
