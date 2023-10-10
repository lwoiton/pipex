/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   01_main_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwoiton <lwoiton@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 11:03:14 by luca              #+#    #+#             */
/*   Updated: 2023/10/10 14:57:20 by lwoiton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	execute(char *cmd, char *envp[])
{
	char	**cmd_args;
	char	*path;

	cmd_args = ft_split(cmd, ' ');
	path = get_cmd_path(cmd_args[0], envp);
	if (execve(path, cmd_args, envp) == -1)
	{
		ft_putstr_fd(cmd_args[0], 2);
		ft_putendl_fd(": command not found", 2);
		free_2d_array(cmd_args);
		exit(EXIT_FAILURE);
	}
	free_2d_array(cmd_args);
	return ;
}

void	read_terminal_input(char *limiter, int *end)
{
	char	*line;

	close(end[0]);
	while (1)
	{
		line = get_next_line(STDIN_FILENO);
		if (ft_strncmp(line, limiter, ft_strlen(limiter)) == 0 && ft_strlen(line) - 1 == ft_strlen(limiter))
		{
			free(line);
			exit(EXIT_SUCCESS);
		}
		ft_putstr_fd(line, end[1]);
		free(line);
	}
	return ;
}

void	pipe_terminal_input(char *argv[])
{
	int		end[2];
	pid_t	pid;

	if (pipe(end) == -1)
		error_exit("pipe() failed\n");
	pid = fork();
	if (pid == -1)
		error_exit("fork() failed\n");
	if (!pid)
		read_terminal_input(argv[2], end);
	else
	{
		close(end[1]);
		dup2(end[0], STDIN_FILENO);
		wait(NULL);
	}
	return ;
}

void	pipe_to_pipe(char *cmd, char *envp[])
{
	int		end[2];
	pid_t	pid;

	if (pipe(end) == -1)
		error_exit("pipe() failed\n");
	pid = fork();
	if (pid == -1)
		error_exit("fork() failed\n");
	if (pid == 0)
	{
		dup2(end[1], STDOUT_FILENO);
		close(end[0]);
		execute(cmd, envp);
	}
	else
	{
		close(end[1]);
		dup2(end[0], STDIN_FILENO);
	}
	return ;
}

int	main(int argc, char *argv[], char *envp[])
{
	int		fd_out;
	int		index;

	if (argc < 5)
		error_exit("Not enough arguments (min: 5)\n\n\
Usage: ./pipex <infile> <cmd1> <cmd2> ... <cmdn> <outfile>");
	if (ft_strncmp(argv[1], "here_doc", 8) == 0)
	{
		if (argc < 6)
			error_exit("Not enough arguments (min: 6)\n\n\
Usage: ./pipex here_doc <LMITER> <cmd1> <cmd2> ... <cmdn> <outfile>");
		index = 3;
		fd_out = open_file(argv[argc - 1], 1);
		pipe_terminal_input(argv);
	}
	else
	{
		index = 2;
		fd_out = open_file(argv[argc - 1], 1);
		dup2(open_file(argv[1], 0), STDIN_FILENO);
	}
	while (index < argc - 2)
		pipe_to_pipe(argv[index++], envp);
	dup2(fd_out, STDOUT_FILENO);
	execute(argv[argc - 2], envp);
	return (0);
}
