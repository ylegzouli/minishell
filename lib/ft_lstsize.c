/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylegzoul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 11:58:27 by ylegzoul          #+#    #+#             */
/*   Updated: 2019/11/06 12:04:01 by ylegzoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int			ft_lstsize(t_list *lst)
{
	t_list	*li;
	int		size;

	li = lst;
	size = 0;
	if (li == NULL)
		return (0);
	while (li->next != NULL)
	{
		size++;
		li = li->next;
	}
	size++;
	return (size);
}
