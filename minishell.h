/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toferrei <toferrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 14:29:42 by famendes          #+#    #+#             */
/*   Updated: 2025/03/12 15:02:00 by toferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef	MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <errno.h>
# include <string.h>
# include <stdlib.h>
# include <stdbool.h>
# include <unistd.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <limits.h>
# include <signal.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <termios.h>
# include "Libft/libft.h"

//lista env

typedef struct s_env
{
	char			*name; //allocado
	char			*value; //allocado
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
	int				pid; //fork
	int				pipe[2]; //pipe
	int				fd_in;
	int				fd_out;
	int				doc_pipe[2]; //pipe
	bool			last_child;
	bool			bad_fd;
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

/* start */

void	show_starter(char **env, t_data *data);

/* error and cleaning */

void	free_all_data(t_data *data);
void	free_split_and_token(char **split, t_token *token);
void	free_stuff(t_data *data);
void	*safe_malloc(size_t size);
void	free_char_array(char **res);

/* init data */

char	*fetch_home(void);
char	*get_till(void);
void	init_data(char **env, t_data *data);
void	env_to_list(t_data *data, char **env);
void	minimal_list_init(t_data *data);

/* parsing */

int		input_parser(t_data *data);
char	**ft_splits(char *str);
t_pipe	*cmd_lst_creation(t_token *token);
char	**add_prefix(char **res, char *value, char *prefix);

/* expanse */

void	expanse_parse(t_data * data);
char	*get_var_name(t_token *token);
int		get_var_len(char *str, int i);
char	*get_var_values(char *var_name, t_env **env);

/* quotes shenanigan */

bool	in_quotes(char const *str, int index);
bool	double_quotes(const char *str, int index);
bool	single_quote(const char *str, int index);
int		ft_isquote(char c);
void	remove_quotes(t_pipe *tree);

/* token fuctions */

t_token		*first_tokenazor(t_data *data, char **inputs);
t_token 	*init_token(char *str);
void		second_tokenazor(t_token **token);

/* executor */

void	executor(t_data *data);
int		is_builtin(char *command);
void	exec_builtin(char **cmd, t_data *data);
void	child_process(t_pipe *tree, t_data *data);

/* red handler */

int		handle_redirections(t_pipe *cmd, t_data *data);
void	exec_doc(char *str, t_pipe *cmd, t_data *data);

/* Built - Ins */

void	environment(char **args, t_data *data);
void	export_bi(char **args, t_data *data);
void	change_directory(char **args, t_data *data);
char	*set_directory(char **args, char *curpath, t_data *data);
void	unset_env(char **args, t_data *data);
void	pwd(t_data *data);
void	echo(char **strstr, t_data *data);
void	builtin_exit(char **args, t_data *data);

/* List Fx */

void	ft_clean_list(t_env **lst);
void	ft_print_list(t_env **lst);
t_env	*check_for_variable(t_env *env, char *var_name);
char	*get_var_value(t_env *env, char *var_name);
void	ft_modified_lstadd_back(t_env **lst, t_env *new);
t_env	*ft_newnode(char *content, char *value, bool exported);
void	list_sorter(t_env **lst);
void	list_copier(t_env **source, t_env **dest);
int		ft_modifiedlstsize(t_env *lst);
size_t	size_until_symbol(char *str, char c);
char	*get_value_for_list(char *str);
bool	for_export(char *str);

/* Signals */

void	set_main_signals();
void	set_signals_to_default(void);
void	set_parent_signals(void);
void	set_signals_to_ignore(void);

/* Data */

t_data	*minicall(void);

#endif
