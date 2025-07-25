/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmaeda <kmaeda@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 17:23:56 by kmaeda            #+#    #+#             */
/*   Updated: 2025/07/25 18:37:57 by kmaeda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static void	free_array(char **array)
{
	int	i;

	i = 0;
	if (!array)
		return ;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

void	ft_clean(t_data *data)
{
	int	i;

	i = 0;
	if (data->infile >= 0)
		close(data->infile);
	if (data->outfile >= 0)
		close(data->outfile);
	while (i < data->cmd_count)
	{
		if (data->cmds[i])
			free_array(data->cmds[i]);
		if (data->path && data->path[i])
			free(data->path[i]);
		if (data->full_paths && data->full_paths[i])
			free_array(data->full_paths[i]);
		i++;
	}
	if (data->cmds)
		free(data->cmds);
	if (data->path)
		free(data->path);
	if (data->full_paths)
		free(data->full_paths);
}

void	error_exit(t_data *data, char *msg)
{
	ft_putstr_fd(msg, 2);
	ft_clean(data);
	exit(1);
}
