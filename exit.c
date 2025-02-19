/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toferrei <toferrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 11:14:05 by toferrei          #+#    #+#             */
/*   Updated: 2025/02/19 16:50:48 by toferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static long long	ft_atoll(const char *str)
{
	long long	nbr;
	int			parity;

	nbr = 0;
	parity = 0;
	while ((*str >= 9 && *str <= 13) || *str == 32)
		str++;
	while (*str == '+' || *str == '-')
	{
		if (*str == '-')
			parity++;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		nbr = nbr * 10 + (*str - '0');
		str++;
	}
	if (parity % 2 != 0)
		return (-nbr);
	return (nbr);
}

static bool	is_in_long_long_range(char *str)
{
	unsigned long long	threshold;
	unsigned long long	nbr;
	int					digit;

	threshold = (unsigned long long) LLONG_MAX;
	while ((*str >= 9 && *str <= 13) || *str == 32)
		str++;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			threshold++;
		str++;
	}
	nbr = 0;
	while (*str >= '0' && *str <= '9')
	{
		digit = *str - '0';
		if (nbr > (threshold - digit) / 10)
			return (false);
		nbr = nbr * 10 + digit;
		str++;
	}
	return (true);
}

bool	is_string_numeric(char *str)
{
	if (!*str)
		return (false);
	while(*str)
	{
		printf("%c\n", *str);
		if ((*str < '0' || *str > '9') && *str != '-' && *str != '+')
			return (false);
		str++;
	}
	return (true);
}

void	exit_exit(t_data *data)
{
	int code;

	code = data->exit_code;
	
	if (data->env)
		ft_clean_list(data->env);
	if (data->pwd)
		free(data->pwd);
	printf("exit\n");
	exit(code);
}

void	builtin_exit(char **args, t_data *data)
{
	if (!args[1])
	{
		data->exit_code = 0;
		exit_exit(data); // macro = 0;
	}
	if (args[2] && is_string_numeric(args[1]))
	{
		printf("minishell: exit: too many arguments\n");
		return ;
	}
	if (!is_string_numeric(args[1]) || !is_in_long_long_range(args[1]))
	{
		write(1, "minishell: exit: ", 18);
		write(1, args[1], ft_strlen(args[1]));
		write(1, ": numeric argument required\n", 29);
		data->exit_code = 2;
		exit_exit(data);
	}
	data->exit_code = (unsigned char)ft_atoll(args[1]);
	exit_exit(data);
}
