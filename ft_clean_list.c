/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_clean_list.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toferrei <toferrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 13:45:23 by toferrei          #+#    #+#             */
/*   Updated: 2025/03/06 15:32:01 by toferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	ft_clean_list(t_env **lst)
{
	t_env	*temp;
	t_env	*temp2;

	temp = *lst;
	if (lst == NULL)
	{
		printf("Tried freeing empty list\n");
		return ;
	}
	while (temp != NULL)
	{
		temp2 = temp->next;
		free(temp->name);
		free(temp->value);
		free(temp);
		temp = temp2;
	}
	free(lst);
}
