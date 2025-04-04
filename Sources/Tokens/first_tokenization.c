/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   first_tokenization.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toferrei <toferrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 19:05:29 by famendes          #+#    #+#             */
/*   Updated: 2025/03/20 16:04:21 by toferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	get_type(char *str)
{
	if (!str || !str[0])
		return (-1);
	else if (str[0] == '>' && !str[1])
		return (REDIR_OUT);
	else if (str[0] == '>' && str[1] == '>' && !str[2])
		return (REDIR_APPEND);
	else if (str[0] == '<' && !str[1])
		return (REDIR_IN);
	else if (str[0] == '<' && str[1] == '<' && !str[2])
		return (HEREDOC);
	else if (str[0] == '|')
		return (PIPE);
	else
		return (WORD);
}

static void	lst_add_back(t_token *token, t_token *add, char *str)
{
	t_token	*current;

	current = token;
	while (current->next)
		current = current->next;
	add->value = malloc(ft_strlen(str) + 1);
	ft_strlcpy(add->value, str, ft_strlen(str) + 1);
	add->token_type = get_type(str);
	current->next = add;
	add->previous = current;
	add->next = NULL;
}

static t_token	*add_tokens(t_token *token, char *str)
{
	t_token	*add;

	add = malloc(sizeof(t_token));
	if (!add)
		return (NULL);
	if (token->next == NULL)
	{
		token->next = add;
		add->previous = token;
		add->value = malloc(ft_strlen(str) + 1);
		if (!add->value)
		{
			free(add);
			return (NULL);
		}
		ft_strlcpy(add->value, str, ft_strlen(str) + 1);
		add->token_type = get_type(str);
		add->next = NULL;
	}
	else
		lst_add_back(token, add, str);
	return (token);
}

t_token	*init_token(char *str)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->value = malloc(ft_strlen(str) + 1);
	if (!token->value)
	{
		free(token);
		return (NULL);
	}
	ft_strlcpy(token->value, str, ft_strlen(str) + 1);
	token->token_type = get_type(str);
	token->next = NULL;
	token->previous = NULL;
	free(str);
	return (token);
}

t_token	*first_tokenazor(t_data *data, char **inputs)
{
	t_token	*token;
	int		i;

	i = 0;
	if (!inputs || !inputs[i])
	{
		free(inputs);
		return (NULL);
	}
	token = init_token(inputs[i]);
	if (!token)
		return (NULL);
	while (inputs[++i])
	{
		if (add_tokens(token, inputs[i]) == NULL)
		{
			free_split_and_token(inputs + i, token);
			return (NULL);
		}
		free(inputs[i]);
	}
	free(inputs);
	data->token = token;
	return (data->token);
}
