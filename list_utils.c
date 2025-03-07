/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toferrei <toferrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 13:12:52 by toferrei          #+#    #+#             */
/*   Updated: 2025/03/05 13:17:16 by toferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	ft_modifiedlstsize(t_env *lst)
{
	int	i;

	i = 0;
	if (!lst)
		return (0);
	while (lst)
	{
		lst = lst->next;
		i++;
	}
	return (i);
}

t_env	*find_previous_node(t_env *list, t_env *node)
{
	if (!list || !node || list == node)
		return (NULL);
	while (list && list->next != node && list != node)
		list = list->next;
	return (list);
}

void	list_sorter(t_env **lst)
{
	t_env	*temp;
	t_env	*prev;
	t_env	*cursor;

	cursor = *lst;
	temp = NULL;
	while (cursor)
	{
		if (cursor->next \
			&& ft_strcmp(cursor->name, cursor->next->name) > 0)
		{
			prev = find_previous_node(*lst, cursor);
			temp = cursor->next;
			cursor->next = temp->next;
			temp->next = cursor;
			if (prev == NULL)
				*lst = temp;
			else
				prev->next = temp;
			cursor = *lst;
		}
		else
			cursor = cursor->next;
	}
}

void	list_copier(t_env **source, t_env **dest)
{
	t_env	*iterator;
	t_env	*temp;

	if (!source || !dest)
		return ;
	iterator = *source;
	while (iterator)
	{
		temp = ft_newnode(ft_strdup(iterator->name), \
			ft_strdup(iterator->value), iterator->exported);
		ft_modified_lstadd_back(dest, temp);
		iterator = iterator->next;
	}
}
