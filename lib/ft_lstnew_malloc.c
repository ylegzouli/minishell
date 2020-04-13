/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylegzoul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 11:17:09 by ylegzoul          #+#    #+#             */
/*   Updated: 2019/11/13 13:05:32 by ylegzoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew_malloc(void const *content, int content_size)
{
	t_list *newcontent;

	if (!(newcontent = (malloc(sizeof(t_list)))))
		return (NULL);
	if (!content)
		newcontent->content = NULL;
	else
	{
		if (!(newcontent->content = (malloc(content_size))))
			return (NULL);
		ft_memcpy(newcontent->content, content, content_size);
	}
	newcontent->next = NULL;
	return (newcontent);
}
