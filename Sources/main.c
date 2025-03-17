/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toferrei <toferrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 14:29:20 by famendes          #+#    #+#             */
/*   Updated: 2025/03/17 15:57:53 by toferrei         ###   ########.fr       */
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
			break ;
		}
		if (*data->input)
		{
			data->line_nbr++;
			add_history(data->input);
			if (input_parser(data) == 1)
				executor(data);
			else
			{
				printf("%s\n", "failed parsing");
				data->exit_status = 2;
			}
		}
		free_stuff(data);
	}
	exit_exit(data);
}

t_data	*minicall(void)
{
	static t_data	data;

	return (&data);
}

int	main(int ac, char **av, char **env)
{
	(void) av;
	if (ac == 1)
	{
		set_main_signals();
		show_starter(env, minicall());
	}
	return (0);
}
