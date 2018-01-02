#include <minix/syslib.h>
#include <minix/driver.h>
#include <machine/int86.h>
#include "mouse.h"
#include "MemGame.h"
#include "math.h"
#include "graphics.h"
#include "vbe.h"
#include "Bitmap.h"


#define HOOK_ID_MOUSE 2
int hookID = 2;

int mouse_subscribe_int()
{
	if ((sys_irqsetpolicy(MOUSE_IRQ, IRQ_REENABLE | IRQ_EXCLUSIVE, &hookID) == OK) && (sys_irqenable(&hookID) == OK))
		return BIT(HOOK_ID_MOUSE);
	return -1;
}


int mouse_unsubscribe_int()
{
	if ((sys_irqdisable(&hookID) == OK) && (sys_irqrmpolicy(&hookID) == OK))
		return 0;
	return 1;
}


int mouse_readByte(unsigned long *data)
{
	if(sys_inb(OUT_BUF, data) != OK)
		return 1;
	return 0;
}

void enable_mouse()
{
	 if (sys_outb(OUT_BUF, SET_SM) != OK) // set stream mode
		 printf("Error while setting stream mode...\n");

	 if (sys_outb(STAT_REG, WBTM) != OK) //write byte to mouse
		 printf("Error while writing byte to mouse...\n");

	 if (sys_outb(OUT_BUF, ENABLE_SM) != OK) // enable stream mode
		 printf("Error enabling stream mode...\n");
}

void disable_mouse()
{
	   if (sys_outb(STAT_REG, WBTM) != OK) // write byte to mouse
		   printf("Error while writing byte to mouse...");

	   if (sys_outb(OUT_BUF, DIS_SM) != OK)   //disable stream mode
		   printf("Unable to disable stream mode ...\n");
}

void mouse_aux(mouse_data * mouse)
{
	unsigned long packet[3];
	int r, ipc_status;
    int count = 0;
    message msg;
    unsigned long data;
    int exit = 0;
    int irq_set = mouse_subscribe_int();
    if (irq_set == -1)
    {
    	printf("Unable to subscribe the mouse...\n");
    	return;
    }
    if (sys_outb(OUT_BUF, SET_SM) != OK) // set stream mode
    	printf("Error while setting stream mode...\n");
    if (sys_outb(STAT_REG, WBTM) != OK) //write byte to mouse
    	printf("Error while writing byte to mouse...\n");
    if (sys_outb(OUT_BUF, ENABLE_SM) != OK) // enable stream mode
    	printf("Error enabling stream mode...\n");
    while (exit == 0)
    {
    	if ((r = driver_receive(ANY, &msg, &ipc_status)) != 0) {
    		printf("driver_receive failed with: %d", r);
    		continue;
    	}
    	if (is_ipc_notify(ipc_status)) {
    		switch (_ENDPOINT_P(msg.m_source)) {
    		case HARDWARE:
    			if (msg.NOTIFY_ARG & irq_set)
    			{
    				mouse_readByte(&data);
    				if (((BIT(3) & data) && (count == 0)) || (count > 0))
    				{
    					packet[count] = data;
    					count++;
    				}
    				if (count == 3) {
    					count = 0;
    					//mouse_get_packet(mouse);
    					aux(packet, count);
    				}
    			}
    		}
    	}
    }
    if (sys_outb(STAT_REG, WBTM) != OK) // write byte to mouse
    	printf("Error while writing byte to mouse...");
    if (sys_outb(OUT_BUF, DIS_SM) != OK)   //disable stream mode
    	printf("Unable to disable stream mode ...\n");
    printf("\n");
    int erro;
    erro = mouse_unsubscribe_int();
    if (erro == 1)
    {
    	return ;
    	printf("Error when unsubscribing ... \n");
    }
    mouse_readByte(&data);
    if (data != ACK)
    	printf("Acknowledgement failed ...\n");
}

void mouse_aux_menu(mouse_data * mouse)
{
	unsigned long packet[3];
	int r, ipc_status;
	int count = 0;
	message msg;
	unsigned long data;
	int exit = 0;
	int irq_set = mouse_subscribe_int();
	if (irq_set == -1)
	{
		printf("Unable to subscribe the mouse...\n");
		return;
	}
	if (sys_outb(OUT_BUF, SET_SM) != OK) // set stream mode
		printf("Error while setting stream mode...\n");
	if (sys_outb(STAT_REG, WBTM) != OK) //write byte to mouse
		printf("Error while writing byte to mouse...\n");
	if (sys_outb(OUT_BUF, ENABLE_SM) != OK) // enable stream mode
		printf("Error enabling stream mode...\n");
	while (exit == 0)
	{
		if ((r = driver_receive(ANY, &msg, &ipc_status)) != 0) {
			printf("driver_receive failed with: %d", r);
			continue;
		}
		if (is_ipc_notify(ipc_status)) {
			switch (_ENDPOINT_P(msg.m_source)) {
			case HARDWARE:
				if (msg.NOTIFY_ARG & irq_set)
				{
					mouse_readByte(&data);
					if (((BIT(3) & data) && (count == 0)) || (count > 0))
					{
						packet[count] = data;
						count++;
					}
					if (count == 3) {
						count = 0;
						//mouse_get_packet(mouse);
						aux_menu(packet);
					}
				}
			}
		}
	}
	if (sys_outb(STAT_REG, WBTM) != OK) // write byte to mouse
		printf("Error while writing byte to mouse...");
	if (sys_outb(OUT_BUF, DIS_SM) != OK)   //disable stream mode
		printf("Unable to disable stream mode ...\n");
	printf("\n");
	int erro;
	erro = mouse_unsubscribe_int();
	if (erro == 1)
	{
		return ;
		printf("Error when unsubscribing ... \n");
	}
	mouse_readByte(&data);
	if (data != ACK)
		printf("Acknowledgement failed ...\n");
}


void aux(unsigned long packet[3], int c)
{
	mouse_data data = mouse_get_packet(packet);
	pos.x += data.xx;
	pos.y -= data.yy;
	pos.lb = data.leftButtonDown;
	out_of_bonds();
}

void aux_menu(unsigned long packet[3])
{
	mouse_data data = mouse_get_packet(packet);
	pos.x += data.xx;
	pos.y -= data.yy;
	pos.lb = data.leftButtonDown;
	out_of_bonds();
	drawMenu();
	drawRato(pos.x,pos.y);
}

void aux_levels(unsigned long packet[3])
{
	mouse_data data = mouse_get_packet(packet);
	pos.x += data.xx;
	pos.y -= data.yy;
	pos.lb = data.leftButtonDown;
	out_of_bonds();
	drawLevels();
	drawRato(pos.x,pos.y);
}

void aux_scores(unsigned long packet[3])
{
	mouse_data data = mouse_get_packet(packet);
	pos.x += data.xx;
	pos.y -= data.yy;
	pos.lb = data.leftButtonDown;
	out_of_bonds();
	drawHighscores();
	read_scores();
	read_scores2();
	read_scores3();
	drawRato(pos.x,pos.y);
}

mouse_data mouse_get_packet(unsigned long packet[3])
{

	mouse_data data;

	float xx;
	float yy;

	data.pack[0] = packet [0];
	data.pack[1] = packet [1];
	data.pack[2] = packet [2];

	if (BIT(4) & data.pack[0]) // sinal do x
	{
		signed char xxx;
		xxx = data.pack[1];
		xx = xx + xxx;
	}
	else
		xx+=data.pack[1];
	if (BIT(5) & data.pack[0]) // sinal do y
	{
		signed char yyy;
		yyy = data.pack[2];
		yy = yy + yyy;
		}
	else
		yy+=data.pack[2];


	data.leftButtonDown = (BIT(0) & packet[0]);
	data.middleButtonDown = (BIT(2) & packet[0]);
	data.rightButtonDown = BIT(1) & packet[0];
	data.xx = xx;
	data.yy = yy;
	return data;

}

