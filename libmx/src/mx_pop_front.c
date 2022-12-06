#include "libmx.h"

void mx_pop_front(t_list **head) {

    if (head == NULL)
        return;

    t_list *_head = *head;

    if (_head == NULL)
        return;

    *head = _head->next;
    free(_head);
}
