/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toferrei <toferrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 17:27:30 by toferrei          #+#    #+#             */
/*   Updated: 2025/02/19 20:00:15 by toferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H

# define BUILTINS_H

# include <stdio.h>
# include <unistd.h>
# include <string.h>
# include <stdbool.h>
# include <limits.h>
# include "Libft/libft.h"

typedef struct s_env
{
	char			*name;
	char			*value;
	struct s_env	*next;
	bool			exported;

}	t_env;

typedef struct s_data
{
	size_t			exit_code;
	t_env			**env;
	char			*pwd;
	char			*home;
}	t_data;

void export_bi(char **args, t_data *data);

// coisas para o env

void	ft_clean_list(t_env **lst);
void	ft_print_list(t_env **lst, bool exported);
void	env_to_list(t_data *data, char **env);
t_env	*check_for_variable(t_env *env, char *var_name);
char	*get_var_value(t_env *env, char *var_name);
void	ft_modified_lstadd_back(t_env **lst, t_env *new);
t_env	*ft_newnode(char *content, char *value, bool exported);
void	minimal_list_init(t_data *data);
void	builtin_exit(char **args, t_data *data);

#endif
