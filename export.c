/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toferrei <toferrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 10:38:05 by toferrei          #+#    #+#             */
/*   Updated: 2025/02/11 14:32:06 by toferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void list_sorter(t_env *list)
{
	t_env *head;
	t_env *temp;

	head = list;
	while (list)
	{
		if (list->next && ft_strncmp(list->name, list->next->name, ft_strlen(list->name)) >= 0)
		{
			temp = list->next;
			list = list
		}
	}
}

void list_copier(t_env **source, t_env **dest)
{
	t_env *iterator;
	t_env *temp;

	if (!source || !dest)
		return ;
	iterator = *source;
	while (iterator)
	{
		temp = ft_newnode(iterator->name, iterator->value, iterator->exported);
		ft_modified_lstadd_back(dest, temp);
		iterator = iterator->next;
	}
}

void print_export(t_env **list)
{
	t_env	**copy;

	if (!list)
		return ;
	copy = malloc(sizeof * copy);
	*copy = NULL;
	list_copier(list, copy);
	list_sorter(copy);
	ft_print_list(copy);
	ft_clean_list(copy);
	
}

void export_bi(char **args, int fd, t_data *data)
{
	data->exit_code = 0;
	if (!args[1])
	{
		print_export(data->env);
		return ;
	}
	
}