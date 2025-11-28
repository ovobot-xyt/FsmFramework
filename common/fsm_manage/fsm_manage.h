#ifndef _FSM_MANAGE_H_
#define _FSM_MANAGE_H_
#include "double_list.h"

#define cmdContainerOf(ptr, type, member) \
    ((type *)((char *)(ptr) - (unsigned long)(&((type *)0)->member)))

#define cmdEntry(ptr, type, member)       cmdContainerOf(ptr, type, member)
#define FSM_LIST(...)    FsmList_t* fsm_list[]={__VA_ARGS__, NULL}
typedef int (*fsm_fun)(void *arg);

typedef struct {
    volatile uint32_t event_code;
    volatile uint32_t status;
    volatile uint32_t delay;
    volatile uint32_t prv_state;
    volatile uint32_t next_state;
} FsmData_t;

typedef struct {
    double_list_t list;
    FsmData_t f_data;
} FsmList_t;

typedef struct {
    int event_code;
    fsm_fun callback_fun;
    double_list_t node;
} FsmCmdContainer_t;

enum FSM_STATUS {
    NONE_ERR,
    ERR = !NONE_ERR
};

extern FsmList_t *fsm_list[];
extern int fsmDelay(void *arg);
extern int fsmSysTick(void);
extern int fsmProcess(void);
extern void fsmCmdInsert(double_list_t *list, char event_code, fsm_fun callback);
#endif