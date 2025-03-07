/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_directory.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toferrei <toferrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 17:26:16 by toferrei          #+#    #+#             */
/*   Updated: 2025/02/19 16:53:16 by toferrei         ###   ########.fr       */
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
		free(data->pwd); 
		data->pwd = new_pwd;
	}
	free (new_pwd);
}

void change_directory(char **args, t_data *data)
{
	char curpath[4096]; //change to PATH_MAX macro
	char	env_var[4128];

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
	export_bi((char *[]){"export", env_var, NULL}, data);
	data->exit_code = 0;

}
