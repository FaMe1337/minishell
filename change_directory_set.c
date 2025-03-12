/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_directory_set.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toferrei <toferrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 14:54:08 by toferrei          #+#    #+#             */
/*   Updated: 2025/03/12 15:04:34 by toferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*set_dir_sub1(char **args, char *curpath, t_data *data)
{
	ft_strlcat(curpath, data->home, ft_strlen(data->home) + 1);
		if (args[1] && ft_strncmp(args[1], "~", ft_strlen(args[1])) \
			&& ft_strncmp(args[1], "~/", ft_strlen(args[1])))
		{
			args[1]++;
			ft_strlcat(curpath, args[1], ft_strlen(data->pwd) + 1);
		}
	return (curpath);
}

static char	*set_dir_sub2(char *curpath, t_data *data)
{
	if (!get_var_value(*(data->env), "OLDPWD"))
	{
		write(2, "cd : OLDPWD not set", 20);
		data->exit_status = 1;
		return (NULL);
	}
	else
	{
		ft_strlcat(curpath, get_var_value(*(data->env), "OLDPWD"), \
			ft_strlen(get_var_value(*(data->env), "OLDPWD")) + 1);
		printf("%s\n", check_for_variable(*(data->env), "PWD")->value);
	}
	return (curpath);
}

char	*set_directory(char **args, char *curpath, t_data *data)
{
	if (!args[1] && !get_var_value(*(data->env), "HOME"))
	{
		write(2, "cd : HOME not set", 18);
		data->exit_status = 1;
		return (NULL);
	}
	else if ((!args[1] && data->home) || !ft_strcmp(args[1], "~") \
		|| !ft_strncmp(args[1], "~/", ft_strlen("~/")))
		ft_strlcat(curpath, set_dir_sub1(args, curpath, data), 4096);
	else if (!ft_strcmp(args[1], "-"))
		ft_strlcat(curpath, set_dir_sub2(curpath, data), 4096);
	else if (!ft_strncmp(args[1], "/", ft_strlen("/")) \
		|| !ft_strcmp(args[1], ".")	|| !ft_strcmp(args[1], ".."))
		ft_strlcat(curpath, args[1], ft_strlen(args[1]) + 1);
	else
	{
		ft_strlcat(curpath, data->pwd, ft_strlen(data->pwd) + 1);
		ft_strlcat(curpath, "/", ft_strlen(data->pwd) + 3);
		ft_strlcat(curpath, args[1], \
			ft_strlen(args[1]) + ft_strlen(data->pwd) + 2);
	}
	return (curpath);
}
