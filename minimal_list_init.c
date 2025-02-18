/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimal_list_init.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toferrei <toferrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 09:57:51 by toferrei          #+#    #+#             */
/*   Updated: 2025/02/18 11:59:38 by toferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// if (!envp

#include "builtins.h"

void	minimal_list_init(t_data *data)
{
	char *temp;
	t_env *temp1;
	temp = NULL;
	temp = getcwd(NULL, 0);

	temp1 = ft_newnode(ft_strdup("PWD="), temp, true);
	ft_modified_lstadd_back(data->env, temp1);
	env_to_list(data, (char *[]){"LS_COLORS=", "SHLVL=1", "PATH=/usr/local/bin:"
			"/usr/local/sbin:/usr/bin:/usr/sbin:/bin:/sbin", "_=/usr/bin/env", NULL});
}

// int main(int ac, char**av, char**env)
// {
// 	char **args;
// 	t_data data;

// 	data.env = NULL;
// 	data.pwd = NULL;
// 	data.pwd = getcwd(NULL, 0);
// 	data.home = "/home/etom";
// 	if (ac != 3)
// 	/* 
// 	{
// 		printf( "deu cagada, o bjoetivo e tipo have uma string ./a.out cd [qualquer string aqui]");
// 		return 0;
// 	} */
// 	args = av;
// 	args = (char *[]){"env", NULL};
// 	env = (char *[]){NULL};
// 	write (1, "ola", 4);

// 	env_to_list(&data, env);
// 	ft_print_list(data.env);
// 	ft_clean_list(data.env);
// 	free(data.pwd);
// 	write (1, "\ndepois clean\n", 15);
// 	// change_directory()
// }









































