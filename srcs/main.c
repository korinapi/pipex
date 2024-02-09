/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpuiu <cpuiu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 18:17:46 by cpuiu             #+#    #+#             */
/*   Updated: 2024/02/09 11:43:43 by cpuiu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

char	*find_path(char **envp)
{
	if (envp == NULL || envp[0] == NULL)
		return (ft_strdup("/bin:/usr/bin"));
	while (ft_strncmp("PATH", *envp, 4))
		envp++;
	return (*envp + 5);
}

void	close_and_wait(t_pipex *pipex)
{
	close(pipex->fd[0]);
	close(pipex->fd[1]);
}

int	mandatory(char **envp, char **argv, t_pipex pipex)
{
	int	status;

	status = 0;
	pipex.paths = find_path(envp);
	pipex.cmd_paths = ft_split(pipex.paths, ':');
	pipex.pid1 = fork();
	if (pipex.pid1 == 0)
		child_1(pipex, argv, envp);
	pipex.pid2 = fork();
	if (pipex.pid2 == 0)
		child_2(pipex, argv, envp);
	close_and_wait(&pipex);
	waitpid(pipex.pid1, &status, 0);
	waitpid(pipex.pid2, &status, 0);
	free_process(&pipex, "parent");
	return (WEXITSTATUS(status));
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex			pipex;
	int				status;

	status = 0;
	if (argc == 5)
	{
		pipe(pipex.fd);
		status = mandatory(envp, argv, pipex);
	}
	if (argc > 5 || argc < 5)
		error_message(ERROR_ARGS);
	return (status);
}
