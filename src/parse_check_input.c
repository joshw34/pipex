/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_check_input.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwhitley <jwhitley@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 15:45:14 by jwhitley          #+#    #+#             */
/*   Updated: 2024/07/11 20:55:59 by jwhitley         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

static	char	*set_cmd_path(char *cmd, char **paths)
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
	return (NULL);
}

static	void	cmd_and_path(char **args, t_data *data)
{
	char	**paths;

	paths = get_paths(data->env);
	if (args[1] != NULL && args[1][0] != '\0')
	{
		data->cmd1 = ft_split(args[1], ' ');
		data->cmd1_path = set_cmd_path(data->cmd1[0], paths);
	}
	if (args[2] != NULL && args[2][0] != '\0')
	{
		data->cmd2 = ft_split(args[2], ' ');
		data->cmd2_path = set_cmd_path(data->cmd2[0], paths);
	}
	free_array(paths);
}

static	void	arg_count(int count, t_data *data)
{
	if (count != 4)
	{
		if (count < 4)
			ft_putstr_fd("Error: Not Enough Arguments", 2);
		if (count > 4)
			ft_putstr_fd("Error: Too Many Arguments", 2);
		free_data_struct(data);
		exit(EXIT_FAILURE);
	}
}

void	populate_struct(int count, char **args, char **env, t_data *data)
{
	arg_count(count - 1, data);
	data->infile = args[1];
	data->outfile = args[4];
	data->env = env;
	cmd_and_path(args + 1, data);
}
