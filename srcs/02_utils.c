/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   02_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwoiton <lwoiton@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 11:59:48 by lwoiton           #+#    #+#             */
/*   Updated: 2023/08/23 15:22:45 by lwoiton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pipex.h>

char	*get_paths(char *envp[], char *env_var_name)
{
	int		i;
	int		j;
	char	*env_var;

	i = 0;
	while (envp[i])
	{
		j = 0;
		while (envp[i][j] && envp[i][j] != '=')
			j++;
		env_var = ft_substr(envp[i], 0, j);
		if (ft_strncmp(env_var , env_var_name, ft_strlen(env_var_name)) == 0)
		{
			free(env_var);
			return (envp[i] + j + 1);
		}
		free(env_var);
		i++;
	}
	return (0);

}

char	*get_cmd_path(char *cmd, char *envp[])
{
	int		i;
	char	**paths;
	char	*slash_added;
	char	*cmd_path;

	paths = ft_split(get_paths(envp, "PATH"), ':');
	i = 0;
	while (paths[i])
	{
		slash_added = ft_strjoin(paths[i], "/");
		cmd_path = ft_strjoin(slash_added, cmd);
		free(slash_added);
		if (access(cmd_path, F_OK | X_OK) == 0)
		{
			free(paths);
			return (cmd_path);
		}
		i++;
		free(cmd_path);
	}
	free(paths);
	return (0);
}