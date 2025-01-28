/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwhitley <jwhitley@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 14:05:52 by jwhitley          #+#    #+#             */
/*   Updated: 2024/06/10 12:12:15 by jwhitley         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft.h"

void	ft_lstadd_back(t_list **list, t_list *new)
{
	t_list	*temp;

	if (*list == NULL)
		*list = new;
	else
	{
		temp = ft_lstlast(*list);
		temp->next = &*new;
	}
}
