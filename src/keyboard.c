#include <minix/sysutil.h>
#include <minix/syslib.h>
#include <minix/drivers.h>
#include <minix/driver.h>
#include "keyboard.h"
#define OUT_BUF 0x60
#define BIT(n) (0x01<<(n))

int hook_id_kb = 1;



int kb_subscribe_int()
{
	int hook_temp = hook_id_kb;

	if((sys_irqsetpolicy(0x01, IRQ_REENABLE | IRQ_EXCLUSIVE, &hook_id_kb) != OK) || (sys_irqenable(&hook_id_kb) != OK))
		return -1;
	return BIT(hook_temp);
}

int kb_unsubscribe_int()
{
	int hook_temp_2 = hook_id_kb;

	if ((OK == sys_irqdisable(&hook_temp_2)) || (OK == sys_irqrmpolicy(&hook_temp_2)))
				return 1;
	return 0;
}


int c_scan(unsigned char st)  // retorna 0 caso tenha 2 bytes e 1 caso so tenha 1
{
	if ((0xE0 & st) == 0xE0)
		return 0;
	else
		return 1;
}

int keyboard_exit()
{
	int r;
	int ipc_status;
	message msg;
	unsigned long conf;
	unsigned short assembly = 0;
	unsigned long irq_set = kb_subscribe_int();
	if (irq_set == -1)
	{
		printf("Error when subscribing the keyboard :(\n\n");
		return 1;
	}
	while(conf != 0x81) {
		if ( (r = driver_receive(ANY, &msg, &ipc_status)) != 0 ) {
			printf("driver_receive failed with: %d", r);
			continue;
		}
		if (is_ipc_notify(ipc_status)) {
			switch (_ENDPOINT_P(msg.m_source)) {
			case HARDWARE:
				if (msg.NOTIFY_ARG & irq_set)
				{
					if (assembly == 0) // em c
					{
						sys_inb(OUT_BUF, &conf);
					}
				}
				break;
			default:
				break;
			}
		}
	}
	if(kb_unsubscribe_int()==1){
		return 1; //erro
	}
	return 0;
}

