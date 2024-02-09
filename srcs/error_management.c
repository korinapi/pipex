/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_management.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpuiu <cpuiu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 13:58:17 by cpuiu             #+#    #+#             */
/*   Updated: 2024/02/06 19:31:18 by cpuiu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

int	error_message(char *err)
{
	ft_putendl_fd(err, 2);
	exit(EXIT_FAILURE);
}

void	errors(char *err)
{
	perror(err);
	exit(EXIT_FAILURE);
}

int	error_message_output(char *err)
{
	ft_putstr_fd("pipex: no such file or directory: ", 2);
	ft_putendl_fd(err, 2);
	exit(EXIT_FAILURE);
}

int	error_message_cmd(char *err, char **cmd)
{
	(void)err;
	ft_putstr_fd("pipex: ", 2);
	ft_putstr_fd(cmd[0], 2);
	ft_putendl_fd(": command not found", 2);
	exit(127);
}

int	error_management(int argc, char **argv, t_pipex *pipex)
{
	(void)argv;
	if (argc < 5)
		error_message(ERROR_ARGS);
	if (pipe(pipex->fd) < 0)
		error_message(ERROR_PIPE);
	return (0);
}
