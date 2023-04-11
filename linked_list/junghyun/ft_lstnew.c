/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junghych <junghych@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 19:51:30 by subinlee          #+#    #+#             */
/*   Updated: 2023/04/10 20:18:20 by junghych         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// 생성 content를 가지는 리스트 생성

t_list	*ft_lstnew(int content)
{
	t_list	*new;

	new = (t_list *)malloc(sizeof(t_list));
	if (!new)
		return (NULL);
	// content를 담고
	new->content = content;
	// next 포인터를 담는다. 새로운 리스트라 NULL
	new->next = NULL;
	return (new);
}