/* in your iperf_api.c (or, better, in iperf_list.h) */

#ifndef IPERF3_LIST_H
#define IPERF3_LIST_H

/* Doubly-linked list head */
typedef struct list_head {
    struct list_head *next, *prev;
} list_head;

/* Initialize a standalone list head */
#define INIT_LIST_HEAD(ptr)                \
    do {                                   \
        (ptr)->next = (ptr);               \
        (ptr)->prev = (ptr);               \
    } while (0)

/* Internal: insert new between prev and next */
static inline void __list_add(struct list_head *new,
                              struct list_head *prev,
                              struct list_head *next)
{
    next->prev = new;
    new->next  = next;
    new->prev  = prev;
    prev->next = new;
}

/* Add new element at end of list headed by head */
static inline void list_add_tail(struct list_head *new,
                                 struct list_head *head)
{
    __list_add(new, head->prev, head);
}

/* Remove entry from its list */
static inline void list_del(struct list_head *entry)
{
    entry->next->prev = entry->prev;
    entry->prev->next = entry->next;
    /* optional: poison pointers */
    entry->next = entry->prev = NULL;
}

/* Iterate over the list */
#define list_for_each(pos, head)            \
    for (pos = (head)->next; pos != (head); \
         pos = pos->next)

#if 0
/* Convenience to get container struct from member pointer */
#define container_of(ptr, type, member) \
    ((type *)((char *)(ptr) - offsetof(type, member)))
#endif

#endif /* IPERF3_LIST_H */
