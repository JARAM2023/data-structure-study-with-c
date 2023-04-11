#include "libft.h"

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	if (!lst || !new)
		return ;
	new->next = *lst;
	*lst = new;
}

t_list	*ft_lstnew(int content)
{
	t_list	*new;

	new = (t_list *)malloc(sizeof(t_list));
	if (!new)
		return (NULL);
	new->content = content;
	new->next = NULL;
	return (new);
}

void printList(t_list **lst) 
{
    t_list *lst_c;

    lst_c = *lst;
    while (lst_c != NULL) {
        printf("%d\n", lst_c->content);
        lst_c = lst_c -> next;
    }
}

// content 찾아서 삭제
t_list* find_delete(t_list **lst, int content) {

    t_list *lst_c;

    lst_c = *lst;

    t_list* pre = NULL;

    if (lst == NULL) {
        return NULL;
    }
    // 찾아서
    while (lst_c->content != content) {

        if (lst_c->next == NULL) {
            return NULL;
        }
        else {
            // 이전 포인터와 찾은 포인터 지정
            pre = lst_c;
            lst_c = lst_c->next;
        }
    }
    // 이전포인터->next를 현재포인터대신 다음포인터로 설정(현재포인터 linked list에서 삭제)
    pre->next = lst_c->next;
    return lst_c;
}
t_list* mid_add(t_list *lst, int content) {
    t_list *lst_next;
    t_list *new_lst;

    // lst다음노드 저장 후
    lst_next = lst->next;
    new_lst = ft_lstnew(content);
    // lst는 새 노드 가르킴
    lst->next = new_lst;
    // 새노드는 저장해둔 다음노드 가르킴
    new_lst->next = lst_next;
    return lst;
}

int main()
{
	t_list **lst;

	lst = (t_list **)malloc(sizeof(t_list *));
	*lst = NULL;
	
	ft_lstadd_front(lst, ft_lstnew(1));
	ft_lstadd_front(lst, ft_lstnew(2));
	ft_lstadd_front(lst, ft_lstnew(3));
    //2가진 노드 삭제
    find_delete(lst, 2);
    // 3 1상태에서 3뒤에 4추가
    find_add(*lst, 4);
	printList(lst);
	
	free(*lst);
	free(lst);
	
	return (0);
}
