/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   01_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwoiton <lwoiton@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 11:03:14 by luca              #+#    #+#             */
/*   Updated: 2023/08/25 14:30:17 by luca             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	execute(char *cmd, char *envp[])
{
	char	**cmd_args;
	char	*path;

	cmd_args = ft_split(cmd, ' ');
	path = get_cmd_path(cmd_args[0], envp);
	if (execve(path, cmd_args, envp) == -1)
	{
		ft_putstr_fd("Error: command not found: ", 2);
		ft_putendl_fd(cmd_args[0], 2);
		free_2d_array(cmd_args);
		exit(1);
	}
	free_2d_array(cmd_args);
	return ;
}
 
void	parent_process(char *file_name, char *cmd, int *end, char *envp[])
{
	int	fd_out;
	int	wstatus;

	wait(&wstatus);
	ft_printf("wstatus: %d\n", WEXITSTATUS(wstatus));
	if (WIFEXITED(wstatus) && WEXITSTATUS(wstatus) == 1)
	{
		perror("Error: child process exited with error");
		exit(-1);
	}
	else
	{
		fd_out = open_file(file_name, 1);
		dup2(fd_out, STDOUT_FILENO);
		dup2(end[0], STDIN_FILENO);
		close(end[1]);
		execute(cmd, envp);
	}
	return ;
}

void	child_process(char *file_name, char *cmd, int *end, char *envp[])
{
	int	fd_in;

	fd_in = open_file(file_name, 0);
	if (fd_in == -1)
		perror("E3");
	dup2(fd_in, STDIN_FILENO);
	dup2(end[1], STDOUT_FILENO);
	close(end[0]);
	execute(cmd, envp);
	return ;
}

int	main(int argc, char *argv[], char *envp[])
{
	int		end[2];
	pid_t	pid;

	if (argc < 5)
		return (error_exit("Error: Wrong number of arguments"));
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
