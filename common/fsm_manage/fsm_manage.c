#include "fsm_manage.h"
#include <stdlib.h>

int fsmDelay(void *arg)
{
    FsmData_t *f_data = (FsmData_t *)arg;

    if (f_data->delay == 0) {
        f_data->event_code = f_data->next_state;
    }

    return 0;
}

int fsmSysTick(void)
{
    volatile uint32_t loop = 0;

    for (loop = 0; fsm_list[loop] != NULL ; loop++) {
        if (fsm_list[loop]->f_data.delay > 0) {
            fsm_list[loop]->f_data.delay--;
        }
    }

    return 0;
}

void fsmCmdInsert(double_list_t *list, char event_code, fsm_fun callback)
{
    FsmCmdContainer_t *_node_ptr = (FsmCmdContainer_t *)malloc(sizeof(FsmCmdContainer_t));
    _node_ptr->event_code = event_code;
    _node_ptr->callback_fun = callback;
    doubleListInsertBefore(list, &_node_ptr->node);
}

FsmCmdContainer_t *fsmCallbackFind(FsmList_t *f_list)
{
    struct double_list_node *list_ptr;
    FsmCmdContainer_t *fsm_node_ptr;

    for (list_ptr = f_list->list.next; list_ptr != &f_list->list; list_ptr = list_ptr->next) {
        fsm_node_ptr = cmdEntry(list_ptr, FsmCmdContainer_t, node);

        if (fsm_node_ptr->event_code == f_list->f_data.event_code) {
            return fsm_node_ptr;
        }
    }

    return 0;
}

int fsmProcess(void)
{
    FsmCmdContainer_t *_fsm_ptr;
    volatile uint32_t loop = 0;
    int ret;

    for (loop = 0; fsm_list[loop] != NULL ; loop++) {
        _fsm_ptr = fsmCallbackFind(fsm_list[loop]);

        if (_fsm_ptr != 0) {
            ret = _fsm_ptr->callback_fun(&fsm_list[loop]->f_data);
        } else {
            ret = -1;
        }
    }

    return ret;
}