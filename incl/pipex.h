/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwoiton <lwoiton@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 19:05:04 by lwoiton           #+#    #+#             */
/*   Updated: 2023/08/24 16:43:51 by lwoiton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <fcntl.h>
# include <errno.h>
# include <stdio.h>
# define _GNU_SOURCE
# include "libft.h"

//---------------------------------01_main.c---------------------------------//

void	execute(char *cmd, char *envp[]);
void	parent_process(char *file_name, char *cmd, int *end, char *envp[]);
void	child_process(char *file_name, char *cmd, int *end, char *envp[]);
int		main(int argc, char *argv[], char *envp[]);

//--------------------------------02_utils.c---------------------------------//
int		error_exit(char *msg);
void	free_2d_array(char **array);
int		open_file(char *file, int mode);
char	*get_paths(char *envp[], char *env_var_name);
char	*get_cmd_path(char *cmd, char *envp[]);
#endif
