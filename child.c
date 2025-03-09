/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fabio <fabio@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 17:32:18 by famendes          #+#    #+#             */
/*   Updated: 2025/03/09 15:56:16 by fabio            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	child_red_out(t_pipe *tree)
{
	int i;
	bool has_red;

	i = 0;
	has_red = false;
	while (tree->red[i])
	{
		if (ft_strcmp(tree->cmd[i], "RDO") == 0 || \
			ft_strcmp(tree->cmd[i], "APP") == 0)
				has_red = true;
		i++;
	}
	if (tree->next != NULL && !has_red)
	{
		dup2(tree->pipe[1], STDOUT_FILENO);
		close(tree->pipe[1]);
	}
	else if (tree->fd_out > 2)
	{
		dup2(tree->fd_out, STDOUT_FILENO);
		close(tree->fd_out);
	}
}

static char	*find_path(char *cmd, char **envp)
{
	int		i;
	char	**paths;
	char	*result;
	char	*path;

	i = 0;
	while (ft_strncmp(envp[i], "PATH", 4) != 0)
		i++;
	paths = ft_split(envp[i] + 5, ':');
	i = 0;
	while (paths[i])
	{
		path = ft_strjoin(paths[i], "/");
		result = ft_strjoin(path, cmd);
		free(path);
		if (access(result, F_OK) == 0)
		{
			free_char_array(paths);
			return (result);
		}
		free(result);
		i++;
	}
	free_char_array(paths);
	return (NULL);
}

void	child_process(t_pipe *tree, t_data *data)
{
	char	*path;

	//red
	child_red_out(tree);
	//child_red_in(tree);
	//executar
	if (is_builtin(tree->cmd[0]))
		exec_builtin(tree->cmd, data);
	else if (access(tree->cmd[0], F_OK) == 0)
		execve(tree->cmd[0], tree->cmd, data->env_str_array);
	else
	{
		path = find_path(tree->cmd[0], data->env_str_array);
		if (!path)
			path = ft_strdup(tree->cmd[0]);
		execve(path, tree->cmd, data->env_str_array);
		free(path);
	}
	write(2, tree->cmd[0], ft_strlen(tree->cmd[0]));
	ft_putstr_fd(" : command not found\n", 2);
	exit(127);
}

