/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toferrei <toferrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 16:22:31 by toferrei          #+#    #+#             */
/*   Updated: 2025/02/20 17:02:10 by toferrei         ###   ########.fr       */
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

	env_to_list(&data, env, 0);
	ft_print_list(data.env, 1);
	write (1, "\n\n\n\n first step \n\n\n\n", 21);
	export_bi((char *[]){"export", "OLA", NULL}, &data);
	export_bi((char *[]){"export", NULL}, &data);
	write (1, "\n\n\n\n second step \n\n\n\n", 22);
	export_bi((char *[]){"export", "OLA=ola", NULL}, &data);
	export_bi((char *[]){"export", NULL}, &data);
	builtin_exit((char *[]){"exit", NULL} , &data);

}