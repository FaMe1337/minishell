/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanse.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fabio <fabio@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 18:32:35 by famendes          #+#    #+#             */
/*   Updated: 2025/03/15 13:21:06 by fabio            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	valid_expansion(char *str, int i)
{
	i++;
	if (ft_isalnum(str[i]) || str[i] == '?' || str[i] == '$' ||
			str[i] == '_' || str[i] == '"' || str[i] == '\'')
		return true;
	return (false);
}

char	*put_var_on_token(t_token *token, char *var)
{
	int	i;
	int	j;
	int	var_size;
	char	*res;
	char	*tmp1;
	char	*tmp2;
	char	*tmp3;

	i = 0;
	while (token->value[i] != '$')
		i++;
	var_size = get_var_len(token->value, i + 1);
	j = (i + 1) + var_size;
	while (token->value[j])
		j++;
	tmp1 = ft_substr(token->value, 0, i);
	tmp2 = ft_strjoin(tmp1, var);
	tmp3 = ft_substr(token->value, (i + 1) + var_size, j);
	res = ft_strjoin(tmp2, tmp3);
	free(tmp1);
	free(tmp2);
	free(tmp3);
	free(token->value);
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
	free(var_name);
	free(var_value);
}


void	expanse_parse(t_data * data)
{
	int	i;
	t_token *temp;

	temp = data->token;
	while (temp)
	{
		if (temp->previous && temp->previous->token_type != HEREDOC)
		{
			i = 0;
			while (temp->value[i])
			{
				if (temp->value[i] == '$' && !single_quote(temp->value, i)
						&& temp->value[i + 1])
				{
					if (valid_expansion(temp->value, i))
					{
						expand_str(temp, data);
						continue;
					}
				}
				i++;
			}
		}
		temp = temp->next;
	}
}
