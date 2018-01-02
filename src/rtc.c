#include "rtc.h"

#define BIT(n) (0x01<<(n))

int hook_id_rtc = 14;

int rtc_subscribe_int()
{
	int hook_temp = hook_id_rtc;
	if((sys_irqsetpolicy(8, IRQ_REENABLE|IRQ_EXCLUSIVE,&hook_temp)!=OK)|| (sys_irqenable(&hook_temp)!=OK))
		return -1;
	return BIT(hook_id_rtc);
}

int rtc_unsubscribe_int()
{
	int hook_temp;
	if((sys_irqrmpolicy(&hook_temp)!=OK) || (sys_irqenable(&hook_temp)!=OK))
		return 1;
	return 0;
}

int day()
{
	unsigned long i;
	sys_outb(0x70, 0x07);
	sys_inb(0x71, &i);
	return i;
}

int month()
{
	unsigned long i;
	sys_outb(0x70, 0x08);
	sys_inb(0x71, &i);
	return i;
}

int year()
{
	unsigned long i;
	sys_outb(0x70, 0x09);
	sys_inb(0x71, &i);
	return i;
}
