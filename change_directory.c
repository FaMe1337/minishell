/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_directory.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toferrei <toferrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 17:26:16 by toferrei          #+#    #+#             */
/*   Updated: 2025/01/30 17:40:22 by toferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

/* char *check_for_variable(t_env *env, char *var_name)
{

}
*/

void	env_to_list(t_data *data, char **env)
{
	data->env = malloc(sizeof * data->env);
	*data->env = NULL;
}

char *get_var_value(t_env *env, char *var_name)
{
	while (env != NULL)
	{
		if (!ft_strncmp(env->name, var_name, ft_strlen(env->name)))
		{
			return (env->value);
		}
	}
	return (NULL);
}

static void	update_pwd(t_data *data)
{
	char	*new_pwd;

	new_pwd = NULL;
	new_pwd = getcwd(NULL, 0);
	if (new_pwd)
	{
		free(data->pwd);
		data->pwd = new_pwd;
	}
}

void change_directory(char **args, int fd, t_data *data)
{
	char curpath[4096]; //change to PATH_MAX macro

	if (!args[1] && !get_var_value(*(data->env), "HOME"))
	{
		perror("cd : erro de nao have home"); //to do (write)
		return ;
	}
	else if((!args[1] && data->home) || !ft_strncmp(args[1], "~", ft_strlen(args[1])) || !ft_strncmp(args[1], "~/", ft_strlen("~/")))
	{
		ft_strlcat(curpath, data->home, ft_strlen(data->home) + 1);
		if (!ft_strncmp(args[1], "~/", ft_strlen("~/")) && ft_strncmp(args[1], "~/", ft_strlen(args[1])))
			ft_strlcat(curpath, data->pwd, ft_strlen(data->pwd) + 1);
	}
	else if(!ft_strncmp(args[1], "-", ft_strlen("-")))
	{
		if (!get_var_value(*(data->env), "OLDPWD")) // to do
		{
			perror("cd : erro de nao haver OLDPWD");
			return ;
		}
		else
			ft_strlcat(curpath, get_var_value(*(data->env), "OLDPWD"), ft_strlen(get_var_value(*(data->env), "OLDPWD")) + 1);
	}
	else if(ft_strncmp(args[1], "/", ft_strlen("/")))
	{
		ft_strlcat(curpath, data->pwd, ft_strlen(data->pwd) + 1);
	}
	printf("%s\n", curpath);
	// export(); // to do
	// data->exit_code = 0;

}

char **args_creator(char **av)
{
	char **result;

	result = malloc(sizeof * result * 2);
	result[0] = malloc (sizeof * result * ft_strlen(av[1]));
	result[1] = malloc (sizeof * result * ft_strlen(av[2]));
	ft_strlcpy(result[0], av[1], 1000);
	ft_strlcpy(result[1], av[2], 1000);
	return (result);
}

int	main(int ac, char **av, char **env)
{
	char **args;
	t_data *data;

	args = args_creator(av);
	int n = 0;
	env_to_list(&data, env);
	change_directory(args, 1, &data);





	// change_directory()
}