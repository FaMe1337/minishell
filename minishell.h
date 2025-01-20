/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: famendes <famendes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 14:29:42 by famendes          #+#    #+#             */
/*   Updated: 2025/01/20 16:56:51 by famendes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef	MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <errno.h>
# include <stdlib.h>
# include <stdbool.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "Libft/libft.h"

//todo
typedef struct s_data
{
	char	*input;
	char	*home; //allocado
	char	*pwd; //allocado
	char	*pwd_with_till; //allocado
	//t_token		*token; //allocado
}t_data;

/* //todo
typedef struct s_token
{

} t_token; */

//start
void	show_starter(char **env, t_data *data);

//init data
char *fetch_home(void);
char *get_till(void);
void	init_data(char **env, t_data *data);

//parsing
char **ft_splits(char *str);


#endif
