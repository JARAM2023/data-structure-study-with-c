/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junghych <junghych@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 19:51:55 by subinlee          #+#    #+#             */
/*   Updated: 2023/04/10 20:07:24 by junghych         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
// lst리스트에 제일 앞에 new를 집어넣기
void	ft_lstadd_front(t_list **lst, t_list *new)
{
	if (!lst || !new)
		return ;
	// 집어넣을 new의 next pointer를 lst로 지정
	new->next = *lst;
	// lst의 시작지점을 new로 갱신
	*lst = new;
}
