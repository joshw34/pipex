/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_commands.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwhitley <jwhitley@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 15:45:44 by jwhitley          #+#    #+#             */
/*   Updated: 2024/07/12 01:23:16 by jwhitley         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

static	void	execute_cmd2(t_data *data, int p_fd[])
{
	int	out_fd;

	close(p_fd[1]);
	out_fd = open(data->outfile, O_CREAT | O_RDWR | O_TRUNC, 0666);
	if (out_fd == -1)
	{
		perror("");
		close(p_fd[0]);
		free_data_struct(data);
		_exit(EXIT_FAILURE);
	}
	dup2(out_fd, STDOUT_FILENO);
	close(out_fd);
	dup2(p_fd[0], STDIN_FILENO);
	close(p_fd[0]);
	if (data->cmd2_path == NULL)
	{
		free_data_struct(data);
		_exit(EXIT_FAILURE);
	}
	execve(data->cmd2_path, data->cmd2, data->env);
	_exit(EXIT_FAILURE);
}

static	void	execute_cmd1(t_data *data, int p_fd[])
{
	int	in_fd;

	close(p_fd[0]);
	in_fd = open(data->infile, O_RDONLY);
	if (in_fd == -1)
	{
		perror("");
		close(p_fd[1]);
		free_data_struct(data);
		_exit(EXIT_FAILURE);
	}
	dup2(in_fd, STDIN_FILENO);
	close(in_fd);
	dup2(p_fd[1], STDOUT_FILENO);
	close(p_fd[1]);
	if (data->cmd1_path == NULL || data->cmd1_path[0] == '\0')
	{
		free_data_struct(data);
		_exit(EXIT_FAILURE);
	}
	execve(data->cmd1_path, data->cmd1, data->env);
	_exit(EXIT_FAILURE);
}

void	execute_commands(t_data *data)
{
	int		p_fd[2];
	int		status;
	pid_t	cpid1;
	pid_t	cpid2;

	pipe(p_fd);
	cpid1 = fork();
	if (cpid1 == 0)
		execute_cmd1(data, p_fd);
	cpid2 = fork();
	if (cpid2 == 0)
		execute_cmd2(data, p_fd);
	close(p_fd[0]);
	close(p_fd[1]);
	waitpid(cpid1, &status, 0);
	waitpid(cpid2, &status, 0);
}
