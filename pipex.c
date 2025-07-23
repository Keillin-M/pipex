/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmaeda <kmaeda@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 10:24:33 by kmaeda            #+#    #+#             */
/*   Updated: 2025/07/23 16:01:05 by kmaeda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	child1(t_data *data, int *fd, char **envp)
{
	close(fd[0]);
	dup2(data->infile, STDIN_FILENO);
	dup2(fd[1], STDOUT_FILENO);
	close(fd[1]);
	if (execve(data->path1, data->cmd1, envp) == -1)
		error_exit(data, "command not found\n");
}

static void	child2(t_data *data, int *fd, char **envp)
{
	close(fd[1]);
	dup2(fd[0], STDIN_FILENO);
	dup2(data->outfile, STDOUT_FILENO);
	close(fd[0]);
	if (execve(data->path2, data->cmd2, envp) == -1)
		error_exit(data, "command not found\n");
}

void	pipex(t_data *data, char **envp)
{
	int		fd[2];
	pid_t	pid1;
	pid_t	pid2;

	if (pipe(fd) == -1)
		error_exit(data, "pipe failed\n");
	pid1 = fork();
	if (pid1 == -1)
		error_exit(data, "fork failed\n");
	if (pid1 == 0)
		child1(data, fd, envp);
	pid2 = fork();
	if (pid2 == -1)
		error_exit(data, "fork failed\n");
	if (pid2 == 0)
		child2(data, fd, envp);
	close(fd[0]);
	close(fd[1]);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
}
