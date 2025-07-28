/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmaeda <kmaeda@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 15:34:05 by kmaeda            #+#    #+#             */
/*   Updated: 2025/07/27 16:00:46 by kmaeda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include "libft.h"
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>

typedef struct s_data
{
	int		infile;
	int		outfile;
	int		offset;
	int		cmd_count;
	int		here_doc;
	int		prev_fd;
	int		fd[2];
	char	*s_path;
	char	**path;
	char	***full_paths;
	char	***cmds;
}	t_data;

int		get_path(char **envp, char **argv, t_data *data);
int		heredoc_main(int argc, char **argv, t_data *data, char **envp);
int		init_arrays(t_data *data);
void	parent(t_data *data, char **envp);
void	error_exit(t_data *data, char *msg);
void	ft_clean(t_data *data);

#endif
