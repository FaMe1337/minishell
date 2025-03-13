/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_prompt.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toferrei <toferrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 12:52:38 by toferrei          #+#    #+#             */
/*   Updated: 2025/03/13 16:42:24 by toferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_path(t_data *data, char *pwd)
{
	char *temp;

	if (check_for_variable(*data->env, "HOME") && \
	!ft_strncmp(get_var_value(*data->env, "HOME"), \
	pwd, \
	ft_strlen(get_var_value(*data->env, "HOME"))))
	{
		temp = safe_malloc(sizeof * temp * ((ft_strlen(pwd) \
			- ft_strlen(get_var_value(*data->env, "HOME")) + 2)));
		temp[0] = '~';
		ft_strlcpy(temp + 1, \
			pwd + ft_strlen(get_var_value(*data->env, "HOME")), \
			ft_strlen(pwd) - ft_strlen(get_var_value(*data->env, "HOME")) + 1);
		printf("\n%s\n", temp);
		return (temp);
	}
	else
		return (ft_strdup(pwd));
}

static char	*get_name(t_data *data)
{
	if (!check_for_variable(*data->env, "NAME"))
		return ("name");
	else
		return (get_var_value(*data->env, "NAME"));
}

static char	*get_user(t_data *data)
{
	if (!check_for_variable(*data->env, "USER"))
		return ("user");
	else
		return (get_var_value(*data->env, "USER"));
}

char	*get_prompt(t_data *data)
{
	char	*line;
	int		size;
	char 	*temp;

	temp = get_path(data, data->pwd);
	size = ft_strlen(get_user(data)) \
		+ ft_strlen(get_name(data)) \
		+ ft_strlen(temp);
	line = safe_malloc(sizeof * line * (size + 4)); 
	ft_strlcat(line, get_user(data), size + 4);
	ft_strlcat(line, "@", size + 4);
	ft_strlcat(line, get_name(data), size + 4);
	ft_strlcat(line, ":", size + 4);
	ft_strlcat(line, temp, size + 4);
	ft_strlcat(line, "$", size + 4);
	free(temp);
	return (line);
}

void update_prompt(t_data *data)
{
	if (data->pwd_with_till)
		free(data->pwd_with_till);
	data->pwd_with_till = get_prompt(data);
}