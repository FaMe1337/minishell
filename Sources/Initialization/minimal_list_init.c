/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimal_list_init.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: famendes <famendes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 09:57:51 by toferrei          #+#    #+#             */
/*   Updated: 2025/03/28 16:57:36 by famendes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	minimal_list_init(t_data *data)
{
	char	*temp;
	t_env	*temp1;

	if (!data->env)
	{
		data->env = safe_malloc(sizeof * data->env);
		*data->env = NULL;
	}
	temp = NULL;
	temp = getcwd(NULL, 0);
	printf("%s\n", temp);
	temp1 = ft_newnode(ft_strdup("PWD"), temp, true);
	ft_modified_lstadd_back(data->env, temp1);
	env_to_list(data, (char *[]){"LS_COLORS=", "SHLVL=1", \
		"PATH=/usr/local/bin:" \
		"/usr/local/sbin:/usr/bin:/usr/sbin:/bin:/sbin", \
		"_=/usr/bin/env", NULL});
}
