/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toferrei <toferrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 11:14:05 by toferrei          #+#    #+#             */
/*   Updated: 2025/02/17 13:47:26 by toferrei         ###   ########.fr       */
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


void	exit_exit(t_data *data)
{
	int code;

	code = data->exit_code;
	exit(code);
}

void	builtin_exit(char **args, t_data *data, int fd)
{
	long long value;

	if (!args[1])
	{
		data->exit_code = 0;
		exit_exit(data); // macro = 0;
	}
	if (args[2] && is_numeric(args[1]))
	{
		printf("minishell: exit: too many arguments\n");
		return ;
	}
	if (!is_numeric(args[1]) || !is_in_long_long_range(args[1]))
	{
		ft_put_str_fd("minishell: exit: ", 2);
		ft_put_str_fd(args[1], 2);
		ft_put_str_fd(": numeric argument required\n", 2);
		data->exit_code = 2;
		exit_exit(data);
	}
	value = ft_atoll(args[1]);
	data->exit_code = (unsigned char)value;
	exit_exit(data);
}

int main(void)
{
	unsigned char c;
	long long d;
	d = 100000;
	c = (unsigned char)d;
	printf("%d\n", c);
}