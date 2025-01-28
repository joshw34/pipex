/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwhitley <jwhitley@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 15:46:10 by jwhitley          #+#    #+#             */
/*   Updated: 2024/07/12 18:23:27 by jwhitley         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex_bonus.h"

char	**b_get_paths(char **env)
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

char	*b_get_next_line(int fd, char **buffer)
{
	char	*line;

	if (fd < 0)
		return (0);
	*buffer = read_file(fd, *buffer);
	if (!*buffer)
		return (NULL);
	line = next_line(*buffer);
	*buffer = leftover(*buffer);
	return (line);
}

void	read_here_doc(t_data *data, char *delimiter)
{
	char	*buffer;
	char	*line;
	size_t	delimiter_len;

	delimiter_len = ft_strlen(delimiter);
	line = NULL;
	buffer = NULL;
	while (1)
	{
		line = b_get_next_line(STDIN_FILENO, &buffer);
		if (ft_strlen(line) == delimiter_len + 1
			&& ft_strncmp(line, delimiter, delimiter_len) == 0)
			break ;
		else
			write(data->infile, line, ft_strlen(line));
		free(line);
	}
	if (line != NULL)
		free(line);
	free(buffer);
	close(data->infile);
	data->infile = open("temp.txt", O_RDONLY);
}
