/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_directory.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toferrei <toferrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 17:26:16 by toferrei          #+#    #+#             */
/*   Updated: 2025/01/31 02:43:43 by toferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

/* char *check_for_variable(t_env *env, char *var_name)
{

}
*/

void	ft_print_list(t_env **lst)
{
	t_env *temp;

	temp = *lst;
	if (lst == NULL)
	{
		printf("Tried printing empty list\n");
		return ;
	}
	while (temp != NULL)
	{
		printf("%s=", temp->name);
		printf("%s\n", temp->value);
		temp = temp->next;
	}
}

t_env	*ft_modifiedlstlast(t_env *lst)
{
	t_env	*temp;

	if (!lst)
		return (NULL);
	temp = lst;
	while (temp->next)
		temp = temp->next;
	return (temp);
}

t_env	*ft_newnode(char *content, char *value)
{
	t_env	*elem;

	elem = malloc(sizeof * elem);
	if (!elem)
		return (NULL);
	elem->name = content;
	elem->value = value;
	elem->next = NULL;
	return (elem);
}

void	ft_modified_lstadd_back(t_env **lst, t_env *new)
{
	t_env	*last;

	last = ft_modifiedlstlast(*lst);
	if (!last)
	{
		*lst = new;
		return ;
	}
	last->next = new;
}

size_t size_until_symbol(char * str, char c)
{
	int n = 0;

	if (!str || !c)
		return (0);
	while (str[n] && str[n] != c)
	{
		n++;
	}
	return (n);
}

char *get_value_for_list(char * str)
{
	while (*str != '=')
		str++;
	return (str);
}

void	env_to_list(t_data *data, char **env)
{
	t_env *temp;
	char *temp1;
	// char *temp2;

	int n = 0;
	data->env = malloc(sizeof * data->env);
	*data->env = NULL;
	while (env[n])
	{
		temp1 = malloc (ft_strlen(env[n] + 1));
		printf("%ld\n", size_until_symbol(env[n], '=') + 1);
		ft_strlcpy(temp1, env[n], size_until_symbol(env[n], '=') + 1);
		printf("%s\n", temp1);
		temp = ft_newnode(temp1, get_value_for_list(env[n]));
		ft_modified_lstadd_back(data->env, temp);
		n++;
		free (temp1);
	}
}

char *get_var_value(t_env *env, char *var_name)
{
	while (env != NULL)
	{
		if (!ft_strncmp(env->name, var_name, ft_strlen(var_name)))
		{
			return (env->value);
		}
		env= env->next;
	}
	return (NULL);
}

static void	update_pwd(t_data *data)
{
	char	*new_pwd;

	new_pwd = NULL;
	new_pwd = getcwd(NULL, 0);
	if (new_pwd)
	{
		free(data->pwd);
		data->pwd = new_pwd;
	}
}



void change_directory(char **args, int fd, t_data *data)
{
	char curpath[4096]; //change to PATH_MAX macro

	curpath[0] = '\0';
	if (!args[1] && !get_var_value(*(data->env), "HOME"))
	{
		perror("cd : erro de nao have home"); //to do (write)
		// data->exit_code = ; to do
		return ;
	}
	else if((!args[1] && data->home) || !ft_strncmp(args[1], "~", ft_strlen(args[1])) || !ft_strncmp(args[1], "~/", ft_strlen("~/")))
	{
		ft_strlcat(curpath, data->home, ft_strlen(data->home) + 1);
		if (ft_strncmp(args[1], "~", ft_strlen("~")) && ft_strncmp(args[1], "~/", ft_strlen(args[1])))
			ft_strlcat(curpath, data->pwd, ft_strlen(data->pwd) + 1);
	}
	else if(!ft_strncmp(args[1], "-", ft_strlen("-")))
	{
		if (!get_var_value(*(data->env), "OLDPWD")) // to do
		{
			perror("cd : erro de nao haver OLDPWD");
			// data->exit_code = ; to do
			return ;
		}
		else
			ft_strlcat(curpath, get_var_value(*(data->env), "OLDPWD"), ft_strlen(get_var_value(*(data->env), "OLDPWD")) + 1);
	}
	else if(!ft_strncmp(args[1], "/", ft_strlen("/")) ||
		!ft_strncmp(args[1], ".", ft_strlen(args[1])) ||
		!ft_strncmp(args[1], "..", ft_strlen(args[1])))
	{
		ft_strlcat(curpath, args[1], ft_strlen(args[1] + 1));
	}
	else
	{
		ft_strlcat(curpath, data->pwd, ft_strlen(data->pwd) + 1);
		ft_strlcat(curpath, "/", ft_strlen(data->pwd) + 3);
		ft_strlcat(curpath, args[1], ft_strlen(args[1]) + ft_strlen(data->pwd) + 2);
	}
	printf("olaolaola: %s\n", curpath);
	// export(); // to do
	// data->exit_code = 0;

}

char **args_creator(char **av)
{
	char **result;

	result = malloc(sizeof * result * 2);
	result[0] = malloc (sizeof * result * ft_strlen(av[1]));
	result[1] = malloc (sizeof * result * ft_strlen(av[2]));
	ft_strlcpy(result[0], av[1], 1000);
	ft_strlcpy(result[1], av[2], 1000);

	return (result);
}

int	main(int ac, char **av, char **env)
{
	char **args;
	t_data data;

	data.pwd = "/home/etom/Escola42/minishell";
	if (ac != 3)
	{
		printf( "deu cagada, o bjoetivo e tipo have uma string ./a.out cd [qualquer string aqui]");
		return 0;
	}
	args = args_creator(av);
	int n = 0;
	env_to_list(&data, env);
	ft_print_list(data.env);
	change_directory(args, 1, &data);





	// change_directory()
}