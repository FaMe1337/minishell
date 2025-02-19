/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toferrei <toferrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 16:22:31 by toferrei          #+#    #+#             */
/*   Updated: 2025/02/19 19:57:50 by toferrei         ###   ########.fr       */
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
	if (ac == 2)
	{
		printf( "deu cagada, o bjoetivo e tipo have uma string ./a.out cd [qualquer string aqui]");
		return 0;
	}
	args = av;

	env_to_list(&data, env);
	ft_print_list(data.env);
	write (1, "\n\n\n\n lista env inicial \n\n\n\n", 28);
	export_bi((char *[]){"export", "OLA", NULL}, &data);
	export_bi((char *[]){"export", NULL}, &data);
	write (1, "\n\n\n\n lista env inicial \n\n\n\n", 28);
	export_bi((char *[]){"export", "OLA=ola", NULL}, &data);


	export_bi((char *[]){"export", NULL}, &data);
	builtin_exit((char *[]){"exit", NULL} , &data);

}