/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_commands_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwhitley <jwhitley@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 15:45:44 by jwhitley          #+#    #+#             */
/*   Updated: 2024/07/12 01:34:06 by jwhitley         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex_bonus.h"

static	void	b_execute_middle(t_data *data, int i)
{
	dup2(data->p_fd[i - 1][0], STDIN_FILENO);
	close(data->p_fd[i - 1][0]);
	dup2(data->p_fd[i][1], STDOUT_FILENO);
	close(data->p_fd[i][1]);
	close(data->p_fd[i][0]);
	if (data->cmd_paths[i] == NULL || data->cmd_paths[i][0] == '\0')
	{
		b_free_data_struct(data);
		_exit(EXIT_FAILURE);
	}
	execve(data->cmd_paths[i], data->cmds[i], data->env);
	_exit(EXIT_FAILURE);
}

static	void	b_execute_last(t_data *data, int i)
{
	if (data->outfile == -1)
	{
		close(data->p_fd[i - 1][0]);
		_exit(EXIT_FAILURE);
	}
	dup2(data->p_fd[i - 1][0], STDIN_FILENO);
	dup2(data->outfile, STDOUT_FILENO);
	close(data->outfile);
	if (data->cmd_paths[i] == NULL || data->cmd_paths[i][0] == '\0')
	{
		b_free_data_struct(data);
		_exit(EXIT_FAILURE);
	}
	execve(data->cmd_paths[i], data->cmds[i], data->env);
	_exit(EXIT_FAILURE);
}

static	void	b_execute_first(t_data *data, int i)
{
	if (data->infile == -1)
	{
		close(data->p_fd[i][0]);
		close(data->p_fd[i][1]);
		b_free_data_struct(data);
		_exit(EXIT_FAILURE);
	}
	dup2(data->infile, STDIN_FILENO);
	close(data->infile);
	dup2(data->p_fd[i][1], STDOUT_FILENO);
	close(data->p_fd[i][1]);
	close(data->p_fd[i][0]);
	if (data->cmd_paths[i] == NULL || data->cmd_paths[i][0] == '\0')
	{
		b_free_data_struct(data);
		_exit(EXIT_FAILURE);
	}
	execve(data->cmd_paths[i], data->cmds[i], data->env);
	_exit(EXIT_FAILURE);
}

static	void	b_execute_child_processes(t_data *data, int i)
{
	if (i == 0)
		b_execute_first(data, i);
	else if (i == data->cmd_count - 1)
		b_execute_last(data, i);
	else
		b_execute_middle(data, i);
}

void	b_execute_commands(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->cmd_count)
	{
		if (i < data->cmd_count - 1)
			pipe(data->p_fd[i]);
		data->pid[i] = fork();
		if (data->pid[i] == 0)
			b_execute_child_processes(data, i);
		if (i < data->cmd_count - 1)
			close(data->p_fd[i][1]);
		if (i > 0)
			close(data->p_fd[i - 1][0]);
		i++;
	}
	i = 0;
	while (i < data->cmd_count)
	{
		waitpid(data->pid[i], NULL, 0);
		i++;
	}
}
