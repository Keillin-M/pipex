/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmaeda <kmaeda@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 12:14:51 by kmaeda            #+#    #+#             */
/*   Updated: 2025/07/23 15:16:02 by kmaeda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	init_files(char **argv, t_data *data)
{
	data->infile = -1;
	data->outfile = -1;
	data->infile = open(argv[1], O_RDONLY);
	if (data->infile < 0)
		return (ft_putstr_fd("Error: could not open infile\n", 2), 1);
	data->outfile = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (data->outfile < 0)
		return (ft_putstr_fd("Error: Could not open outfile\n", 2), 1);
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	t_data	data;

	data.s_path = NULL;
	data.paths = NULL;
	data.path1 = NULL;
	data.path2 = NULL;
	data.cmd1 = NULL;
	data.cmd2 = NULL;
	if (argc != 5)
		return (ft_putstr_fd("Usage: ./pipex infile cmd1 cmd2 outfile\n", 2), 1);
	if (get_path(envp, argv, &data))
		return (ft_clean(&data), 1);
	if (init_files(argv, &data))
		return (ft_clean(&data), 1);
	pipex(&data, envp);
	ft_clean(&data);
	return (0);
}
