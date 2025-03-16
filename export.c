/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toferrei <toferrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 10:38:05 by toferrei          #+#    #+#             */
/*   Updated: 2025/03/13 16:43:34 by toferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	is_valid_name_for_export(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (false);
	if (str[0] == '=' || ft_isdigit(str[0])
		|| (!ft_isalpha(str[0]) && str[0] != '_'))
		return (false);
	while (str[i] && str[i] != '=')
	{
		if (!ft_isalpha(str[i]) && !ft_isdigit(str[i]) && str[i] != '_')
			return (false);
		i++;
	}
	return (true);
}

static void	print_export(t_env **list)
{
	t_env	**copy;

	if (!list)
		return ;
	copy = malloc(sizeof * copy);
	if (!copy)
		return ;
	*copy = NULL;
	list_copier(list, copy);
	if (ft_modifiedlstsize(*copy) > 1)
		list_sorter(copy);
	ft_print_list(copy);
	ft_clean_list(copy);
}

void	export_bi(char **args, t_data *data)
{
	int	i;

	i = 1;
	data->exit_status = 0;
	if (!args[1])
	{
		print_export(data->env);
		return ;
	}
	while (args[i])
	{
		if (!is_valid_name_for_export(args[i]))
		{
			write(2, "minishell: export: \"", 21);
			write(2, args[i], ft_strlen(args[i]));
			write(2, "\": not a valid identifier\n", 26);
			data->exit_status = 1;
		}
		else
			env_to_list(data, (char *[]){args[i], NULL});
		i++;
	}
	update_prompt(data);
}
