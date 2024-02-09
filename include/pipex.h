/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpuiu <cpuiu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 09:43:41 by cpuiu             #+#    #+#             */
/*   Updated: 2024/02/09 11:29:42 by cpuiu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../Libft/libft.h"
# include <errno.h>
# include <fcntl.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/types.h>
# include <unistd.h>
# define ERROR_INPUT "pipex: input: No such file or directory"
# define ERROR_OUTPUT "Error output file!\n"
# define ERROR_PIPE "Error pipe\n"
# define ERROR_CMD "pipex: command not found: "
# define ERROR_ARGS "invalid number of arguments\n"
# define ERROR_FILE_PERMISSIONS "Permission denied\n"
# define ERROR_CMD_PATH "path not found\n"
# define ERROR_HERE_DOC "here_doc"
# define ERROR_ENVP "error envp"

typedef struct s_pipex
{
	pid_t	pid1;
	pid_t	pid2;
	int		in_fd;
	int		out_fd;
	char	**cmd_paths;
	char	**cmd_args;
	char	*cmd_path;
	int		fd[2];
	char	*paths;
}			t_pipex;

// processes
void		child_1(t_pipex pipex, char **argv, char **envp);
void		child_2(t_pipex pipex, char **argv, char **envp);
char		*find_path(char **envp);
void		free_process(t_pipex *pipex, char *process);
char		*get_cmd_path(char **paths, char *cmd);
// error management
void		errors(char *err);
int			error_message(char *err);
int			error_management(int argc, char **argv, t_pipex *pipex);
int			error_message_cmd(char *err, char **cmd);
int			error_message_output(char *err);
// utils
int			ft_wordcount(char *str);
char		*word_dupe(char *str, int len);
int			is_whitespace(char c);
char		**ft_split_quotes(char *str);
int			get_next_line(int const fd, char **line);

#endif