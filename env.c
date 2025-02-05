/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toferrei <toferrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 10:35:44 by toferrei          #+#    #+#             */
/*   Updated: 2025/02/05 17:05:29 by toferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void environment(char **args, t_data *data)
{
	if (!data->env)
	{
		data->exit_code = 1;
		return ;
	}
	if (args[1])
	{
		write(1, "env: '", 6);
		write(1, args[1], ft_strlen(args[1]));
		write(1, "': No such file or directory\n", 29);
		data->exit_code = 127;
		return ;
	}
}
