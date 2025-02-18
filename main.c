/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toferrei <toferrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 16:22:31 by toferrei          #+#    #+#             */
/*   Updated: 2025/02/18 16:23:05 by toferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	main(int ac, char **av, char **env)
{
	char **args;
	t_data data;

	data.env = NULL;
	data.pwd = NULL;
	data.pwd = getcwd(NULL, 0);
	data.home = "/home/etom";
	/* 
	if (ac != 3)
	{
		printf( "deu cagada, o bjoetivo e tipo have uma string ./a.out cd [qualquer string aqui]");
		return 0;
	} */
	args = av;
	args = (char *[]){"export", "OLA", NULL};
	env_to_list(&data, env);
	ft_print_list(data.env);

	export_bi(args, 1, &data);
	export_bi((char *[]){"export", "OLA=ola", NULL}, &data);


	export_bi((char *[]){"export", NULL}, 1, &data);
	builtin_exit((char *[]){"exit", NULL} , &data, 1);

}