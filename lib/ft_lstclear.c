/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoudouy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 08:06:48 by acoudouy          #+#    #+#             */
/*   Updated: 2019/11/06 15:56:03 by acoudouy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list		*temp;
	t_list		*temp2;

	temp2 = *lst;
	temp = NULL;
	if (lst == NULL || *lst == NULL)
		return ;
	while (temp2)
	{
		if (temp2->next)
			temp = temp2->next;
		else
			temp = NULL;
		(*del)(temp2->content);
		free(temp2);
		temp2 = temp;
	}
	*lst = NULL;
}
