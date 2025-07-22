/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmaeda <kmaeda@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 15:34:05 by kmaeda            #+#    #+#             */
/*   Updated: 2025/07/22 16:41:06 by kmaeda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "libft.h"

typedef struct	s_data
{
	char	*cmd1;
	char	*cmd2;
	char	*full;
	char	*path;
	char	*s_path;
	char	**paths;
}	t_data;

#endif
