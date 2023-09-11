/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwoiton <lwoiton@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 19:05:04 by lwoiton           #+#    #+#             */
/*   Updated: 2023/09/11 19:01:30 by lwoiton          ###   ########.fr       */
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

//------------------------------01_main_bonus.c-------------------------------//

void	execute(char *cmd, char *envp[]);
void	pipe_to_pipe(char *cmd, char *envp[]);
void	pipe_terminal_input(char *argv[]);
void	read_terminal_input(char *limiter, int *end);
int		main(int argc, char *argv[], char *envp[]);

//--------------------------------02_utils.c---------------------------------//
int		error_exit(char *msg);
void	free_2d_array(char **array);
int		open_file(char *file, int mode);
char	*get_paths(char *envp[], char *env_var_name);
char	*get_cmd_path(char *cmd, char *envp[]);
#endif
