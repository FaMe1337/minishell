/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_directory_set.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toferrei <toferrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 14:54:08 by toferrei          #+#    #+#             */
/*   Updated: 2025/03/18 16:10:46 by toferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*set_dir_sub1(char **args, char *curpath, t_data *data)
{
	int i;

	i = 0;
	// printf("passei aqui 1;%s\n", curpath);
	ft_strlcat(curpath, data->home, ft_strlen(data->home) + 1);
	// printf("curapth %s\n",curpath);
	if (args[1] && ft_strncmp(args[1], "~", ft_strlen(args[1])) \
		&& ft_strncmp(args[1], "~/", ft_strlen(args[1])))
	{
		// printf("args 1 antes:%s\n", args[1]);
		args[1]++;
		// printf("args 1 depois:%s\n", &args[1][1]);
		// printf("length %d %d\n", (int)ft_strlen(data->home), (int)ft_strlen(args[1]));
		ft_strlcat(curpath, args[1], \
			ft_strlen(data->home) \
			+ ft_strlen(args[1]) + 1);
		args[1]--;
	}
	// printf("size linha toda %d\n", (int)ft_strlen(curpath));
	// printf("passei aqui 2;%s\n", curpath);
	return (curpath);
}

static char	*set_dir_sub2(char *curpath, t_data *data)
{
	if (!get_var_value(*(data->env), "OLDPWD"))
	{
		write(2, "cd : OLDPWD not set\n", 21);
		data->exit_status = 1;
	}
	else
	{
		ft_strlcat(curpath, get_var_value(*(data->env), "OLDPWD"), \
			ft_strlen(get_var_value(*(data->env), "OLDPWD")) + 1);
		printf("%s\n", curpath);
	}
	return (curpath);
}

char	*set_directory(char **args, char *curpath, t_data *data)
{
	if (!args[1] && !get_var_value(*(data->env), "HOME"))
	{
		write(2, "cd : HOME not set\n", 19);
		data->exit_status = 1;
		return (NULL);
	}
	else if ((!args[1] && data->home) || !ft_strcmp(args[1], "~") \
		|| !ft_strncmp(args[1], "~/", ft_strlen("~/")))
		curpath = set_dir_sub1(args, curpath, data);
	else if (!ft_strcmp(args[1], "-"))
		curpath = set_dir_sub2(curpath, data);
	else if (!ft_strncmp(args[1], "/", ft_strlen("/")) \
		|| !ft_strcmp(args[1], ".") || !ft_strcmp(args[1], ".."))
		ft_strlcat(curpath, args[1], ft_strlen(args[1]) + 1);
	else
	{
		ft_strlcat(curpath, data->pwd, ft_strlen(data->pwd) + 1);
		ft_strlcat(curpath, "/", ft_strlen(data->pwd) + 3);
		ft_strlcat(curpath, args[1], \
			ft_strlen(args[1]) + ft_strlen(data->pwd) + 2);
	}
	// printf("passei aqui ;%s\n", curpath);
	return (curpath);
}
