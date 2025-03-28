/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanse.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toferrei <toferrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 18:32:35 by famendes          #+#    #+#             */
/*   Updated: 2025/03/28 15:33:44 by toferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

bool	valid_expansion(char *str, int i)
{
	i++;
	if (ft_isalnum(str[i]) || str[i] == '?' || str[i] == '$'\
		|| str[i] == '_' || str[i] == '"' || str[i] == '\'')
		return (true);
	return (false);
}

char	*put_var_on_token(t_token *token, char *var)
{
	int		i;
	int		j;
	char	*res;
	char	*tmp1;
	char	*tmp2;

	i = -1;
	while (token->value[++i])
	{
		if (token->value[i] == '$' && single_quote(token->value, (i + 1)))
			i++;
		else if (token->value[i] == '$')
			break;
	}
	j = (i + 1) + get_var_len(token->value, i + 1);
	while (token->value[j])
		j++;
	tmp1 = ft_substr(token->value, 0, i);
	tmp2 = ft_strjoin(tmp1, var);
	free(tmp1);
	tmp1 = ft_substr(token->value, (i + 1) + \
			get_var_len(token->value, i + 1), j);
	res = ft_strjoin(tmp2, tmp1);
	free_strs(tmp1, tmp2, token->value);
	return (res);
}

void	expand_str(t_token *token, t_data *data)
{
	char	*var_name;
	char	*var_value;

	var_name = get_var_name(token);
	if (!ft_strcmp(var_name, "?"))
		var_value = ft_itoa(data->exit_status);
	else if (!ft_strcmp(var_name, "$"))
		var_value = ft_itoa(getpid());
	else
		var_value = get_var_values(var_name, data->env);
	token->value = put_var_on_token(token, var_value);
	printf("%s\n", token->value);
	free(var_name);
	free(var_value);
}

static void	expand_token(t_token *token, t_data *data)
{
	int	i;
	char *temp;

	i = 0;
	temp = token->value;
	while (temp[i])
	{
		if (temp[i] == '$' && !single_quote(temp, i) \
			&& temp[i + 1])
		{
			if (valid_expansion(temp, i))
			{
				expand_str(token, data);
				continue;
			}	
		}
		i++;
	}
}

void	expanse_parse(t_data *data)
{
	t_token	*temp;

	temp = data->token;
	while (temp)
	{
		if (temp->previous && temp->previous->token_type != HEREDOC)
			expand_token(temp, data);
		else if (!temp->previous)
			expand_token(temp, data);
		temp = temp->next;
	}
}
