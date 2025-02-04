/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toferrei <toferrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 10:38:10 by toferrei          #+#    #+#             */
/*   Updated: 2025/02/04 12:35:58 by toferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void delete_node(t_env *env, char *var_name)
{
	t_env	*temp;

	temp = check_for_variable(env, var_name);
	while (env->next != temp)
		env = env->next;
	env->next = temp->next;
	free(temp->name);
	free(temp);
}

void	unset_env(char **args, t_data *data)
{
	int	i;

	i = 0;
	if (!args || !data->env)
	{
		data->exit_code = 1;
		return ;
	}
	while (args[++i])
		if (check_for_variable(*data->env, args[i]))
			delete_node(*data->env, args[i]);
	data->exit_code = 0;
}

int	main(int ac, char **av, char **env)
{
	char **args;
	t_data data;

	data.env = NULL;
	data.pwd = NULL;
	data.pwd = getcwd(NULL, 0);
	data.home = "/home/toferrei";
	if (ac != 3)
	/* 
	{
		printf( "deu cagada, o bjoetivo e tipo have uma string ./a.out cd [qualquer string aqui]");
		return 0;
	} */
	args = av;
	args = (char *[]){"unset", "OLA", NULL};
	env_to_list(&data, env);
	write (1, "\ndepois en_to_list\n", 20);
	ft_print_list(data.env);
	write (1, "\ndepois print_list\n", 20);
	unset_env(args, &data);
	write (1, "\ndepois unset\n", 15);
	ft_print_list(data.env);
	ft_clean_list(data.env);
	free(data.env);
	free(data.pwd);
	write (1, "\ndepois clean\n", 15);





	// change_directory()
}
