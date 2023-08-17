/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   01_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwoiton <lwoiton@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 11:03:14 by luca              #+#    #+#             */
/*   Updated: 2023/08/17 16:24:42 by lwoiton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	error_exit(char *msg)
{
	ft_printf("Error: %s\n", msg);
	return (-1);
}

int	parse_args(int argc, char *argv[], t_pipex *args)
{
	if (argc != 5)
		return (error_exit("wrong number of arguments"));
	args->fd_file_in = open(argv[1], O_RDONLY);
	args->fd_file_out = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (args->fd_file_in == -1 || args->fd_file_out == -1)
		return (error_exit("could not open file"));
	args->file_in = argv[1];
	args->file_out = argv[4];
	args->cmd1 = ft_split(argv[2], ' ');	//its probably enough to just read in the string in order to execute the command
	args->cmd2 = ft_split(argv[3], ' ');	//its probably enough to just read in the string in order to execute the command
	if (args->cmd1 == NULL || args->cmd2 == NULL)
		return (error_exit("malloc failed"));
	return (0);
}

int	create_pipe(t_pipex *args)
{
	int	pipefd[2];

	if (pipe(pipefd) == -1)
		return (error_exit("pipe failed"));
	args->fd_pipe[0] = pipefd[0];
	args->fd_pipe[1] = pipefd[1];
	return (0);
}

int	create_fork(t_pipex *args)
{
	args->cpid = fork();
	if (args->cpid == -1)
	{
//		strerror("fork");
//		exit(EXIT_FAILURE);
		return (error_exit("fork failed"));
	}
	return (0);
}

int	read_from_child_process(t_pipex *args)
{
	int		status;

	if (args->cpid == 0)
	{
		close(args->fd_pipe[0]);
		dup2(args->fd_pipe[1], STDOUT_FILENO);
		close(args->fd_pipe[1]);
		execve(args->cmd1[0], args->cmd1, NULL);
	}
	else
	{
		close(args->fd_pipe[1]);
		dup2(args->fd_pipe[0], STDIN_FILENO);
		close(args->fd_pipe[0]);
		execve(args->cmd2[0], args->cmd2, NULL);
	}
	waitpid(args->cpid, &status, 0);
	return (0);
}

char	**cmd_path(char *cmd1, char *cmd2, char **envp)
{
	char	**path;
	char	*tmp;

	tmp = getenv("PATH");
	path = ft_split(tmp, ':');
	return (path);
}

void	pipex(int f1, int f2, char *cmd1, char *cmd2)
{
	int	end[2];
	int	status;
	pid_t	cpid1;
	pid_t	cpid2;

	if (pipe(end) == -1)
		return (-1);
	cpid1 = fork();
	if (cpid1 == -1)
		return (perror("Fork: "));
	if (cpid1 == 0)
		handle_child1(f1, cmd1);
	cpid2 = fork();
	if (cpid2 == -1)
		return (perror("Fork: "));
	if (cpid2 == 0)
		handle_child2(f2, cmd2);
	close(end[0]);
	close(end[1]);
	waitpid(cpid1, &status, 0);
	waitpid(cpid2, &status, 0);
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
	if (argc != 5)
		return (error_exit("wrong number of arguments"));
	pipex(open_file(argv[1], 0), open_file(argv[4], 1), argv[2], argv[3]);
	
	t_pipex	*args;

	args = malloc(sizeof(t_pipex));
	if (args == NULL)
		return (error_exit("malloc failed"));
	if (parse_args(argc, argv, args) == -1)
		return (-1);
	if (create_pipe(args) == -1)
		return (-1);
	if (create_fork(args) == -1)
		return (-1);
	if (read_from_child_process(args) == -1)
		return (-1);
	
	//create pipe
	//fork
	//child 1: dup2 pipe[1] stdout, close pipe[0], execve
	//child 2: dup2 pipe[0] stdin, close pipe[1], execve
	//parent: close pipe[0], close pipe[1], waitpid
	//free
	return (0);
}