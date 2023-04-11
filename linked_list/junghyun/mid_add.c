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