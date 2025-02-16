/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_handler.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: famendes <famendes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 20:51:25 by famendes          #+#    #+#             */
/*   Updated: 2025/02/16 21:19:10 by famendes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	parse_redirections(char *str, t_pipe *cmd)
{
	int	error;

	error = 0;
	if(ft_strncmp(str, "RDI:", 4) == 0)
		error = red_in(str, cmd);
	else if (ft_strncmp(str, "DOC:", 4) == 0)
		error = here_doc();
	else if (ft_strncmp(str, "RDO:", 4) == 0)
		error = red_out();
	else if (ft_strncmp(str, "APP:", 4) == 0)
		error = append();
	if (error)
		return (1);
	return (0);
}

int	handle_redirections(t_pipe *cmd)
{
	t_pipe	*start;
	int		i;

	if (!cmd)
		return (1);
	start = cmd;
	while (start)
	{
		i = 0;
		while(start->red && start->red[i])
		{
			if (parse_redirections(start->red[i], cmd))
				return (1);
			i++;
		}
		start = start->next;
	}
	return (0);
}
