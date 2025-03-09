/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: famendes <famendes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 14:29:20 by famendes          #+#    #+#             */
/*   Updated: 2025/03/09 17:34:02 by famendes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	show_starter(char **env, t_data *data)
{
	init_data(env, data);
	while (1)
	{
		data->input = readline(data->pwd_with_till);
		if (!data->input)
		{
			ft_putstr_fd("exit\n", 2);
			break;
		}
		if (*data->input)
		{
			add_history(data->input);
			if (input_parser(data) == 1)
				executor(data);
			else
			{
				printf("%s\n", "failed parsing");
				data->exit_status = 2;
			}
		}
		//limpar tudo que foi usado para o parsing e execuçao
		free_stuff(data);
	}
	//limpar tudo que resta
	free_all_data(data);
	/*
		MEMORY IS CLEANED
	*/
}

int	main(int ac, char **av, char **env)
{
	(void) av;
	t_data data;

	if (ac == 1)
	{
		show_starter(env, &data);
	}
	return (0);
}

