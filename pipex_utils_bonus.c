/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmaeda <kmaeda@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 10:22:52 by kmaeda            #+#    #+#             */
/*   Updated: 2025/07/24 11:49:38 by kmaeda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static void	free_array(char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

void	ft_clean(t_data *data)
{
	if (data->infile >= 0)
		close(data->infile);
	if (data->outfile >= 0)
		close(data->outfile);
	if (data->cmd1)
		free_array(data->cmd1);
	if (data->cmd2)
		free_array(data->cmd2);
	if (data->paths)
		free_array(data->paths);
	if (data->path1)
		free(data->path1);
	if (data->path2)
		free(data->path2);
}

void	error_exit(t_data *data, char *msg)
{
	ft_putstr_fd(msg, 2);
	ft_clean_bonus(data);
	exit(1);
}

static char	*find_path(t_data *data, char *cmd)
{
	int		i;
	char	*temp;
	char	*full_path;

	i = 0;
	temp = NULL;
	full_path = NULL;
	while (data->paths[i] != NULL)
	{
		temp = ft_strjoin(data->paths[i], "/");
		full_path = ft_strjoin(temp, cmd);
		if (access(full_path, X_OK) == 0)
			return (free(temp), full_path);
		free(temp);
		free(full_path);
		i++;
	}
	if (temp)
		free(temp);
	if (full_path)
		free(full_path);
	return (NULL);
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
	data->path1 = find_path(data, data->cmd1[0]);
	data->path2 = find_path(data, data->cmd2[0]);
	if (!data->path1 || !data->path2)
		return (1);
	return (0);
}
