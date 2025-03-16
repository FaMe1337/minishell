/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toferrei <toferrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 10:35:44 by toferrei          #+#    #+#             */
/*   Updated: 2025/03/07 23:26:44 by toferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	environment(char **args, t_data *data)
{
	t_env	*env;

	if (!data->env)
	{
		data->exit_status = 1;
		return ;
	}
	env = *(data->env);
	if (args[1])
	{
		write(2, "env: '", 6);
		write(2, args[1], ft_strlen(args[1]));
		write(2, "': No such file or directory\n", 29);
		data->exit_status = 127;
		return ;
	}
	while (env)
	{
		if (env->exported)
			printf("%s=%s\n", env->name, env->value);
		env = env->next;
	}
}
