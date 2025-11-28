#ifndef __double_list_h__
#define __double_list_h__

typedef struct double_list_node {
    struct double_list_node *next;
    struct double_list_node *prev;
};

typedef struct double_list_node  double_list_t;

extern void doubleListInit(double_list_t *l);
extern void doubleListInsertAfter(double_list_t *l, double_list_t *n);
extern void doubleListInsertBefore(double_list_t *l, double_list_t *n);
extern void doubleListRemove(double_list_t *n);

#endif
