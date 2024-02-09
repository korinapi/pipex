/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpuiu <cpuiu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 18:17:46 by cpuiu             #+#    #+#             */
/*   Updated: 2024/02/09 11:30:42 by cpuiu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex_bonus.h"

static void	creat_pipes(t_pipex_bonus *pipex)
{
	int	i;

	i = 0;
	while (i < pipex->arg_nb - 1)
	{
		if (pipe(pipex->pip + 2 * i) < 0)
			parent_free(pipex);
		i++;
	}
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

int	bonus(int argc, char **envp, char **argv, t_pipex_bonus pipex)
{
	int	status;

	status = 0;
	pipex.arg_nb = argc - 3 - pipex.here_doc;
	pipex.pip_nb = 2 * (pipex.arg_nb - 1);
	pipex.pip = (int *)malloc(sizeof(int) * pipex.pip_nb);
	if (!pipex.pip)
		errors(ERROR_PIPE);
	pipex.envp_path = find_path(envp);
	pipex.cmd_paths = ft_split(pipex.envp_path, ':');
	if (!pipex.cmd_paths)
		pipe_free(&pipex);
	creat_pipes(&pipex);
	pipex.index = -1;
	while (++(pipex.index) < pipex.arg_nb)
		child(pipex, argv, envp);
	close_pipes(&pipex);
	waitpid(pipex.pid, &status, 0);
	parent_free(&pipex);
	return (WEXITSTATUS(status));
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex			pipex;
	t_pipex_bonus	pipex_bonus;
	int				status;

	if (argc == 5)
	{
		pipe(pipex.fd);
		status = mandatory(envp, argv, pipex);
	}
	if (argc == 6 && !ft_strncmp(argv[2], "here_doc", 9))
	{
		get_infile(argv, &pipex_bonus);
		get_outfile(argv[argc - 1], &pipex_bonus);
		status = bonus(argc, envp, argv, pipex_bonus);
	}
	else if (argc > 5)
	{
		get_infile(argv, &pipex_bonus);
		get_outfile(argv[argc - 1], &pipex_bonus);
		status = bonus(argc, envp, argv, pipex_bonus);
	}
	return (status);
}
