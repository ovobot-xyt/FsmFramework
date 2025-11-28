#include "main.h"
#include "fsm_manage.h"

FSM_LIST(&fsm_a, &fsm_b, &fsm_c);
int main(void)
{
    systemInit();

    for (;;) {
        fsmProcess();
    }

    return 0;
}
