/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: famendes <famendes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 14:29:42 by famendes          #+#    #+#             */
/*   Updated: 2025/01/22 20:44:14 by famendes         ###   ########.fr       */
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
typedef struct s_data{
	char	*input;
	char	*home; //allocado
	char	*pwd; //allocado
	char	*pwd_with_till; //allocado
	char	**env; //allocado, vai ser o tomas a gerir
	int		exit_status;
	t_token		*token; //allocado
}		t_data;

//todo
typedef struct s_token{
	int		token_type;
	int		index;
	char	*value;
	struct s_token *next;
	struct s_token *previous;
}		t_token;

typedef enum {
	REDIR_IN ,
	REDIR_OUT,
	REDIR_APPEND,
	HEREDOC,
	PIPE,
	CMD,
	ARG,
	WORD,
} Token_type;

//start
void	show_starter(char **env, t_data *data);

//init data
char *fetch_home(void);
char *get_till(void);
void	init_data(char **env, t_data *data);

//parsing
int input_parser(t_data *data);
bool	check_for_open_quotes(char *str);
char **ft_splits(char *str);

//token
t_token *first_tokenazor(t_data *data, char **inputs);

#endif
