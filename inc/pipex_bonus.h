/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwhitley <jwhitley@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 15:27:53 by jwhitley          #+#    #+#             */
/*   Updated: 2024/07/12 18:27:35 by jwhitley         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include "../libft/libft.h"
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <unistd.h>
# include <sys/wait.h>
# include <errno.h>
# include <string.h>
# include <stdarg.h>

typedef struct s_pipe
{
	int		infile;
	int		outfile;
	char	***cmds;
	char	**cmd_paths;
	char	**env;
	int		**p_fd;
	pid_t	*pid;
	int		cmd_count;
}	t_data;

/* parse_check_input_bonus.c */
void	b_populate_struct(int count, char **args, char **env, t_data *data);

/* utils_bonus.c */
char	**b_get_paths(char **env);
char	*b_get_next_line(int fd, char **buffer);
void	read_here_doc(t_data *data, char *delimiter);

/* free_bonus.c */
void	b_free_array(char **array);
void	b_free_data_struct(t_data *data);

/** execute_commands_bonus.c */
void	b_execute_commands(t_data *data);

#endif