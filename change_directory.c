/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_directory.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toferrei <toferrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 17:26:16 by toferrei          #+#    #+#             */
/*   Updated: 2025/03/10 18:12:19 by toferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	export_for_cd(t_data *data, char *env_var)
{
	char	oldpwd_var[4128];
	if (check_for_variable(*(data->env), "PWD"))
	{
		printf("\nsupposed value in pwd:%s:\n", get_var_value(*(data->env), "PWD"));
		ft_strlcpy(oldpwd_var, "OLDPWD=", sizeof(env_var));
		ft_strlcat(oldpwd_var, \
			get_var_value(*(data->env), "PWD"), \
			sizeof(oldpwd_var) + sizeof(get_var_value(*(data->env), "PWD")));
		printf("\nantes de mandar olpwd:%s:\n", oldpwd_var);
		export_bi((char *[]){"export", oldpwd_var, NULL}, data);
	}
	export_bi((char *[]){"export", env_var, NULL}, data);
}

void	change_directory(char **args, t_data *data)
{
	char	curpath[4096];
	char	env_var[4128];

	curpath[0] = '\0';
	if (!args[1] && !get_var_value(*(data->env), "HOME"))
	{
		write(2, "cd : HOME not set", 18);
		data->exit_status = 1;
		return ;
	}
	else if ((!args[1] && data->home) \
		|| !ft_strncmp(args[1], "~", ft_strlen(args[1])) \
		|| !ft_strncmp(args[1], "~/", ft_strlen("~/")))
	{
		ft_strlcat(curpath, data->home, ft_strlen(data->home) + 1);
		if (args[1] && ft_strncmp(args[1], "~", ft_strlen(args[1])) \
			&& ft_strncmp(args[1], "~/", ft_strlen(args[1])))
		{
			args[1]++;
			ft_strlcat(curpath, args[1], ft_strlen(data->pwd) + 1);
		}
	}
	else if (!ft_strncmp(args[1], "-", ft_strlen(args[1])))
	{
		if (!get_var_value(*(data->env), "OLDPWD"))
		{
			write(2, "cd : OLDPWD not set", 20);
			data->exit_status = 1;
			return ;
		}
		else
			ft_strlcat(curpath, get_var_value(*(data->env), "OLDPWD"), \
				ft_strlen(get_var_value(*(data->env), "OLDPWD")) + 1);
	}
	else if (!ft_strncmp(args[1], "/", ft_strlen("/")) \
		|| !ft_strncmp(args[1], ".", ft_strlen(args[1])) \
		|| !ft_strncmp(args[1], "..", ft_strlen(args[1])))
	{
		ft_strlcat(curpath, args[1], ft_strlen(args[1]) + 1);
	}
	else
	{
		printf("entrei \n%s\n", curpath);
		ft_strlcat(curpath, data->pwd, ft_strlen(data->pwd) + 1);
		ft_strlcat(curpath, "/", ft_strlen(data->pwd) + 3);
		ft_strlcat(curpath, args[1], \
			ft_strlen(args[1]) + ft_strlen(data->pwd) + 2);
	}
	if (chdir(curpath))
	{
		write(2, "cd: ", 5);
		data->exit_status = 1;
		return ;
	}
	if (getcwd(curpath, sizeof(curpath)) == NULL)
	{
		write(2, "pwd: ", 6);
		data->exit_status = 1;
		return ;
	}
	ft_strlcpy(env_var, "PWD=", sizeof(env_var));
	ft_strlcat(env_var, curpath, sizeof(env_var));
	update_pwd(data);
	printf("\n%s\n", env_var);
	export_for_cd(data, env_var);
	data->exit_status = 0;
}
