/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: famendes <famendes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 14:29:42 by famendes          #+#    #+#             */
/*   Updated: 2025/02/15 15:01:08 by famendes         ###   ########.fr       */
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
	int				index;
	char			*value; //allocado
	struct s_token *next;
	struct s_token *previous;
}		t_token;

typedef struct s_pipe
{
	int				pid;
	int				pipe[2];
	int				fd[2];
	int				has_doc;
	int				doc_pipe[2];
	bool			last_child;
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
	t_env		**env; //allocado, vai ser o tomas a gerir
	int			exit_status;
	t_token		*token; //allocado
	t_pipe		*pipe_list; //allocado
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
} Token_type;

//start
void	show_starter(char **env, t_data *data);

//error and cleaning
void	free_all_data(t_data *data);
void	free_split_and_token(char **split, t_token *token);
void	free_stuff(t_data *data);
void	*safe_malloc(size_t size);



//init data
char	*fetch_home(void);
char	*get_till(void);
void	init_data(char **env, t_data *data);
void	env_to_list(t_data *data, char **env);

//parsing
int		input_parser(t_data *data);
char	**ft_splits(char *str);

//quotes shenanigan
bool	check_for_open_quotes(char *str);
bool	in_quotes(char const *str, int index);
bool	double_quotes(const char *str, int index);
bool	single_quote(const char *str, int index);

//token
t_token		*first_tokenazor(t_data *data, char **inputs);
t_token 	*init_token(char *str);
void		second_tokenazor(t_token **token);
t_pipe		*pipe_lst__creation(t_token *token);

#endif
