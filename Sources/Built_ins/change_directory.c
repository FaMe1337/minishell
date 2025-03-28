/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_directory.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toferrei <toferrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 17:26:16 by toferrei          #+#    #+#             */
/*   Updated: 2025/03/28 02:00:49 by toferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

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
	update_prompt(data);
}

static void	export_for_cd(t_data *data, char *env_var)
{
	char	oldpwd_var[4128];

	if (check_for_variable(*(data->env), "PWD"))
	{
		ft_strlcpy(oldpwd_var, "OLDPWD=", sizeof(env_var));
		ft_strlcat(oldpwd_var, \
			get_var_value(*(data->env), "PWD"), \
			sizeof(oldpwd_var) + sizeof(get_var_value(*(data->env), "PWD")));
		export_bi((char *[]){"export", oldpwd_var, NULL}, data);
	}
	export_bi((char *[]){"export", env_var, NULL}, data);
}

void	change_directory(char **args, t_data *data)
{
	char	curpath[4098];
	char	env_var[4128];

	curpath[0] = '\0';
	data->exit_status = 0;
	set_directory(args, curpath, data);
	if (data->exit_status == 1)
		return ;
	if (chdir(curpath))
	{
		write(2, "minishell: cd: ", 16);
		perror(args[1]);
		data->exit_status = 1;
		return ;
	}
	if (getcwd(curpath, sizeof(curpath)) == NULL)
	{
		perror("minishell: pwd: ");
		data->exit_status = 1;
		return ;
	}
	ft_strlcpy(env_var, "PWD=", sizeof(env_var));
	ft_strlcat(env_var, curpath, sizeof(env_var));
	update_pwd(data);
	export_for_cd(data, env_var);
}

void	change_directory_main(char **args, t_data *data)
{
	if (!args[1] || !args[2])
		change_directory(args, data);
	else
	{
		write(2, "minishell: cd: too many arguments\n", 35);
		data->exit_status = 1;
	}
		
}
