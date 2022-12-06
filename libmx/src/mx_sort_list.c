#include "libmx.h"

t_list *mx_sort_list(t_list *lst, bool (*cmp)(void *a, void *b)) {
    
    t_list *head = lst;
    t_list *i_list = lst;
    t_list *j_list = lst;
    while (i_list != NULL)
    {
        j_list = head;
        while (j_list->next != NULL)
        {
            if (cmp(j_list->data, j_list->next->data)) {
                void *buff = j_list->data;
                j_list->data = j_list->next->data;
                j_list->next->data = buff;
            }
            j_list = j_list->next;
        }
        
        i_list = i_list->next;
    }
    
    return head;
}
