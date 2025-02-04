/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_directory.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toferrei <toferrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 17:26:16 by toferrei          #+#    #+#             */
/*   Updated: 2025/02/04 12:23:07 by toferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static void	update_pwd(t_data *data)
{
	char	*new_pwd;

	new_pwd = NULL;
	new_pwd = getcwd(NULL, 0);
	if (new_pwd)
	{
		//free(data->pwd); 
		data->pwd = new_pwd;
	}
	free (new_pwd);
}

void change_directory(char **args, int fd, t_data *data)
{
	char curpath[4096]; //change to PATH_MAX macro
	char	env_var[4128];

	if (fd)
	{

	}
	curpath[0] = '\0';
	if (!args[1] && !get_var_value(*(data->env), "HOME"))
	{
		perror("cd : erro de nao have home"); //to do (write)
		// data->exit_code = ; to do
		return ;
	}
	else if((!args[1] && data->home) || !ft_strncmp(args[1], "~", ft_strlen(args[1])) \
		|| !ft_strncmp(args[1], "~/", ft_strlen("~/")))
	{
		ft_strlcat(curpath, data->home, ft_strlen(data->home) + 1);


		write (1, "\npila\n", 7);
		printf("\n\n aqui tou a tentar algo curpath : %s\n\n", curpath);
		printf("\n\n args : %s\n\n", args[1]);
		printf("condition 1 %d:\n", ft_strncmp(args[1], "~", ft_strlen(args[1])));
		printf("condition 2 %d:\n", ft_strncmp(args[1], "~/", ft_strlen("~/")));

	
		if (ft_strncmp(args[1], "~", ft_strlen(args[1])) && ft_strncmp(args[1], "~/", ft_strlen(args[1])))
		{
			args[1]++;
			ft_strlcat(curpath, args[1], ft_strlen(data->pwd) + 1);
		}
	}
	else if(!ft_strncmp(args[1], "-", ft_strlen(args[1])))//vai buscar um strcmp da forma que tens falha se escreveres mais no args[1]
	{
		if (!get_var_value(*(data->env), "OLDPWD")) // to do
		{
			perror("cd : erro de nao haver OLDPWD");
			// data->exit_code = ; to do
			return ;
		}
		else
			ft_strlcat(curpath, get_var_value(*(data->env), "OLDPWD"), ft_strlen(get_var_value(*(data->env), "OLDPWD")) + 1);
	}
	else if(!ft_strncmp(args[1], "/", ft_strlen("/")) ||
		!ft_strncmp(args[1], ".", ft_strlen(args[1])) ||
		!ft_strncmp(args[1], "..", ft_strlen(args[1])))
	{
		ft_strlcat(curpath, args[1], ft_strlen(args[1] + 1));
	}
	else
	{
		ft_strlcat(curpath, data->pwd, ft_strlen(data->pwd) + 1);
		ft_strlcat(curpath, "/", ft_strlen(data->pwd) + 3);
		ft_strlcat(curpath, args[1], ft_strlen(args[1]) + ft_strlen(data->pwd) + 2);
	}
	printf("olaolaola: %s\n", curpath);

	if (chdir(curpath))
	{
		perror("minishell: cd: ");
		data->exit_code = 1;
		return ;
	}
	if (getcwd(curpath, sizeof(curpath)) == NULL)
	{
		perror("minishell: pwd: ");
		data->exit_code = 1;
		return ;
	}
	ft_strlcpy(env_var, "PWD=", sizeof(env_var));
	ft_strlcat(env_var, curpath, sizeof(env_var));
	printf("%s\n", env_var);
	update_pwd(data);
	//export((char *[]){"export", env_var, NULL}, fd);
	data->exit_code = 0;
	// data->exit_code = 0;

}

/* char **args_creator(char **av)
{
	char **result;

	result = malloc(sizeof * result * 2);
	result[0] = malloc (sizeof * result * ft_strlen(av[1]) + 1);
	if (av[2])
		result[1] = malloc (sizeof * result * ft_strlen(av[2]) + 1);
	if (result[0])
		ft_strlcpy(result[0], av[1], ft_strlen(av[1]) + 1);
	if (result[1])
		ft_strlcpy(result[1], av[2], ft_strlen(av[2]) + 1);

	return (result);
} */

int	main(int ac, char **av, char **env)
{
	char **args;
	t_data data;

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
	args = (char *[]){"cd", "-", NULL};
	env_to_list(&data, env);
	write (1, "\ndepois en_to_list\n", 20);
	ft_print_list(data.env);
	write (1, "\ndepois print_list\n", 20);
	change_directory(args, 1, &data);
	write (1, "\ndepois cd\n", 12);
	ft_clean_list(data.env);
	free(data.env);
	write (1, "\ndepois clean\n", 15);





	// change_directory()
}