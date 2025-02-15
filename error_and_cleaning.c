/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_and_cleaning.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: famendes <famendes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 17:14:12 by famendes          #+#    #+#             */
/*   Updated: 2025/02/09 16:46:21 by famendes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*safe_malloc(size_t size)
{
	void	*ret;

	ret = malloc(size);
	if (!ret)
	{
		ft_putstr_fd("Error allocating memory in Malloc\n", 2);
		return(NULL);
	}
	ft_memset(ret, '\0', size);
	return (ret);
}

void free_split_and_token(char **split, t_token *token)
{
	int	i;
	t_token *temp;

	i = 0;
	while (split[i])
	 free(split[i++]);
	free(split);
	temp = token;
	while (token)
	{
		token = token->next;
		free(temp);
		temp = token;
	}
}

void free_all_data(t_data *data)
{
	free(data->home);
	free(data->pwd);
	free(data->pwd_with_till);
}

void	free_stuff(t_data *data)
{
	t_token *current;

	if (data->exit_status == 2)
		free(data->input);
	while (data->token)
	{
		current = data->token->next;
		free(data->token->value);
		free(data->token);
		data->token = current;
	}
}
