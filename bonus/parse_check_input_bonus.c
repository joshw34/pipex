/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_check_input_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwhitley <jwhitley@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 15:45:14 by jwhitley          #+#    #+#             */
/*   Updated: 2024/07/12 18:19:28 by jwhitley         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex_bonus.h"

static	void	p_fd_and_pid(t_data *data)
{
	int	i;

	i = 0;
	data->p_fd = (int **)ft_calloc(data->cmd_count, sizeof(int *));
	while (i < data->cmd_count - 1)
	{
		data->p_fd[i] = (int *)ft_calloc(2, sizeof(int));
		i++;
	}
	data->p_fd[i] = NULL;
	data->pid = (pid_t *)ft_calloc(data->cmd_count, sizeof(pid_t));
	if (!data->p_fd || !data->pid)
	{
		perror("Failed to allocated memory for FD/PID");
		b_free_data_struct(data);
	}
}

static	char	*b_set_cmd_path(char *cmd, char **paths)
{
	char	*result;
	int		i;

	i = 0;
	while (paths[i])
	{
		result = ft_strjoin(paths[i], cmd);
		if (access(result, X_OK) == 0)
			return (result);
		else
			free(result);
		i++;
	}
	result = ft_strdup("");
	return (result);
}

static	void	b_cmd_and_path(char **args, t_data *data)
{
	char	**paths;
	int		i;

	i = 0;
	paths = b_get_paths(data->env);
	data->cmds = (char ***)ft_calloc(data->cmd_count + 1, sizeof(char **));
	data->cmd_paths = (char **)ft_calloc(data->cmd_count + 1, sizeof(char *));
	while (i < data->cmd_count)
	{
		if (args[i] != NULL && args[i][0] != '\0')
		{
			data->cmds[i] = ft_split(args[i], ' ');
			data->cmd_paths[i] = b_set_cmd_path(data->cmds[i][0], paths);
		}
		else
		{
			data->cmds[i] = ft_split("fakecmd fakecmd", ' ');
			data->cmd_paths[i] = ft_strdup("");
		}
		i++;
	}
	data->cmds[i] = NULL;
	data->cmd_paths[i] = NULL;
	b_free_array(paths);
}

static	void	b_arg_count(int count, t_data *data)
{
	if (count < 4)
	{
		ft_putstr_fd("Error: Not Enough Arguments", 2);
		b_free_data_struct(data);
		exit(EXIT_FAILURE);
	}
}

void	b_populate_struct(int ac, char **args, char **env, t_data *data)
{
	if (ft_strncmp(args[1], "here_doc", 7) == 0)
	{
		b_arg_count(ac - 2, data);
		data->infile = open("temp.txt", O_RDWR | O_CREAT | O_TRUNC, 0777);
		data->outfile = open(args[ac - 1], O_RDWR | O_CREAT | O_APPEND, 0666);
		data->env = env;
		data->cmd_count = ac - 4;
		read_here_doc(data, args[2]);
		b_cmd_and_path(args + 3, data);
		p_fd_and_pid(data);
	}
	else
	{
		b_arg_count(ac - 1, data);
		data->infile = open(args[1], O_RDONLY);
		data->outfile = open(args[ac - 1], O_RDWR | O_CREAT | O_TRUNC, 0666);
		data->env = env;
		data->cmd_count = ac - 3;
		b_cmd_and_path(args + 2, data);
		p_fd_and_pid(data);
	}
}
