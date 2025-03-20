/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_list.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toferrei <toferrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 13:47:48 by toferrei          #+#    #+#             */
/*   Updated: 2025/03/20 16:06:17 by toferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_print_list(t_env **lst)
{
	t_env	*temp;

	temp = *lst;
	if (!lst)
	{
		printf("Tried printing empty list\n");
		return ;
	}
	while (temp != NULL)
	{
		printf("declare -x %s", temp->name);
		if (temp->exported)
			printf("=\"%s\"", temp->value);
		printf ("\n");
		temp = temp->next;
	}
}
