/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toferrei <toferrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 10:38:05 by toferrei          #+#    #+#             */
/*   Updated: 2025/02/11 00:49:46 by toferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	size_list(t_env *list)
{
	int	n;

	n = 0;
	while (list)
	{
		n++;
		list = list->next;
	}
	return (n);
}

void print_export(t_env *list)
{
	t_env	*copy;

	copy = 
}

void export_bi(char **args, int fd, t_data *data)
{
	data->exit_code = 0;
	if (!args[1])
	{
		print_export(*(data->env));
		return ;
	}
	
}