/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toferrei <toferrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 15:25:17 by famendes          #+#    #+#             */
/*   Updated: 2025/02/03 19:07:48 by toferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_data(char **env, t_data *data)
{
	data->home = fetch_home();
	data->pwd = getcwd(NULL, 0);
	env_to_list(data, env);
	data->pwd_with_till = get_till();
	data->token = NULL;
	data->exit_status = 0;
}


char *fetch_home(void)
{
	char	*cwd;
	char	*result;
	int	count;
	int	i;

	i = 0;
	count = 0;
	cwd = getcwd(NULL, 0);
	while (cwd[i])
	{
		if (cwd[i] == '/')
			count++;
		if (count == 3)
			break;
		i++;
	}
	result = malloc(i + 1);
	if (!result)
		return (NULL);
	result[i] = '\0';
	while (--i >= 0)
		result[i] = cwd[i];
	free(cwd);
	return (result);
}

char *get_till(void)
{
	char	*cwd;
	char	*result;
	int	i;
	int count;

	count = 0;
	cwd = getcwd(NULL, 0);
	i = ft_strlen(cwd);
	while (cwd[--i] != '/' && i >= 0)
		count++;
	result = malloc(count + 5);
	if (!result)
		return (NULL);
	result[0] = '~';
	ft_strlcpy(result + 1, cwd + i, count + 2);
	ft_strlcat(result, "->", count + 5);
	free(cwd);
	return (result);
}
