/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   01_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwoiton <lwoiton@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 11:03:14 by luca              #+#    #+#             */
/*   Updated: 2023/08/23 18:48:00 by lwoiton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	error_exit(char *msg)
{
	ft_printf("Error: %s\n", msg);
	return (-1);
}

void	execute(char *cmd, char *envp[])
{
	char	**cmd_and_flags;
	char	*cmd_path;

	cmd_and_flags = ft_split(cmd, ' ');
	cmd_path = get_cmd_path(cmd, envp);
	if (execve(cmd_path, cmd_and_flags, envp) == -1)
	{
		free(cmd_and_flags);
		free(cmd_path);
		error_exit("Error at execution");
		return ;
	}
	free(cmd_and_flags);
	free(cmd_path);
	return ;
}

void	child_process(int fd_infile, char *cmd, int p_end[], char *envp[])
{
	dup2(fd_infile, STDOUT_FILENO);
	dup2(p_end[1], STDIN_FILENO);
	close(p_end[0]);
	execute(cmd, envp);
	return ;
}

void	parent_process(int fd_outfile, char *cmd, int p_end[], char *envp[])
{
	dup2(fd_outfile, STDOUT_FILENO);
	dup2(p_end[0], STDIN_FILENO);
	close(p_end[1]);
	execute(cmd, envp);
	return ;
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

int	main(int argc, char *argv[], char *envp[])
{
	int	end[2];
	pid_t	pid;

	if (argc != 5)
		return (error_exit("wrong number of arguments"));
	if (pipe(end) == -1)
		return (error_exit("Error for pipex"));
	pid = fork();
	if (pid == -1)
		return (error_exit("error forking"));
	if (pid == 0)
		child_process(open_file(argv[1], 0), argv[2], end, envp);
	parent_process(open_file(argv[4], 0), argv[3], end, envp);
	return (0);
}