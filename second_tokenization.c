/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   second_tokenization.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: famendes <famendes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 18:16:54 by famendes          #+#    #+#             */
/*   Updated: 2025/01/29 21:38:15 by famendes         ###   ########.fr       */
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


static char	*has_expand(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$' && str[i + 1] != ' ')
			return(ft_strdup("$"));
		i++;
	}
	return (NULL);
}
// AQUI
static t_token *extract_operator(t_token *token, char *operator)
{
	t_token *new;
	t_token	*new_after;
	char *new_value;
	int	op_len;

	op_len = ft_strlen(operator);
	printf("a legnht é: %d\n", op_len);
	new_value = ft_substr(token->value, 0, op_len);
	new = init_token(new_value);
	new_value = ft_substr(token->value, op_len, ft_strlen(token->value) - op_len);
	new_after = init_token(new_value);
	new->previous = token->previous;
	new->next = new_after;
	new_after->previous = new;
	new_after->next = token->next;
	free(token->value);
	free(token);
	return(new);
}
static void	extract_word(t_token *token)
{
	printf("FAZER AMANHA\n\n\n\n");
}

void	reasign_tokens(t_token *token, char *operator)
{
	t_token	*new_first;

	if (ft_strncmp(token->value, operator, ft_strlen(operator) + 1))
		new_first = extract_operator(token, operator);
	else
		extract_word(token);
}

void	second_tokenazor(t_token *token)
{// o maximo que consigo ter numa str sao 3 operators e posso ter $ no meio
	int	i;
	char *operator;
	char *expand;

	i = 0;
	while (token)
	{
		operator = has_operator(token->value);
		if (operator && !in_quotes(token->value, 1))
			reasign_tokens(token, operator);
/* 		expand = has_expand(token->value);
		if (expand || (expand && double_quotes(token->value, 1)))
			//todo(token, expand);
		token->index = i++; */
		token = token->next;
	}
}

