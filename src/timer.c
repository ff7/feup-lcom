#include <minix/syslib.h>
#include <minix/drivers.h>
#include <minix/driver.h>
#include "timer.h"

static int hook_id=6;
static unsigned long count=0;

int timer_subscribe_int(void ) {
        int hook_t = hook_id;
        if(sys_irqsetpolicy(0, IRQ_REENABLE, &hook_id) == OK || sys_irqenable(&hook_id) == OK)
                return BIT(hook_t);
        return -1;
}

int timer_unsubscribe_int() {
        if((sys_irqdisable(&hook_id) == OK)|| (sys_irqrmpolicy(&hook_id) == OK))
                return 0;
        return 1;
}

void timer_int_handler() {
        count++;
}

int timer_exit(unsigned long delay) {
         int ipc_status;
         unsigned long irq_set = timer_subscribe_int();
         message msg;
         while(count < delay*60 ) {
                 int r =driver_receive(ANY, &msg, &ipc_status);
                 if ( r != 0 ) {
                    printf("driver_receive failed with: %d", r);
                    continue;
                 }
                 if (is_ipc_notify(ipc_status)) { /* received notification */
                         switch (_ENDPOINT_P(msg.m_source)) {
                         case HARDWARE: /* hardware interrupt notification */
                                 if (msg.NOTIFY_ARG & irq_set) { /* subscribed interrupt */
                                         timer_int_handler();
                                 }
                                 break;
                         default:
                                 break; /* no other notifications expected: do nothing */
                 }
                 } else { /* received a standard message, not a notification */
                         //no standard messages expected to do nothing
                 }
         }
         timer_unsubscribe_int();
         return 0;
}

