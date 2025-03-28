/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toferrei <toferrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 14:29:42 by famendes          #+#    #+#             */
/*   Updated: 2025/03/28 20:28:30 by toferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
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

typedef struct s_env
{
	char			*name; //allocado
	char			*value; //allocado
	bool			exported;
	struct s_env	*next;
}		t_env;

typedef struct s_token
{
	int				token_type;
	char			*value; //allocado
	struct s_token	*next;
	struct s_token	*previous;
}		t_token;

typedef struct s_pipe
{
	int				pid;
	int				pipe[2];
	int				fd_in;
	int				fd_out;
	int				doc_pipe[2];
	bool			heredoc;
	bool			last_child;
	bool			bad_fd;
	char			*path;
	char			**red;
	char			**cmd;
	struct s_pipe	*next;
	struct s_pipe	*previous;
}		t_pipe;

typedef struct s_data
{
	char		*input;
	char		*home;
	char		*pwd;
	char		*pwd_with_till;
	char		**env_str_array;
	int			exit_status;
	int			line_nbr;
	bool		signaled;
	t_env		**env;
	t_token		*token;
	t_pipe		*cmd_tree;
}		t_data;

typedef enum Token_type
{
	REDIR_IN,
	REDIR_OUT,
	REDIR_APPEND,
	HEREDOC,
	PIPE,
	WORD,
}		t_Token_type;

/* Start */

void	show_starter(char **env, t_data *data);

/* Error and Cleaning */

void	free_all_data(t_data *data);
void	free_split_and_token(char **split, t_token *token);
void	free_stuff(t_data *data);
void	*safe_malloc(size_t size);
void	free_char_array(char **res);
void	clean_all_fds(t_pipe *tree);
void	exit_exit(t_data *data);

/* Initialize Data */

char	*fetch_home(void);
char	*get_till(void);
void	init_data(char **env, t_data *data);
void	env_to_list(t_data *data, char **env);
void	minimal_list_init(t_data *data);
char	*get_prompt(t_data *data);
void	update_prompt(t_data *data);
char	**cpy_from_env(t_env **env);

/* Parsing */

int		input_parser(t_data *data);
char	**ft_splits(char *str);
t_pipe	*cmd_lst_creation(t_token *token);
char	**add_prefix(char **res, char *value, char *prefix);
void	split_for_export(t_pipe *tree);

/* Expanse */

void	expanse_parse(t_data *data);
void	expand_str(t_token *token, t_data *data);
char	*get_var_name(t_token *token);
int		get_var_len(char *str, int i);
char	*get_var_values(char *var_name, t_env **env);
bool	valid_expansion(char *str, int i);
void	free_strs(char *str1, char *str2, char *str3);

/* Quotes */

bool	check_for_open_quotes(char *str);
bool	in_quotes(char const *str, int index);
bool	double_quotes(const char *str, int index);
bool	single_quote(const char *str, int index);
int		ft_isquote(char c);
void	remove_quotes(t_pipe *tree);

/* Token Functions */

t_token	*first_tokenazor(t_data *data, char **inputs);
t_token	*init_token(char *str);
void	second_tokenazor(t_token **token);

/* Executor */

void	executor(t_data *data);
int		is_builtin(char *command);
void	exec_builtin(char **cmd, t_data *data, t_pipe *tree);
void	child_process(t_pipe *tree, t_data *data);

/* Redirections Handler */

int		handle_redirections(t_pipe *cmd, t_data *data);
void	check_last_red_in(t_pipe *cmd);
int		exec_doc(char *str, t_pipe *cmd, t_data *data);
int		pipe_error(t_pipe *cmd);

/* Built - Ins */

void	environment(char **args, t_data *data);
void	export_bi(char **args, t_data *data);
void	change_directory_main(char **args, t_data *data);
char	*set_directory(char **args, char *curpath, t_data *data);
void	unset_env(char **args, t_data *data);
void	pwd(t_data *data);
void	echo(char **strstr, t_data *data, t_pipe *tree);
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

void	set_main_signals(void);
void	set_signals_to_default(void);
void	set_parent_signals(void);
void	set_signals_to_ignore(void);
void	ft_waitpid(int pid, t_data *data);
void	ctrl_d_msg_and_exit(char *input, char *str, t_pipe *pipe, t_data *data);

/* Data */

t_data	*minicall(void);

#endif
