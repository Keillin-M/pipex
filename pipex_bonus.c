/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmaeda <kmaeda@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 10:24:33 by kmaeda            #+#    #+#             */
/*   Updated: 2025/07/28 15:15:51 by kmaeda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static void	first_child(t_data *data, char **envp)
{
	close(data->fd[0]);
	dup2(data->infile, STDIN_FILENO);
	close(data->infile);
	dup2(data->fd[1], STDOUT_FILENO);
	close(data->fd[1]);
	if (execve(data->path[0], data->cmds[0], envp) == -1)
		error_exit(data, "command not found\n");
}

static void	last_child(t_data *data, char **envp)
{
	dup2(data->prev_fd, STDIN_FILENO);
	close(data->prev_fd);
	dup2(data->outfile, STDOUT_FILENO);
	close(data->outfile);
	if (execve(data->path[data->cmd_count - 1], \
		data->cmds[data->cmd_count - 1], envp) == -1)
		error_exit(data, "command not found\n");
}

static void	middle_child(t_data *data, int i, char **envp)
{
	dup2(data->prev_fd, STDIN_FILENO);
	close(data->prev_fd);
	dup2(data->fd[1], STDOUT_FILENO);
	close(data->fd[0]);
	close(data->fd[1]);
	if (execve(data->path[i], data->cmds[i], envp) == -1)
		error_exit(data, "command not found\n");
}

static void	pipex(t_data *data, pid_t *pid, int i, char **envp)
{
	if (i < data->cmd_count - 1 && pipe(data->fd) == -1)
		error_exit(data, "pipe failed\n");
	pid[i] = fork();
	if (pid[i] == -1)
		error_exit(data, "fork failed\n");
	if (pid[i] == 0)
	{
		if (i == 0)
			first_child(data, envp);
		else if (i == data->cmd_count - 1)
			last_child(data, envp);
		else
			middle_child(data, i, envp);
	}
	if (data->prev_fd != -1)
		close(data->prev_fd);
	if (i < data->cmd_count - 1)
	{
		close(data->fd[1]);
		data->prev_fd = data->fd[0];
	}
}

void	parent(t_data *data, char **envp)
{
	int		i;
	pid_t	*pid;

	i = 0;
	data->prev_fd = -1;
	if (data->cmd_count <= 0)
		error_exit(data, "no commands to execute\n");
	pid = malloc(sizeof(pid_t) * data->cmd_count);
	if (!pid)
		error_exit(data, "malloc failed\n");
	while (i < data->cmd_count)
	{
		pipex(data, pid, i, envp);
		i++;
	}
	if (data->prev_fd != -1)
		close(data->prev_fd);
	i = 0;
	while (i < data->cmd_count)
	{
		waitpid(pid[i], NULL, 0);
		i++;
	}
	free(pid);
}
