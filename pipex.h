/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmaeda <kmaeda@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 15:34:05 by kmaeda            #+#    #+#             */
/*   Updated: 2025/07/23 16:01:27 by kmaeda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "libft.h"
# include <unistd.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>

typedef struct s_data
{
	int		infile;
	int		outfile;
	char	*path1;
	char	*path2;
	char	*s_path;
	char	**cmd1;
	char	**cmd2;
	char	**paths;
}	t_data;

int		get_path(char **envp, char **argv, t_data *data);
void	error_exit(t_data *data, char *msg);
void	pipex(t_data *data, char **envp);
void	ft_clean(t_data *data);

#endif
