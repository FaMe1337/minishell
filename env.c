/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toferrei <toferrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 10:35:44 by toferrei          #+#    #+#             */
/*   Updated: 2025/02/07 14:57:02 by toferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void environment(char **args, t_data *data)
{
	t_env *env;
	printf("\nolaola\n");
	if (!data->env)
	{
		data->exit_code = 1;
		return ;
	}
	env = *(data->env);
	if (args[1])
	{
		write(1, "env: '", 6);
		write(1, args[1], ft_strlen(args[1]));
		write(1, "': No such file or directory\n", 29);
		data->exit_code = 127;
		return ;
	}
	while(data->env)
	{
		printf("%s=%s\n", env->name, env->value);
		env=env->next;
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
	args = (char *[]){"env", NULL};
	env_to_list(&data, env);
	write (1, "\ndepois en_to_list\n", 20);
	ft_print_list(data.env);
	write (1, "\ndepois print_list\n", 20);
	environment(args, &data);
	write (1, "\ndepois unset\n", 15);
	ft_print_list(data.env);
	ft_clean_list(data.env);
	free(data.env);
	free(data.pwd);
	write (1, "\ndepois clean\n", 15);
	// change_directory()
}