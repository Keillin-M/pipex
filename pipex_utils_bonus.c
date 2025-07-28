/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmaeda <kmaeda@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 10:22:52 by kmaeda            #+#    #+#             */
/*   Updated: 2025/07/28 15:23:11 by kmaeda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static char	*find_path(char **paths, char *cmd)
{
	int		i;
	char	*temp;
	char	*full_path;

	i = 0;
	temp = NULL;
	full_path = NULL;
	while (paths[i])
	{
		temp = ft_strjoin(paths[i], "/");
		if (!temp)
			return (NULL);
		full_path = ft_strjoin(temp, cmd);
		free(temp);
		if (!full_path)
			return (NULL);
		if (access(full_path, X_OK) == 0)
			return (full_path);
		free(full_path);
		i++;
	}
	return (NULL);
}

static int	get_commands(char **argv, t_data *data)
{
	int	i;
	int	start;

	i = 0;
	if (data->here_doc)
		start = 3;
	else
		start = 2;
	data->cmds = malloc(sizeof(char **) * (data->cmd_count + 1));
	if (!data->cmds)
		return (1);
	while (i < data->cmd_count)
	{
		data->cmds[i] = ft_split(argv[i + start], ' ');
		if (!data->cmds[i])
			return (1);
		i++;
	}
	data->cmds[i] = NULL;
	return (0);
}

static int	parse_commands(char **argv, t_data *data)
{
	int	i;

	i = 0;
	if (get_commands(argv, data) != 0)
		return (1);
	while (i < data->cmd_count)
	{
		if (!data->cmds[i] || !data->cmds[i][0])
			return (1);
		data->full_paths[i] = ft_split(data->s_path, ':');
		if (!data->full_paths[i])
			return (1);
		data->path[i] = find_path(data->full_paths[i], data->cmds[i][0]);
		i++;
	}
	return (0);
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
	if (!data->s_path)
		return (1);
	if (parse_commands(argv, data))
		return (1);
	while (i < data->cmd_count)
	{
		if (!data->path[i])
			return (1);
		i++;
	}
	return (0);
}
