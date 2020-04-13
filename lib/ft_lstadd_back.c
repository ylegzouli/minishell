/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylegzoul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 11:34:33 by ylegzoul          #+#    #+#             */
/*   Updated: 2019/11/12 19:00:58 by ylegzoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void			ft_lstadd_back(t_list **alst, t_list *new)
{
	t_list		*li;

	li = *alst;
	if (*alst == NULL)
	{
		*alst = new;
		return ;
	}
	while (li->next != NULL)
		li = li->next;
	li->next = new;
}
