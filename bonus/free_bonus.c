/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwhitley <jwhitley@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 18:20:26 by jwhitley          #+#    #+#             */
/*   Updated: 2024/07/12 18:20:31 by jwhitley         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex_bonus.h"

static	void	b_free_int_array(int **array)
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

void	b_free_array(char **array)
{
	int	i;

	i = 0;
	if (!array)
		return ;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

static	void	b_free_cmd_array(char ***cmds)
{
	int	i;

	i = 0;
	while (cmds[i])
	{
		b_free_array(cmds[i]);
		i++;
	}
	free(cmds);
}

void	b_free_data_struct(t_data *data)
{
	if (data->cmds != NULL)
		b_free_cmd_array(data->cmds);
	if (data->cmd_paths != NULL)
		b_free_array(data->cmd_paths);
	if (data->p_fd != NULL)
		b_free_int_array(data->p_fd);
	if (data->pid != NULL)
		free(data->pid);
	if (access("temp.txt", F_OK) != -1)
		unlink("temp.txt");
	free(data);
}
