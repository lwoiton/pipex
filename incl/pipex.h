/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwoiton <lwoiton@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 19:05:04 by lwoiton           #+#    #+#             */
/*   Updated: 2023/08/23 18:41:30 by lwoiton          ###   ########.fr       */
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
# define _GNU_SOURCE
# include "libft.h"

typedef struct	s_pipex
{
	char	*file_in;
	int		fd_file_in;
	char	*file_out;
	int		fd_file_out;
	char	**cmd1;
	char	**cmd2;
	int		fd_pipe[2];
	pid_t	cpid;
}	t_pipex;

# define INT_MAX 2147483647
# define INT_MIN -2147483648

//---------------------------------01_main.c---------------------------------//
int	error_exit(char *msg);
void	execute(char *cmd, char *envp[]);
void	child_process(int fd_infile, char *cmd, int p_end[], char *envp[]);
void	parent_process(int fd_outfile, char *cmd, int p_end[], char *envp[]);
int	open_file(char *file, int mode);

//--------------------------------02_utils.c---------------------------------//
char	*get_paths(char *envp[], char *env_var_name);
char	*get_cmd_path(char *cmd, char *envp[]);

#endif
