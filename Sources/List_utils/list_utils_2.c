/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toferrei <toferrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 12:23:45 by toferrei          #+#    #+#             */
/*   Updated: 2025/03/20 16:06:21 by toferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_env	*ft_modifiedlstlast(t_env *lst)
{
	t_env	*temp;

	if (!lst)
		return (NULL);
	temp = lst;
	while (temp->next)
		temp = temp->next;
	return (temp);
}

t_env	*ft_newnode(char *content, char *value, bool exported)
{
	t_env	*elem;

	elem = malloc(sizeof * elem);
	if (!elem)
		return (NULL);
	elem->name = content;
	elem->value = value;
	elem->exported = exported;
	elem->next = NULL;
	return (elem);
}

void	ft_modified_lstadd_back(t_env **lst, t_env *new)
{
	t_env	*last;

	last = ft_modifiedlstlast(*lst);
	if (!last)
	{
		*lst = new;
		return ;
	}
	last->next = new;
}

t_env	*check_for_variable(t_env *env, char *var_name)
{
	if (!env || !var_name || !var_name[0])
		return (NULL);
	while (env != NULL)
	{
		if (!ft_strcmp(env->name, var_name))
			return (env);
		env = env->next;
	}
	return (NULL);
}

size_t	size_until_symbol(char *str, char c)
{
	int	n;

	n = 0;
	if (!str || !c)
		return (0);
	while (str[n] && str[n] != c)
		n++;
	return (n);
}
