/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmaeda <kmaeda@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 12:14:51 by kmaeda            #+#    #+#             */
/*   Updated: 2025/07/28 15:22:31 by kmaeda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	init_arrays(t_data *data)
{
	int	i;

	i = 0;
	data->cmds = malloc(sizeof(char **) * (data->cmd_count + 1));
	data->path = malloc(sizeof(char *) * (data->cmd_count + 1));
	data->full_paths = malloc(sizeof(char **) * (data->cmd_count + 1));
	if (!data->cmds || !data->path || !data->full_paths)
		return (perror("Memory allocation failed\n"), 1);
	while (i <= data->cmd_count)
	{
		data->cmds[i] = NULL;
		data->path[i] = NULL;
		data->full_paths[i] = NULL;
		i++;
	}
	return (0);
}

static int	init_files(int argc, char **argv, t_data *data)
{
	data->infile = -1;
	data->outfile = -1;
	data->infile = open(argv[1], O_RDONLY);
	if (data->infile < 0)
		return (ft_putstr_fd("Error: could not open infile\n", 2), 1);
	data->outfile = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (data->outfile < 0)
		return (ft_putstr_fd("Error: Could not open outfile\n", 2), 1);
	return (0);
}

static void	ft_init(t_data *data)
{
	data->s_path = NULL;
	data->full_paths = NULL;
	data->path = NULL;
	data->cmds = NULL;
}

static int	pipex_main(int argc, char **argv, t_data *data, char **envp)
{
	int	i;

	i = 0;
	data->cmd_count = argc - 3;
	if (init_arrays(data))
		return (ft_clean(data), 1);
	if (init_files(argc, argv, data))
		return (ft_clean(data), 1);
	if (get_path(envp, argv, data))
	{
		while (i < data->cmd_count)
		{
			if (!data->path[i])
			{
				ft_printf("command not found: %s\n", argv[i + 2]);
				return (ft_clean(data), 1);
			}
			i++;
		}
	}
	parent(data, envp);
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	t_data	data;

	data.here_doc = 0;
	if (argc < 5)
		return (ft_putstr_fd("Usage: ./pipex infile cmd1 .. cmdn outfile\n", \
			2), 1);
	ft_init(&data);
	if (ft_strncmp(argv[1], "here_doc", 8) == 0)
		data.here_doc = 1;
	if (data.here_doc)
	{
		if (heredoc_main(argc, argv, &data, envp))
			return (1);
	}
	else
	{
		if (pipex_main(argc, argv, &data, envp))
			return (1);
	}
	ft_clean(&data);
	return (0);
}
