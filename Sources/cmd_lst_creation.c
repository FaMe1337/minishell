/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_lst_creation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toferrei <toferrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 15:25:17 by famendes          #+#    #+#             */
/*   Updated: 2025/03/17 16:19:54 by toferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_pipe	*init_pipe(void)
{
	t_pipe	*data;

	data = safe_malloc(sizeof(t_pipe));
	data->next = NULL;
	data->previous = NULL;
	data->red = NULL;
	data->cmd = NULL;
	data->pid = -1;
	data->fd_in = 0;
	data->fd_out = 1;
	return (data);
}

static int	count_pipes(t_token *token)
{
	int	res;

	res = 1;
	while (token)
	{
		if (token->token_type == PIPE)
			res++;
		token = token->next;
	}
	return (res);
}

static void	pipe_add_back(t_pipe *start, t_pipe *next)
{
	t_pipe	*current;

	if (!start || !next)
		return ;
	current = start;
	while (current->next)
		current = current->next;
	current->next = next;
	next->previous = current;
}

static void	init_red_and_cmd(t_token *token, t_pipe *start)
{
	while (token)
	{
		if (token->token_type == HEREDOC)
			start->red = add_prefix(start->red, token->next->value, "DOC:");
		else if (token->token_type == REDIR_IN)
			start->red = add_prefix(start->red, token->next->value, "RDI:");
		else if (token->token_type == REDIR_OUT)
			start->red = add_prefix(start->red, token->next->value, "RDO:");
		else if (token->token_type == REDIR_APPEND)
			start->red = add_prefix(start->red, token->next->value, "APP:");
		else if (token->token_type == WORD)
			start->cmd = add_prefix(start->cmd, token->value, NULL);
		else if (token->token_type == PIPE)
			start = start->next;
		if (token->token_type == WORD || token->token_type == PIPE)
			token = token->next;
		else
			token = token->next->next;
	}
}

t_pipe	*cmd_lst_creation(t_token *token)
{
	t_pipe	*start;
	t_pipe	*next;
	int		processes;

	start = init_pipe();
	processes = count_pipes(token);
	if (processes > 1)
	{
		while (processes > 1)
		{
			next = init_pipe();
			pipe_add_back(start, next);
			processes--;
		}
	}
	init_red_and_cmd(token, start);
	return (start);
}
