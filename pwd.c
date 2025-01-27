/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toferrei <toferrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 17:15:58 by toferrei          #+#    #+#             */
/*   Updated: 2025/01/27 15:19:56 by toferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built-ins.h"

void pwd(t_list *data)
{
	char *dir;

	dir = NULL;
	dir = getcwd(NULL, 0);
	if (!dir)
	{
		dir = // duplicate string of global variable (data->nev)
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
