/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: famendes <famendes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 14:29:42 by famendes          #+#    #+#             */
/*   Updated: 2025/01/29 20:44:14 by famendes         ###   ########.fr       */
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
# include <limits.h>
# include "Libft/libft.h"

//todo
typedef struct s_token{
	int				token_type;
	int				index;
	char			*value; //allocado
	struct s_token *next;
	struct s_token *previous;
}		t_token;

//todo
typedef struct s_data{
	char		*input;
	char		*home; //allocado
	char		*pwd; //allocado
	char		*pwd_with_till; //allocado
	char		**env; //allocado, vai ser o tomas a gerir
	int			exit_status;
	t_token		*token; //allocado
}		t_data;

typedef enum {
	REDIR_IN ,
	REDIR_OUT,
	REDIR_APPEND,
	HEREDOC,
	PIPE,
	WORD,
	CMD,
	ARG,
	EXPAND,
} Token_type;

//start
void	show_starter(char **env, t_data *data);

//error and cleaning
void	free_all_data(t_data *data);
void	free_split_and_token(char **split, t_token *token);
void	free_stuff(t_data *data);



//init data
char	*fetch_home(void);
char	*get_till(void);
void	init_data(char **env, t_data *data);

//parsing
int		input_parser(t_data *data);
char	**ft_splits(char *str);

//quotes shenanigan
bool	check_for_open_quotes(char *str);
bool	in_quotes(char const *str, int index);
bool	double_quotes(const char *str, int index);
bool	single_quote(const char *str, int index);

//token
t_token	*first_tokenazor(t_data *data, char **inputs);
t_token *init_token(char *str);
void 	second_tokenazor(t_token *token);

#endif
