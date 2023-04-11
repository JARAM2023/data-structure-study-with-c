#include "libft.h"

void printList(t_list **lst) 
{
    t_list *lst_c;

    lst_c = *lst;
    while (lst_c != NULL) {
        printf("%d\n", lst_c->content);
        lst_c = lst_c -> next;
    }
}