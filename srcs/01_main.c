/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   01_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwoiton <lwoiton@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 11:03:14 by luca              #+#    #+#             */
/*   Updated: 2023/08/24 09:06:23 by lwoiton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	error_exit(char *msg)
{
	ft_printf("Error: %s\n", msg);
	return (-1);
}

int	open_file(char *file, int mode)
{
	int	fd;

	if (mode == 0)
		fd = open(file, O_RDONLY);
	else if (mode == 1)
		fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else
		return (-1);
	return (fd);
}

void	execute(char *cmd, char *envp[])
{
	char	**cmd_args;
	char	*path;

	cmd_args = ft_split(cmd, ' ');
	path = get_cmd_path(cmd_args[0], envp);
	if (path == NULL)
	{
		ft_printf("Error: command not found\n");
		exit(1);
	}
	if (execve(path, cmd_args, envp) == -1)
	{
		ft_printf("Error: %s\n", strerror(errno));
		exit(1);
	}
	return ;
}

void	parent_process(char *file_name, char *cmd, int *end, char *envp[])
{
	int	fd_out;

	close(end[1]);
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	fd_out = open_file(file_name, 1);
	dup2(fd_out, STDOUT_FILENO);
	dup2(end[0], STDIN_FILENO);
	execute(cmd, envp);
	return ;
}

void	child_process(char *file_name, char *cmd, int *end, char *envp[])
{
	int	fd_in;

	close(end[0]);
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	fd_in = open_file(file_name, 0);
	dup2(fd_in, STDIN_FILENO);
	dup2(end[1], STDOUT_FILENO);
	execute(cmd, envp);
	return ;
}

int	main(int argc, char *argv[], char *envp[])
{
	int end[2];
	pid_t pid;

	if (argc != 5)
		return (error_exit("wrong number of arguments"));
	if (pipe(end) == -1)
		return (error_exit("pipe error"));
	pid = fork();
	if (pid == -1)
		return (error_exit("fork error"));
	if (pid == 0)
		child_process(argv[1], argv[2], end, envp);
	parent_process(argv[4], argv[3], end, envp);
	return (0);
}