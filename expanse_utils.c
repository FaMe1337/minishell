/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanse_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: famendes <famendes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 19:59:45 by famendes          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2025/03/02 15:08:55 by famendes         ###   ########.fr       */
=======
/*   Updated: 2025/03/02 15:10:12 by famendes         ###   ########.fr       */
>>>>>>> fabio
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_var_len(char *str, int i)
{
	int	len;

	len = 0;
	if (ft_isdigit(str[i]) || str[i] == '$' || str[i] == '?')
		return (1);
	while (str[i + len] && (ft_isalnum(str[i + len])
			|| str[i + len] == '_') &&
				!ft_isquote(str[i + len]))
		len++;
	return(len);
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
	return (ft_substr(token->value, i, get_var_len(token->value, i)));
}

int	ft_isquote(char c)
{
	if (c == '"' || c == '\'')
		return (1);
	return (0);
}
