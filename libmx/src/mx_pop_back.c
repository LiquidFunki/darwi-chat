#include "libmx.h"

void mx_pop_back(t_list **head) {
    
    t_list *_head = *head;
    t_list *current = _head;
    t_list *last = NULL;

    if (_head ==  NULL) return;
    
    while (current->next != NULL)
    {
        last = current;
        current = current->next;
    }

    if (current == _head) {
        _head = NULL;
    }

    if (last != NULL) {
        last->next = NULL;
    }

    *head = _head;
    free(current);
}
