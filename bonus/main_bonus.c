/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwhitley <jwhitley@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 16:16:57 by jwhitley          #+#    #+#             */
/*   Updated: 2024/07/12 17:56:47 by jwhitley         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex_bonus.h"

int	main(int argc, char **argv, char **env)
{
	t_data	*data;

	if (argc == 1)
		exit(EXIT_FAILURE);
	data = ft_calloc(1, sizeof(t_data));
	if (!data)
	{
		perror("Failed to allocate data struct");
		exit(EXIT_FAILURE);
	}
	b_populate_struct(argc, argv, env, data);
	b_execute_commands(data);
	b_free_data_struct(data);
	return (0);
}
