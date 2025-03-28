/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toferrei <toferrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 17:15:58 by toferrei          #+#    #+#             */
/*   Updated: 2025/03/28 14:41:23 by toferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	pwd(t_data *data)
{
	char	*dir;

	dir = NULL;
	dir = getcwd(NULL, 0);
	if (!dir)
		dir = ft_strdup(data->pwd);
	if (dir != NULL)
	{
		write(1, dir, ft_strlen(dir));
		write(1, "\n", 1);
		free(dir);
		data->exit_status = 0;
	}
	else
	{
		perror("pwd : no pwd");
		data->exit_status = 1;
	}
}
