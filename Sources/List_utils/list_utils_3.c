/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils_3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toferrei <toferrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 15:23:35 by toferrei          #+#    #+#             */
/*   Updated: 2025/03/20 16:06:25 by toferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*get_value_for_list(char *str)
{
	int	n;

	n = 1;
	while (str[n] != '\0' && str[n - 1] != '=')
		n++;
	return (&str[n]);
}

/* fx below is redundant because of check_for_variable*/

char	*get_var_value(t_env *env, char *var_name)
{
	while (env != NULL)
	{
		if (!ft_strcmp(env->name, var_name))
			return (env->value);
		env = env->next;
	}
	return (NULL);
}

bool	for_export(char *str)
{
	while (*str)
	{
		if (*str == '=')
			return (true);
		str++;
	}
	return (false);
}
