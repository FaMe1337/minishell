/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimal_list_init.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toferrei <toferrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 09:57:51 by toferrei          #+#    #+#             */
/*   Updated: 2025/03/20 16:06:11 by toferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	minimal_list_init(t_data *data)
{
	char	*temp;
	t_env	*temp1;

	temp = NULL;
	temp = getcwd(NULL, 0);
	temp1 = ft_newnode(ft_strdup("PWD"), temp, true);
	ft_modified_lstadd_back(data->env, temp1);
	env_to_list(data, (char *[]){"LS_COLORS=", "SHLVL=1", \
		"PATH=/usr/local/bin:" \
		"/usr/local/sbin:/usr/bin:/usr/sbin:/bin:/sbin", \
		"_=/usr/bin/env", NULL});
}
