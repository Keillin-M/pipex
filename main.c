/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmaeda <kmaeda@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 12:14:51 by kmaeda            #+#    #+#             */
/*   Updated: 2025/07/22 16:41:38 by kmaeda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	find_path(t_data *data, char *cmd)
{
	int	i;
	char	*temp;

	i = 0;
	temp = NULL;
	data->full = NULL;
	while (data->paths[i] != NULL)
	{
		temp = ft_strjoin(data->paths[i], "/");
		data->full = ft_strjoin(temp, cmd);
		if (access(data->full, X_OK) == 0)
			return (free(temp), 0);
		free(temp);
		free(data->full);
		i++;
	}
	if (temp)
		free(temp);
	if (data->full)
		free(data->full);
	return (1);
}

int	get_path(char **envp, char **argv, t_data *data)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
		{
			data->s_path = envp[i] + 5;
			break ;
		}
		i++;
	}
	data->cmd1 = ft_split(argv[2], ' ');
	data->cmd2 = ft_split(argv[3], ' ');
	data->paths = ft_split(data->s_path, ':');
	if (find_path(data, data->cmd1[0]) || find_path(data, data->cmd2[0]))
		return (1);
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	int	infile;
	int	outfile;
	t_data	data;

	if (argc != 5)
		return (ft_putstr_fd("Usage: ./pipex infile cmd1 cmd2 outfile\n", 2), 1);
	if (get_path(envp, argv, &data))
		return (ft_clean(&data), 1);
	ft_clean(&data);
	infile = open(argv[1], O_RDONLY);
	if (infile < 0)
		return ((ft_putstr_fd("Error: could not open infile\n", 2), 1);
	outfile = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (outfile < 0)
		return ((ft_putstr_fd("Error: Could not open outfile\n", 2), 1);
}
