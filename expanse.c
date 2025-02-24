/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanse.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: famendes <famendes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 18:32:35 by famendes          #+#    #+#             */
/*   Updated: 2025/02/24 00:15:03 by famendes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//todo
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
						expand_str(temp, data);
				}
				i++;
			}
		}
		temp = temp->next;
	}
}

bool	valid_expansion(char *str, int i)
{
	i++;
	if (ft_isalnum(str[i]) || str[i] == '?' || str[i] == '$' ||
			str[i] == '_')
		return true;
	return (false);
}


void	expand_str(t_token *token, t_data *data)
{
	char	*var_name;
	char	*var_value;

	var_name = get_var_name(token);
	printf("var_name é: %s\n", var_name);
	if (!ft_strcmp(var_name, "?"))
		var_value = ft_itoa(data->exit_status);
	else if (!ft_strcmp(var_name, "$"))
		var_value = ft_itoa(getpid());
	else
		var_value = get_var_values(var_name, data->env);
	printf("var_value é : %s\n", var_value);
}

char	*get_var_values(char *var_name, t_env **env)
{
	char *res;
	t_env	*temp;

	temp = (*env);
	while (temp)
	{
		if (!ft_strcmp(temp->name, var_name))
			return (ft_strdup(temp->value));
		temp = temp->next;
	}
	return (ft_strdup(""));
}

char	*get_var_name(t_token *token)
{
	int	i;

	i = 0;
	while (token->value[i] != '$')
		i++;
	i++;
	if (token->value[i] == '$' || token->value[i] == '?')
		return (ft_substr(token->value, i, 1));
	return (ft_substr(token->value, i, var_name_len(token->value, i)));
}

int	var_name_len(char *str, int i)
{
	int	len;

	len = 0;
	if (ft_isdigit(str[i]) || str[i] == '$' || str[i] == '?')
		return (1);
	while (str[i + len] && (ft_isalnum(str[i + len])
			|| str[i + len] == '_'))
		len++;
	printf("len da env: %d\n", len);
	return(len);
}
