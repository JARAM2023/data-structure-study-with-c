/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junghych <junghych@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 19:52:34 by subinlee          #+#    #+#             */
/*   Updated: 2023/04/10 20:11:11 by junghych         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
// lst의 길이
int	ft_lstsize(t_list *lst)
{
	int	size;

	size = 0;
	// lst의 next를 타고가서 그때의 lst가 null일때까지 cnt
	while (lst)
	{
		lst = lst->next;
		size++;
	}
	return (size);
}
