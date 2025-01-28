/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwhitley <jwhitley@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 15:46:10 by jwhitley          #+#    #+#             */
/*   Updated: 2024/07/12 01:26:03 by jwhitley         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

char	**get_paths(char **env)
{
	char	**result;
	char	*paths;
	char	*temp;
	int		i;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], "PATH=", 5) == 0)
			paths = ft_strtrim(env[i], "PATH=");
		i++;
	}
	result = ft_split(paths, ':');
	i = 0;
	while (result[i])
	{
		temp = ft_strjoin(result[i], "/");
		free(result[i]);
		result[i] = temp;
		i++;
	}
	free(paths);
	return (result);
}

void	free_array(char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

void	free_data_struct(t_data *data)
{
	if (data->cmd1 != NULL)
	{
		free_array(data->cmd1);
		data->cmd1 = NULL;
	}
	if (data->cmd2 != NULL)
	{
		free_array(data->cmd2);
		data->cmd2 = NULL;
	}
	if (data->cmd1_path != NULL)
	{
		free(data->cmd1_path);
		data->cmd1_path = NULL;
	}
	if (data->cmd2_path != NULL)
	{
		free(data->cmd2_path);
		data->cmd2_path = NULL;
	}
	free(data);
}
