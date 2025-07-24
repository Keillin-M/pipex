/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmaeda <kmaeda@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 12:14:51 by kmaeda            #+#    #+#             */
/*   Updated: 2025/07/24 11:49:32 by kmaeda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static 

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

static void	ft_init(t_data *data)
{
	data->s_path = NULL;
	data->paths = NULL;
	data->path1 = NULL;
	data->path2 = NULL;
	data->cmd1 = NULL;
	data->cmd2 = NULL;
}

int	main(int argc, char **argv, char **envp)
{
	int	here_doc;
	t_data	data;
	
	here_doc = 0;
	if (argc < 5)
		return (ft_putstr_fd("Usage: ./pipex infile cmd1 .. cmdn outfile\n", 2), 1);
	ft_init(&data);
	if (ft_strncmp(argv[1], "here_doc", 9) == 0)
		here_doc = 1;
	if (here_doc)
	{

	}
	else
	{
		if (init_files(argv, &data))
			return (ft_clean_bonus(&data), 1);
		if (get_path_bonus(envp, argv, &data))
		{
			if (!data.path1)
				ft_printf("command not found: %s\n", argv[2]);
			if (!data.path2)
				ft_printf("command not found: %s\n", argv[3]);
			return (ft_clean(&data), 1);
		}
		pipex(&data, envp);
	}
	ft_clean(&data);
	return (0);
}
