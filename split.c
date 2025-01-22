/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: famendes <famendes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 16:57:46 by famendes          #+#    #+#             */
/*   Updated: 2025/01/22 20:38:37 by famendes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


char **ft_splits(char *str)
{
	int	i;
	int i2;
	int i3;
	char **result;

	i = 0;
	i2 = 0;
	result = malloc(ft_strlen(str) + 1);
	while (str[i] <= 32)
		i++;
	while (str[i])
	{
		if (str[i] > 33)
		{
			i3 = 0;
			result[i2] = malloc(1000);
			while (str[i] > 33)
				result[i2][i3++] = str[i++];
			result[i2++][i3] = '\0';
		}
		else
			i++;
	}
	result[i2] = '\0';
	return (result);
}

/* int main (void)
{
	char *str1 = " "" "" "" "" "" ";
	char **str;
	int i = 0;
	str = ft_splits(str1);
	if (!str || !str[i][0])
	{
		free(str);
		return (1);
	}
	while (str[i])
		printf("%s\n", str[i++]);

} */
