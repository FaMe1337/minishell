/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: famendes <famendes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 14:29:42 by famendes          #+#    #+#             */
/*   Updated: 2025/02/23 23:23:32 by famendes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef	MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <errno.h>
# include <stdlib.h>
# include <stdbool.h>
# include <unistd.h>
#include  <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <limits.h>
# include "Libft/libft.h"

//lista env

typedef struct s_env
{
	char			*name;
	char			*value;
	bool			exported;
	struct s_env	*next;
}	t_env;

//todo
typedef struct s_token{
	int				token_type;
	char			*value; //allocado
	struct s_token *next;
	struct s_token *previous;
}		t_token;

typedef struct s_pipe
{
	int				pid;
	int				pipe[2]; //fork
	int				fd_in;
	int				fd_out;  //pipe
	int				doc_pipe[2];
	bool			last_child;
	bool			last_red_out;
	bool			bad_fd;
	bool			bad_command;
	char			*path;
	char			**red; //allocado
	char			**cmd; //allocado
	struct s_pipe	*next;
	struct s_pipe	*previous;
}			t_pipe;

//todo
typedef struct s_data{
	char		*input;
	char		*home; //allocado
	char		*pwd; //allocado
	char		*pwd_with_till; //allocado
	char		**env_str_array; //allocado
	int			exit_status;
	t_env		**env; //allocado, vai ser o tomas a gerir
	t_token		*token; //allocado
	t_pipe		*cmd_tree; //allocado
}		t_data;

typedef enum {
	REDIR_IN,
	REDIR_OUT,
	REDIR_APPEND,
	HEREDOC,
	PIPE,
	WORD,
} Token_type;

//start
void	show_starter(char **env, t_data *data);

//error and cleaning
void	free_all_data(t_data *data);
void	free_split_and_token(char **split, t_token *token);
void	free_stuff(t_data *data);
void	*safe_malloc(size_t size);
void	free_char_array(char **res);

//init data
char	*fetch_home(void);
char	*get_till(void);
void	init_data(char **env, t_data *data);
void	env_to_list(t_data *data, char **env);

//parsing
int		input_parser(t_data *data);
char	**ft_splits(char *str);
t_pipe	*cmd_lst_creation(t_token *token);
char	**add_prefix(char **res, char *value, char *prefix);

//parsing $
void	expanse_parse(t_data * data);
bool	valid_expansion(char *str, int i);
void	expand_str(t_token *token, t_data *data);
char	*get_var_name(t_token *token);
int		var_name_len(char *str, int i);
char	*get_var_values(char *var_name, t_env **env);

//quotes shenanigan
bool	check_for_open_quotes(char *str);
bool	in_quotes(char const *str, int index);
bool	double_quotes(const char *str, int index);
bool	single_quote(const char *str, int index);

//token fuctions
t_token		*first_tokenazor(t_data *data, char **inputs);
t_token 	*init_token(char *str);
void		second_tokenazor(t_token **token);

//executor
void	executor(t_data *data);

//red handler
int	handle_redirections(t_pipe *cmd);

#endif
