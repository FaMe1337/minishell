/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   first_tokenization.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: famendes <famendes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 19:05:29 by famendes          #+#    #+#             */
/*   Updated: 2025/01/22 20:24:05 by famendes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int get_type(char *str)
{
	if (!str || !str[0])
		return (-1);
	else if (str[0] == '>' && str[1])
		return (REDIR_OUT);
	else if (str[0] == '>' && str[1] == '>' && str[2])
		return (REDIR_APPEND);
	else if (str[0] == '<' && str[1])
		return (REDIR_IN);
	else if (str[0] == '<' && str[1] == '<' && str[2])
		return (HEREDOC);
	else if (str[0] == '|' && str[1])
		return (PIPE);
	else
		return (WORD);
}

static t_token *init_token(char *str)
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
	token->index = 0;
	token->next = NULL;
	token->previous = NULL;
}

static t_token *add_tokens(t_token *token)
{
	t_token *add;

	add = malloc(sizeof(t_token));
	if (!add)
		return (NULL);
	if (token->next = NULL)
	{
		token->next = add;
	}
}

static void free_all(char **split, t_token *token)
{
	int	i;
	t_token *temp;

	i = 0;
	while (split[i])
	 free(split[i++]);
	free(split);
	temp = token;
	while (token)
	{
		token = token->next;
		free(temp);
		temp = token;
	}
}

t_token *first_tokenazor(t_data *data, char **inputs)
{
	t_token *token;
	int	i;

	i = 0;
	if (!inputs || !inputs[i][0])
	{
		free(inputs);
		return (NULL);
	}
	token = init_token(inputs[i]);
	if (!token)
		return (NULL);
	while (inputs[++i])
	{
		if (add_tokens(token) == NULL)
		{
			free_all(inputs + i, token);
			return (NULL);
		}
		free(inputs[i]);
	}
	free(inputs);
	return (token);
}
