/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: famendes <famendes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 17:32:18 by famendes          #+#    #+#             */
/*   Updated: 2025/03/02 22:49:59 by famendes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	child_red_out(t_pipe *tree)
{
	if (tree->next != NULL)
	{
		//todo
	}
	if (tree->fd_out == 1)
		return ;
	dup2(tree->fd_out, STDOUT_FILENO);
	close(tree->fd_out);
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
		execve(path, tree->cmd, data->env_str_array);
		free(path);
	}
	write(2, tree->cmd[0], ft_strlen(tree->cmd[0]));
	ft_putstr_fd(" : command not found\n", 2);
	exit(127);
}

