/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toferrei <toferrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 17:15:58 by toferrei          #+#    #+#             */
/*   Updated: 2025/01/30 16:29:39 by toferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void pwd(t_list *data)
{
	char *dir;

	dir = NULL;
	dir = getcwd(NULL, 0);
	if (!dir)
	{
		dir = data->
	}
	if (dir != NULL)
	{
		write(1, dir, ft_strlen(dir));
		write(1, "\n", 1);
		free(dir);
		data->exit_code = 0;
	}
	else
	{
		perror("");
		data->exit_code = 1;
	}
}
