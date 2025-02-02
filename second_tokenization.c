/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   second_tokenization.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: famendes <famendes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 18:16:54 by famendes          #+#    #+#             */
/*   Updated: 2025/02/02 21:03:19 by famendes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char *has_operator(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '<' && str[i + 1] == '<')
			return ("<<");
		if (str[i] == '>' && str[i + 1] == '>')
			return (">>");
		if (str[i] == '|')
			return ("|");
		if (str[i] == '>')
			return (">");
		if (str[i] == '<')
			return ("<");
		i++;
	}
	return (NULL);
}

static t_token *extract_operator(t_token *token, char *operator)
{
	t_token *new;
	t_token	*new_after;
	char *new_value;
	int	op_len;

	op_len = ft_strlen(operator);
	new_value = ft_substr(token->value, 0, op_len);
	new = init_token(new_value);
	new_value = ft_substr(token->value, op_len, ft_strlen(token->value) - op_len);
	new_after = init_token(new_value);
	if (!new && !new_after)
		return (NULL);
	new->next = new_after;
	new_after->previous = new;
	return(new);
}
static t_token *extract_word(t_token *token, char *operator)
{
	int	i;
	t_token *new;
	t_token	*new_after;
	char *new_value;

	i = 0;
   while (token->value[i] && ft_strncmp(&token->value[i],
   			operator, ft_strlen(operator)) != 0)
        i++;
	new_value = ft_substr(token->value, 0, i);
	new = init_token(new_value);
	new_value = ft_substr(token->value, i,
		ft_strlen(token->value) -  i);
	new_after = init_token(new_value);
	if (!new && !new_after)
		return (NULL);
	new->next = new_after;
	new_after->previous = new;
	return(new);
}

static t_token	*reasign_tokens(t_token *token, char *operator)
{
	t_token *new;

	if (ft_strncmp(token->value, operator, ft_strlen(operator)) == 0)
		new = extract_operator(token, operator);
	else
		new = extract_word(token, operator);
	if (!new)
		return (NULL);
	new->next->next = token->next;
	if (token->previous)
		token->previous->next = new;
	new->previous = token->previous;
	if (token->next)
		token->next->previous = new->next;
	free(token->value);
	free(token);
	return (new);
}

void	second_tokenazor(t_token **head)
{// o maximo que consigo ter numa str sao 3 operators
	int	i;
	char *operator;
	char *expand;
	t_token *token;

	i = 0;
	token = *head;
	while (token)
	{
		operator = has_operator(token->value);
		if (operator && !in_quotes(token->value, 1))
		{
			token = reasign_tokens(token, operator);
			if (token->previous == NULL)
				*head = token;
		}
		token->index = i++;
		token = token->next;
	}
}

