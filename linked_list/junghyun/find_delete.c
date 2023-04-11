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