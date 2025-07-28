/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmaeda <kmaeda@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 16:34:31 by kmaeda            #+#    #+#             */
/*   Updated: 2025/07/27 16:07:29 by kmaeda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static void	read_heredoc(char *limiter, int write_fd)
{
	int		lim_len;
	int		line_len;
	char	*line;

	lim_len = ft_strlen(limiter);
	while (1)
	{
		write(1, "pipe heredoc> ", 14);
		line = get_next_line(STDIN_FILENO);
		if (!line)
			break ;
		if ((ft_strncmp(line, limiter, lim_len)) == 0 && line[lim_len] == '\n')
		{
			free(line);
			return ;
		}
		line_len = ft_strlen(line);
		write(write_fd, line, line_len);
		free(line);
	}
}

static int	heredoc_init_files(int argc, char **argv, t_data *data)
{
	int	pipe_fd[2];

	data->outfile = -1;
	data->outfile = open(argv[argc - 1], O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (data->outfile < 0)
		return (ft_putstr_fd("Error: Could not open outfile\n", 2), 1);
	if (pipe(pipe_fd) < 0)
		return (ft_putstr_fd("Error: pipe failed\n", 2), 1);
	read_heredoc(argv[2], pipe_fd[1]);
	close(pipe_fd[1]);
	data->infile = pipe_fd[0];
	return (0);
}

int	heredoc_main(int argc, char **argv, t_data *data, char **envp)
{
	int	i;

	i = 0;
	data->cmd_count = argc - 4;
	if (init_arrays(data))
		return (ft_clean(data), 1);
	if (heredoc_init_files(argc, argv, data))
		return (1);
	if (get_path(envp, argv, data))
	{
		while (i < data->cmd_count && data->cmds[i] && data->cmds[i][0])
		{
			if (!data->path[i])
				ft_printf("command not found: %s\n", data->cmds[i][0]);
			i++;
		}
		return (ft_clean(data), 1);
	}
	parent(data, envp);
	return (0);
}
