/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: subinlee <subinlee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 19:53:00 by subinlee          #+#    #+#             */
/*   Updated: 2022/11/14 20:42:22 by subinlee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
// lst의 제일 끝부분(next가 null인 노드)
t_list	*ft_lstlast(t_list *lst)
{
	if (!lst)
		return (NULL);
	// next가 null이면 탈출
	while (lst->next)
		lst = lst->next;
	return (lst);
}
