/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: famendes <famendes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 13:06:26 by famendes          #+#    #+#             */
/*   Updated: 2025/01/20 17:11:57 by famendes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int input_parser(t_data *data)
{
	char **inputs;
	int i = 0;

	inputs = ft_splits(data->input);
	//tokenizar o que recebo
	while (inputs[i])
		printf("%s\n", inputs[i++]);
}

