/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toferrei <toferrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 10:38:05 by toferrei          #+#    #+#             */
/*   Updated: 2025/02/12 15:29:32 by toferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	if (!s1 || !s2)
		return (NULL);
	while (*s1 && *s2 && (*s1 == *s2))
	{
		if (!*s1 || !*s2)
			break ;
		s1++;
		s2++;
	}
	return (*(const unsigned char *)s1 - *(const unsigned char *)s2);
}

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

void list_sorter(t_env **lst)
{
	t_env *temp;
	t_env *prev;
	t_env *cursor;

	cursor = *lst;
	temp = NULL;
	while (cursor)
	{
		if (cursor->next && ft_strcmp(cursor->name, cursor->next->name) > 0)
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

void list_copier(t_env **source, t_env **dest)
{
	t_env *iterator;
	t_env *temp;
	char *tempstr;

	if (!source || !dest)
		return ;
	iterator = *source;
	while (iterator)
	{
		temp = ft_newnode(ft_strdup(iterator->name), iterator->value, iterator->exported);
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
	ft_print_list(copy);
	printf("\nlist size %d\n", ft_modifiedlstsize(*copy));
	if (ft_modifiedlstsize(*copy) > 1)
		list_sorter(copy);
	printf("\nlist size %d\n", ft_modifiedlstsize(*copy));
	ft_print_list(copy);
	ft_clean_list(copy);
	free(copy);
}

void export_bi(char **args, int fd, t_data *data)
{
	data->exit_code = 0;
	if (!args[1])
	{
		print_export(data->env);
		return ;
	}
	if (fd)
	{
		;
	}
	
}

int	main(int ac, char **av, char **env)
{
	char **args;
	t_data data;

	data.env = NULL;
	data.pwd = NULL;
	data.pwd = getcwd(NULL, 0);
	data.home = "/home/etom";
	if (ac != 3)
	/* 
	{
		printf( "deu cagada, o bjoetivo e tipo have uma string ./a.out cd [qualquer string aqui]");
		return 0;
	} */
	args = av;
	args = (char *[]){"export", NULL};
	env_to_list(&data, env);
	ft_print_list(data.env);


	printf("\n\n\n\n\n antes export fx\n\n\n\n\n");
	export_bi(args, 1, &data);
	ft_clean_list(data.env);
	free(data.env);
	free(data.pwd);

}