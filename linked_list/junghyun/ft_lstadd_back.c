/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junghych <junghych@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 19:53:23 by subinlee          #+#    #+#             */
/*   Updated: 2023/04/10 20:07:52 by junghych         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
// lst제일 뒤에 new 추가
void	ft_lstadd_back(t_list **lst, t_list *new)
{
	// 꼬리의 위치 포인터
	t_list	*tail;

	if (!lst || !new)
		return ;
	// 만약 lst의 첫자리가 비어있다면 new는 lst의 머리에 넣기
	if (!(*lst))
	{
		*lst = new;
		return ;
	}
	// 꼬리는 lst의 제일 끝부분 포인터로 설정
	tail = ft_lstlast(*lst);
	// lst의 끝부분 다음에 new를 삽입
	tail->next = new;
}
