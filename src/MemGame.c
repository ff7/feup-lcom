#include <stdio.h>
#include <minix/driver.h>
#include "keyboard.h"
#include "timer.h"
#include "graphics.h"
#include "mouse.h"
#include "Bitmap.h"
#include "MemGame.h"
#include "vbe.h"
#include "rtc.h"

int gameplay1(mouse_data * mouse, unsigned long irq_set_timer, unsigned long irq_set, unsigned long irq_set_kb, unsigned long irq_set_rtc)
{
	drawBlack();
	drawMemorize();
	drawBack();

	sleep(1);
	drawMonstro3();
	sleep(2);
	drawCapa3();
	sleep(1);
	drawMonstro5();
	sleep(2);
	drawCapa5();
	sleep(1);
	drawMonstro8();
	sleep(2);
	drawCapa8();
	sleep(1);


	int contagem = 0; // contagem de cartas corretas
	int cont_lb = 0; // contagem de clicks com o botao esquerdo do rato nas cartas

	int c = 0; //contagem do timer

	unsigned long packet[3];
	int r, ipc_status;
	int count = 0; // contagem dos packets
	message msg;
	unsigned long data;
	pos.x = 490;
	pos.y = 480;

	unsigned long conf;

	while ((contagem != 3) && (c < 20*60))
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
						aux(packet,c);
					}


					if (cont_lb == 0)
						if (pos.x > 500 && pos.x < 680 && pos.y > 200 && pos.y < 456  && pos.lb != 0)
						{
							contagem++;
							cont_lb++;
						}
						else if ((pos.x > 100 && pos.x < 280 && pos.y > 200 && pos.y < 456 && pos.lb != 0) || (pos.x > 300 && pos.x < 480 && pos.y > 200 && pos.y < 456 && pos.lb != 0) || (pos.x > 700 && pos.x < 880 && pos.y > 200 && pos.y < 456 && pos.lb != 0) || (pos.x > 100 && pos.x < 280 && pos.y > 500 && pos.y < 756 && pos.lb != 0) || (pos.x > 300 && pos.x < 480 && pos.y > 500 && pos.y < 756 && pos.lb != 0) || (pos.x > 500 && pos.x < 680 && pos.y > 500 && pos.y < 756 && pos.lb != 0) || (pos.x > 700 && pos.x < 880 && pos.y > 500 && pos.y < 756 && pos.lb != 0))
						{
							drawYouLose();
							sleep(2);
							contagem = 3;
							loop_main_menu(mouse, irq_set_timer,irq_set,irq_set_kb,irq_set_rtc);
						}
					if (cont_lb == 1)
						if (pos.x > 100 && pos.x < 280 && pos.y > 500 && pos.y < 756 && pos.lb != 0)
						{
							contagem++;
							cont_lb++;
						}
						else if ((pos.x > 100 && pos.x < 280 && pos.y > 200 && pos.y < 456 && pos.lb != 0) || (pos.x > 300 && pos.x < 480 && pos.y > 200 && pos.y < 456 && pos.lb != 0) ||/* (pos.x > 500 && pos.x < 680 && pos.y > 200 && pos.y < 456 && pos.lb != 0) ||*/ (pos.x > 700 && pos.x < 880 && pos.y > 200 && pos.y < 456 && pos.lb != 0) || (pos.x > 300 && pos.x < 480 && pos.y > 500 && pos.y < 756 && pos.lb != 0) || (pos.x > 500 && pos.x < 680 && pos.y > 500 && pos.y < 756 && pos.lb != 0) || (pos.x > 700 && pos.x < 880 && pos.y > 500 && pos.y < 756 && pos.lb != 0))
						{
							drawYouLose();
							sleep(2);
							contagem = 3;
							loop_main_menu(mouse, irq_set_timer,irq_set,irq_set_kb,irq_set_rtc);
						}
					if (cont_lb == 2)
						if (pos.x > 700 && pos.x < 880 && pos.y > 500 && pos.y < 756 && pos.lb != 0)
						{
							drawYouWin();
							sleep(2);
							contagem++;
							cont_lb++;
							loop_main_menu(mouse, irq_set_timer,irq_set,irq_set_kb, irq_set_rtc);
						}
						else if ((pos.x > 100 && pos.x < 280 && pos.y > 200 && pos.y < 456 && pos.lb != 0) || (pos.x > 300 && pos.x < 480 && pos.y > 200 && pos.y < 456 && pos.lb != 0) || (pos.x > 500 && pos.x < 680 && pos.y > 200 && pos.y < 456 && pos.lb != 0) || (pos.x > 700 && pos.x < 880 && pos.y > 200 && pos.y < 456 && pos.lb != 0) || (pos.x > 300 && pos.x < 480 && pos.y > 500 && pos.y < 756 && pos.lb != 0) || (pos.x > 500 && pos.x < 680 && pos.y > 500 && pos.y < 756 && pos.lb != 0) || (pos.x > 100 && pos.x < 280 && pos.y > 200 && pos.y < 456 && pos.lb != 0))
						{
							drawYouLose();
							sleep(2);
							contagem = 3;
							loop_main_menu(mouse, irq_set_timer,irq_set,irq_set_kb, irq_set_rtc);
						}


				}
				if (msg.NOTIFY_ARG & irq_set_timer)
				{
					c++;
					drawBlack();
					drawCards();
					drawReproduce();
					displayTimer(c);
					drawRato(pos.x,pos.y);
				}
				if (msg.NOTIFY_ARG & irq_set_kb)
				{
					sys_inb(OUT_BUF, &conf);
				}
				if (msg.NOTIFY_ARG & irq_set_rtc)
				{
					day();
					month();
					year();
				}


			}
		}
	}

	if (c == 20*60)
	{
		drawYouLose();
		sleep(2);
		loop_main_menu(mouse, irq_set_timer,irq_set,irq_set_kb, irq_set_rtc);
	}

	return 0;
}


int gameplay2(mouse_data * mouse, unsigned long irq_set_timer, unsigned long irq_set, unsigned long irq_set_kb, unsigned long irq_set_rtc)
{
	drawBlack();
	drawMemorize();
	drawBack();

	sleep(1);
	drawMonstro6();
	sleep(1);
	drawCapa6();
	sleep(1);
	drawMonstro4();
	sleep(1);
	drawCapa4();
	sleep(1);
	drawMonstro2();
	sleep(1);
	drawCapa2();
	sleep(1);
	drawMonstro7();
	sleep(1);
	drawCapa7();
	sleep(1);
	drawMonstro1();
	sleep(1);
	drawCapa1();
	sleep(1);

	unsigned long conf;

	int contagem = 0; // contagem de cartas corretas
	int cont_lb = 0; // contagem de clicks com o botao esquerdo do rato nas cartas

	int c = 0; //contagem do timer

	unsigned long packet[3];
	int r, ipc_status;
	int count = 0; // contagem dos packets
	message msg;
	unsigned long data;

	pos.x = 490;
	pos.y = 480;

	while ((contagem != 5) && (c < 20*60))
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
						aux(packet,c);
					}

					if (cont_lb == 0)
						if (pos.x > 300 && pos.x < 480 && pos.y > 500 && pos.y < 756  && pos.lb != 0)
						{
							contagem++;
							cont_lb++;
						}
						else if ((pos.x > 100 && pos.x < 280 && pos.y > 200 && pos.y < 456 && pos.lb != 0) || (pos.x > 300 && pos.x < 480 && pos.y > 200 && pos.y < 456 && pos.lb != 0) ||(pos.x > 700 && pos.x < 880 && pos.y > 200 && pos.y < 456 && pos.lb != 0) || (pos.x > 100 && pos.x < 280 && pos.y > 500 && pos.y < 756 && pos.lb != 0) || (pos.x > 500 && pos.x < 680 && pos.y > 200 && pos.y < 456 && pos.lb != 0) || (pos.x > 500 && pos.x < 680 && pos.y > 500 && pos.y < 756 && pos.lb != 0) || (pos.x > 700 && pos.x < 880 && pos.y > 500 && pos.y < 756 && pos.lb != 0) /*||(pos.x > 300 && pos.x < 480 && pos.y > 500 && pos.y < 756  && pos.lb != 0)*/ )
						{
							drawYouLose();
							sleep(2);
							contagem = 5;
							loop_main_menu(mouse, irq_set_timer,irq_set, irq_set_kb,irq_set_rtc);
						}
					if (cont_lb == 1)
						if (pos.x > 700 && pos.x < 880 && pos.y > 200 && pos.y < 456 && pos.lb != 0)
						{
							contagem++;
							cont_lb++;
						}
						else if ((pos.x > 100 && pos.x < 280 && pos.y > 200 && pos.y < 456 && pos.lb != 0) || (pos.x > 300 && pos.x < 480 && pos.y > 200 && pos.y < 456 && pos.lb != 0) /*||(pos.x > 700 && pos.x < 880 && pos.y > 200 && pos.y < 456 && pos.lb != 0)*/ || (pos.x > 100 && pos.x < 280 && pos.y > 500 && pos.y < 756 && pos.lb != 0) || (pos.x > 500 && pos.x < 680 && pos.y > 200 && pos.y < 456 && pos.lb != 0) || (pos.x > 500 && pos.x < 680 && pos.y > 500 && pos.y < 756 && pos.lb != 0) || (pos.x > 700 && pos.x < 880 && pos.y > 500 && pos.y < 756 && pos.lb != 0) /*||(pos.x > 300 && pos.x < 480 && pos.y > 500 && pos.y < 756  && pos.lb != 0)*/ )
						{
							drawYouLose();
							sleep(2);
							contagem = 5;
							loop_main_menu(mouse, irq_set_timer,irq_set, irq_set_kb,irq_set_rtc);
						}
					if (cont_lb == 2)
						if (pos.x > 300 && pos.x < 480 && pos.y > 200 && pos.y < 456 && pos.lb != 0)
						{
							contagem++;
							cont_lb++;
						}
						else if ((pos.x > 100 && pos.x < 280 && pos.y > 200 && pos.y < 456 && pos.lb != 0)/* || (pos.x > 300 && pos.x < 480 && pos.y > 200 && pos.y < 456 && pos.lb != 0) ||(pos.x > 700 && pos.x < 880 && pos.y > 200 && pos.y < 456 && pos.lb != 0)*/ || (pos.x > 100 && pos.x < 280 && pos.y > 500 && pos.y < 756 && pos.lb != 0) || (pos.x > 500 && pos.x < 680 && pos.y > 200 && pos.y < 456 && pos.lb != 0) || (pos.x > 500 && pos.x < 680 && pos.y > 500 && pos.y < 756 && pos.lb != 0) || (pos.x > 700 && pos.x < 880 && pos.y > 500 && pos.y < 756 && pos.lb != 0) ||(pos.x > 300 && pos.x < 480 && pos.y > 500 && pos.y < 756  && pos.lb != 0) )
						{
							drawYouLose();
							sleep(2);
							contagem = 5;
							loop_main_menu(mouse, irq_set_timer,irq_set, irq_set_kb,irq_set_rtc);
						}
					if (cont_lb == 3)
						if (pos.x > 500 && pos.x < 680 && pos.y > 500 && pos.y < 756 && pos.lb != 0)
						{
							contagem++;
							cont_lb++;
						}
						else if ((pos.x > 100 && pos.x < 280 && pos.y > 200 && pos.y < 456 && pos.lb != 0)/* || (pos.x > 300 && pos.x < 480 && pos.y > 200 && pos.y < 456 && pos.lb != 0)*/ ||(pos.x > 700 && pos.x < 880 && pos.y > 200 && pos.y < 456 && pos.lb != 0) || (pos.x > 100 && pos.x < 280 && pos.y > 500 && pos.y < 756 && pos.lb != 0) || (pos.x > 500 && pos.x < 680 && pos.y > 200 && pos.y < 456 && pos.lb != 0) /*|| (pos.x > 500 && pos.x < 680 && pos.y > 500 && pos.y < 756 && pos.lb != 0) */|| (pos.x > 700 && pos.x < 880 && pos.y > 500 && pos.y < 756 && pos.lb != 0) ||(pos.x > 300 && pos.x < 480 && pos.y > 500 && pos.y < 756  && pos.lb != 0) )
						{
							drawYouLose();
							sleep(2);
							contagem = 5;
							loop_main_menu(mouse, irq_set_timer,irq_set, irq_set_kb,irq_set_rtc);
						}
					if (cont_lb == 4)
						if (pos.x > 100 && pos.x < 280 && pos.y > 200 && pos.y < 456 && pos.lb != 0)
						{
							drawYouWin();
							sleep(2);
							contagem++;
							cont_lb++;
							loop_main_menu(mouse, irq_set_timer,irq_set, irq_set_kb,irq_set_rtc);
						}
						else if (/*(pos.x > 100 && pos.x < 280 && pos.y > 200 && pos.y < 456 && pos.lb != 0)*/(pos.x > 300 && pos.x < 480 && pos.y > 200 && pos.y < 456 && pos.lb != 0) ||(pos.x > 700 && pos.x < 880 && pos.y > 200 && pos.y < 456 && pos.lb != 0) || (pos.x > 100 && pos.x < 280 && pos.y > 500 && pos.y < 756 && pos.lb != 0) || (pos.x > 500 && pos.x < 680 && pos.y > 200 && pos.y < 456 && pos.lb != 0) /*|| (pos.x > 500 && pos.x < 680 && pos.y > 500 && pos.y < 756 && pos.lb != 0) */|| (pos.x > 700 && pos.x < 880 && pos.y > 500 && pos.y < 756 && pos.lb != 0) ||(pos.x > 300 && pos.x < 480 && pos.y > 500 && pos.y < 756  && pos.lb != 0) )
						{
							drawYouLose();
							sleep(2);
							contagem = 5;
							loop_main_menu(mouse, irq_set_timer,irq_set, irq_set_kb,irq_set_rtc);
						}

				}
				if (msg.NOTIFY_ARG & irq_set_timer)
				{
					c++;
					drawBlack();
					drawCards();
					drawReproduce();
					displayTimer(c);
					drawRato(pos.x,pos.y);
				}

				if (msg.NOTIFY_ARG & irq_set_kb)
				{
					sys_inb(OUT_BUF, &conf);
				}
				if (msg.NOTIFY_ARG & irq_set_rtc)
				{
					day();
					month();
					year();
				}

			}
		}
	}
	if (c == 20*60)
	{
		drawYouLose();
		sleep(2);
		loop_main_menu(mouse, irq_set_timer,irq_set,irq_set_kb, irq_set_rtc);
	}

	return 0;
}


int gameplay3(mouse_data * mouse, unsigned long irq_set_timer, unsigned long irq_set, unsigned long irq_set_kb, unsigned long irq_set_rtc)
{
	drawBlack();
	drawMemorize();
	drawBack();

	sleep(1);
	drawMonstro5();
	sleep(1);
	drawCapa5();
	sleep(1);
	drawMonstro2();
	sleep(1);
	drawCapa2();
	sleep(1);
	drawMonstro8();
	sleep(1);
	drawCapa8();
	sleep(1);
	drawMonstro7();
	sleep(1);
	drawCapa7();
	sleep(1);
	drawMonstro3();
	sleep(1);
	drawCapa3();
	sleep(1);
	drawMonstro6();
	sleep(1);
	drawCapa6();
	sleep(1);
	drawMonstro1();
	sleep(1);
	drawCapa1();
	sleep(1);
	drawMonstro4();
	sleep(1);
	drawCapa4();
	sleep(1);

	unsigned long conf;

	pos.x = 490;
	pos.y = 480;

	int contagem = 0; // contagem de cartas corretas
	int cont_lb = 0; // contagem de clicks com o botao esquerdo do rato nas cartas

	int c = 0; //contagem do timer

	unsigned long packet[3];
	int r, ipc_status;
	int count = 0; // contagem dos packets
	message msg;
	unsigned long data;

	while ((contagem != 8) && (c < 20*60))
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
						aux(packet,c);
					}


					if (cont_lb == 0)
						if (pos.x > 100 && pos.x < 280 && pos.y > 500 && pos.y < 756  && pos.lb != 0)
						{
							contagem++;
							cont_lb++;
						}
						else if ((pos.x > 100 && pos.x < 280 && pos.y > 200 && pos.y < 456 && pos.lb != 0) || (pos.x > 300 && pos.x < 480 && pos.y > 200 && pos.y < 456 && pos.lb != 0) ||(pos.x > 700 && pos.x < 880 && pos.y > 200 && pos.y < 456 && pos.lb != 0)/* || (pos.x > 100 && pos.x < 280 && pos.y > 500 && pos.y < 756 && pos.lb != 0)*/ || (pos.x > 500 && pos.x < 680 && pos.y > 200 && pos.y < 456 && pos.lb != 0) || (pos.x > 500 && pos.x < 680 && pos.y > 500 && pos.y < 756 && pos.lb != 0) || (pos.x > 700 && pos.x < 880 && pos.y > 500 && pos.y < 756 && pos.lb != 0) ||(pos.x > 300 && pos.x < 480 && pos.y > 500 && pos.y < 756  && pos.lb != 0))
						{
							drawYouLose();
							sleep(2);
							contagem = 8;
							loop_main_menu(mouse, irq_set_timer,irq_set, irq_set_kb,irq_set_rtc);
						}
					if (cont_lb == 1)
						if (pos.x > 300 && pos.x < 480 && pos.y > 200 && pos.y < 456 && pos.lb != 0)
						{
							contagem++;
							cont_lb++;
						}
						else if ((pos.x > 100 && pos.x < 280 && pos.y > 200 && pos.y < 456 && pos.lb != 0) /*|| (pos.x > 300 && pos.x < 480 && pos.y > 200 && pos.y < 456 && pos.lb != 0) */||(pos.x > 700 && pos.x < 880 && pos.y > 200 && pos.y < 456 && pos.lb != 0)/* || (pos.x > 100 && pos.x < 280 && pos.y > 500 && pos.y < 756 && pos.lb != 0) */|| (pos.x > 500 && pos.x < 680 && pos.y > 200 && pos.y < 456 && pos.lb != 0) || (pos.x > 500 && pos.x < 680 && pos.y > 500 && pos.y < 756 && pos.lb != 0) || (pos.x > 700 && pos.x < 880 && pos.y > 500 && pos.y < 756 && pos.lb != 0) ||(pos.x > 300 && pos.x < 480 && pos.y > 500 && pos.y < 756  && pos.lb != 0))
						{
							drawYouLose();
							sleep(2);
							contagem = 8;
							loop_main_menu(mouse, irq_set_timer,irq_set, irq_set_kb,irq_set_rtc);
						}
					if (cont_lb == 2)
						if (pos.x > 700 && pos.x < 880 && pos.y > 500 && pos.y < 756 && pos.lb != 0)
						{
							contagem++;
							cont_lb++;
						}
						else if ((pos.x > 100 && pos.x < 280 && pos.y > 200 && pos.y < 456 && pos.lb != 0)/* || (pos.x > 300 && pos.x < 480 && pos.y > 200 && pos.y < 456 && pos.lb != 0)*/ ||(pos.x > 700 && pos.x < 880 && pos.y > 200 && pos.y < 456 && pos.lb != 0) || (pos.x > 100 && pos.x < 280 && pos.y > 500 && pos.y < 756 && pos.lb != 0) || (pos.x > 500 && pos.x < 680 && pos.y > 200 && pos.y < 456 && pos.lb != 0) || (pos.x > 500 && pos.x < 680 && pos.y > 500 && pos.y < 756 && pos.lb != 0) /*|| (pos.x > 700 && pos.x < 880 && pos.y > 500 && pos.y < 756 && pos.lb != 0)*/ ||(pos.x > 300 && pos.x < 480 && pos.y > 500 && pos.y < 756  && pos.lb != 0) )
						{
							drawYouLose();
							sleep(2);
							contagem = 8;
							loop_main_menu(mouse, irq_set_timer,irq_set, irq_set_kb,irq_set_rtc);
						}
					if (cont_lb == 3)
						if (pos.x > 500 && pos.x < 680 && pos.y > 500 && pos.y < 756 && pos.lb != 0)
						{
							contagem++;
							cont_lb++;
						}
						else if ((pos.x > 100 && pos.x < 280 && pos.y > 200 && pos.y < 456 && pos.lb != 0) || (pos.x > 300 && pos.x < 480 && pos.y > 200 && pos.y < 456 && pos.lb != 0) ||(pos.x > 700 && pos.x < 880 && pos.y > 200 && pos.y < 456 && pos.lb != 0) || (pos.x > 100 && pos.x < 280 && pos.y > 500 && pos.y < 756 && pos.lb != 0) || (pos.x > 500 && pos.x < 680 && pos.y > 200 && pos.y < 456 && pos.lb != 0) /*|| (pos.x > 500 && pos.x < 680 && pos.y > 500 && pos.y < 756 && pos.lb != 0) || (pos.x > 700 && pos.x < 880 && pos.y > 500 && pos.y < 756 && pos.lb != 0)*/ ||(pos.x > 300 && pos.x < 480 && pos.y > 500 && pos.y < 756  && pos.lb != 0) )
						{
							drawYouLose();
							sleep(2);
							contagem = 8;
							loop_main_menu(mouse, irq_set_timer,irq_set, irq_set_kb,irq_set_rtc);
						}
					if (cont_lb == 4)
						if (pos.x > 500 && pos.x < 680 && pos.y > 200 && pos.y < 456 && pos.lb != 0)
						{
							contagem++;
							cont_lb++;
						}
						else if ((pos.x > 100 && pos.x < 280 && pos.y > 200 && pos.y < 456 && pos.lb != 0) || (pos.x > 300 && pos.x < 480 && pos.y > 200 && pos.y < 456 && pos.lb != 0) ||(pos.x > 700 && pos.x < 880 && pos.y > 200 && pos.y < 456 && pos.lb != 0) || (pos.x > 100 && pos.x < 280 && pos.y > 500 && pos.y < 756 && pos.lb != 0) /*|| (pos.x > 500 && pos.x < 680 && pos.y > 200 && pos.y < 456 && pos.lb != 0) || (pos.x > 500 && pos.x < 680 && pos.y > 500 && pos.y < 756 && pos.lb != 0) */|| (pos.x > 700 && pos.x < 880 && pos.y > 500 && pos.y < 756 && pos.lb != 0) ||(pos.x > 300 && pos.x < 480 && pos.y > 500 && pos.y < 756  && pos.lb != 0) )
						{
							drawYouLose();
							sleep(2);
							contagem = 8;
							loop_main_menu(mouse, irq_set_timer,irq_set, irq_set_kb,irq_set_rtc);
						}
					if (cont_lb == 5)
						if (pos.x > 300 && pos.x < 480 && pos.y > 500 && pos.y < 756 && pos.lb != 0)
						{
							contagem++;
							cont_lb++;
						}
						else if ((pos.x > 100 && pos.x < 280 && pos.y > 200 && pos.y < 456 && pos.lb != 0) || (pos.x > 300 && pos.x < 480 && pos.y > 200 && pos.y < 456 && pos.lb != 0) ||(pos.x > 700 && pos.x < 880 && pos.y > 200 && pos.y < 456 && pos.lb != 0) || (pos.x > 100 && pos.x < 280 && pos.y > 500 && pos.y < 756 && pos.lb != 0) /*|| (pos.x > 500 && pos.x < 680 && pos.y > 200 && pos.y < 456 && pos.lb != 0)*/ || (pos.x > 500 && pos.x < 680 && pos.y > 500 && pos.y < 756 && pos.lb != 0) || (pos.x > 700 && pos.x < 880 && pos.y > 500 && pos.y < 756 && pos.lb != 0) /*||(pos.x > 300 && pos.x < 480 && pos.y > 500 && pos.y < 756  && pos.lb != 0)*/ )
						{
							drawYouLose();
							sleep(2);
							contagem = 8;
							loop_main_menu(mouse, irq_set_timer,irq_set, irq_set_kb,irq_set_rtc);
						}
					if (cont_lb == 6)
						if (pos.x > 100 && pos.x < 280 && pos.y > 200 && pos.y < 456 && pos.lb != 0)
						{
							contagem++;
							cont_lb++;
						}
						else if (/*(pos.x > 100 && pos.x < 280 && pos.y > 200 && pos.y < 456 && pos.lb != 0) ||*/ (pos.x > 300 && pos.x < 480 && pos.y > 200 && pos.y < 456 && pos.lb != 0) ||(pos.x > 700 && pos.x < 880 && pos.y > 200 && pos.y < 456 && pos.lb != 0) || (pos.x > 100 && pos.x < 280 && pos.y > 500 && pos.y < 756 && pos.lb != 0) || (pos.x > 500 && pos.x < 680 && pos.y > 200 && pos.y < 456 && pos.lb != 0) || (pos.x > 500 && pos.x < 680 && pos.y > 500 && pos.y < 756 && pos.lb != 0) || (pos.x > 700 && pos.x < 880 && pos.y > 500 && pos.y < 756 && pos.lb != 0) /*||(pos.x > 300 && pos.x < 480 && pos.y > 500 && pos.y < 756  && pos.lb != 0) */)
						{
							drawYouLose();
							sleep(2);
							contagem = 8;
							loop_main_menu(mouse, irq_set_timer,irq_set,irq_set_kb,irq_set_rtc);
						}
					if (cont_lb == 7)
						if (pos.x > 700 && pos.x < 880 && pos.y > 200 && pos.y < 456 && pos.lb != 0)
						{
							drawYouWin();
							sleep(2);
							contagem++;
							cont_lb++;
							menu_name(mouse, irq_set_timer,irq_set, irq_set_kb,irq_set_rtc);
							//loop_main_menu(mouse, irq_set_timer,irq_set);
						}
						else if (/*(pos.x > 100 && pos.x < 280 && pos.y > 200 && pos.y < 456 && pos.lb != 0) ||*/ (pos.x > 300 && pos.x < 480 && pos.y > 200 && pos.y < 456 && pos.lb != 0) /*||(pos.x > 700 && pos.x < 880 && pos.y > 200 && pos.y < 456 && pos.lb != 0)*/ || (pos.x > 100 && pos.x < 280 && pos.y > 500 && pos.y < 756 && pos.lb != 0) || (pos.x > 500 && pos.x < 680 && pos.y > 200 && pos.y < 456 && pos.lb != 0) || (pos.x > 500 && pos.x < 680 && pos.y > 500 && pos.y < 756 && pos.lb != 0) || (pos.x > 700 && pos.x < 880 && pos.y > 500 && pos.y < 756 && pos.lb != 0) ||(pos.x > 300 && pos.x < 480 && pos.y > 500 && pos.y < 756  && pos.lb != 0) )
						{
							drawYouLose();
							sleep(2);
							contagem = 8;
							loop_main_menu(mouse, irq_set_timer,irq_set, irq_set_kb,irq_set_rtc);
						}

				}
				if (msg.NOTIFY_ARG & irq_set_timer)
				{
					c++;
					drawBlack();
					drawCards();
					drawReproduce();
					displayTimer(c);
					drawRato(pos.x,pos.y);
				}

				if (msg.NOTIFY_ARG & irq_set_kb)
				{
					sys_inb(OUT_BUF, &conf);
				}
				if (msg.NOTIFY_ARG & irq_set_rtc)
				{
					day();
					month();
					year();
				}

			}
		}
	}

	if (c == 20*60)
	{
		drawYouLose();
		sleep(2);
		loop_main_menu(mouse, irq_set_timer,irq_set,irq_set_kb, irq_set_rtc);
	}

	return 0;

}



int main_menu(mouse_data * mouse)
{
	drawMenu();

	int contagem = 0; // apenas para sair

	unsigned long irq_set_timer = timer_subscribe_int();
	int c = 0; //contagem do timer

	unsigned long irq_set_kb = kb_subscribe_int();

	unsigned long packet[3];
	int r, ipc_status;
	int count = 0; // contagem dos packets
	message msg;
	unsigned long data;

	unsigned long irq_set = mouse_subscribe_int();
	unsigned long conf;

	if (sys_outb(OUT_BUF, SET_SM) != OK) // set stream mode
		printf("Error while setting stream mode...\n");
	if (sys_outb(STAT_REG, WBTM) != OK) //write byte to mouse
		printf("Error while writing byte to mouse...\n");
	if (sys_outb(OUT_BUF, ENABLE_SM) != OK) // enable stream mode
		printf("Error enabling stream mode...\n");


	//set rtc
	unsigned long regB = BIT(4) | BIT(1);
	sys_outb(0x70, 0x0B);
	sys_outb(0x71, regB);

	unsigned long irq_set_rtc = rtc_subscribe_int();

	while ((contagem != 1) && (c < 30*60) && conf!=0x81)
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
						aux_menu(packet);
					}


					if (pos.x > 291 && pos.x < 728 && pos.y > 347 && pos.y < 441  && pos.lb != 0) //play
					{
						menu_levels(mouse, irq_set_timer,irq_set,irq_set_kb, irq_set_rtc);
						sleep(1);
						contagem = 1;
						return 0;
					}

					else if (pos.x > 291 && pos.x < 728 && pos.y > 471 && pos.y < 564  && pos.lb != 0) //highscores
					{
						menu_scores(mouse, irq_set_timer,irq_set,irq_set_kb,irq_set_rtc);
						sleep(1);
						contagem = 1;
						return 0;
					}
					else if (pos.x > 291 && pos.x < 728 && pos.y > 596 && pos.y < 691  && pos.lb != 0) //exit
					{
						contagem = 1;
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

						timer_unsubscribe_int();
						kb_unsubscribe_int();
						exitGraphics();
					}
				}

				if (msg.NOTIFY_ARG & irq_set_timer)
				{
					c++;
				}
				if (msg.NOTIFY_ARG & irq_set_kb)
				{
					sys_inb(OUT_BUF, &conf);
				}
				if (msg.NOTIFY_ARG & irq_set_rtc)
				{
					day();
					month();
					year();
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

	rtc_unsubscribe_int();
	timer_unsubscribe_int();
	kb_unsubscribe_int();
	return 0;
}

int menu_levels(mouse_data * mouse, unsigned long irq_set_timer, unsigned long irq_set, unsigned long irq_set_kb, unsigned long irq_set_rtc)
{
	drawLevels();

	pos.x = 600;
	pos.y = 442;

	int contagem = 0;
	int c = 0;

	unsigned long packet[3];
	int r, ipc_status;
	int count = 0; // contagem dos packets
	message msg;
	unsigned long data;

	unsigned long conf;

	while (contagem != 1)
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
						aux_levels(packet);
					}


					if (pos.x > 291 && pos.x < 728 && pos.y > 347 && pos.y < 441  && pos.lb != 0) //level 1
					{
						gameplay1(mouse, irq_set_timer,irq_set, irq_set_kb, irq_set_rtc);
						sleep(1);
						contagem = 1;
					}

					else if (pos.x > 291 && pos.x < 728 && pos.y > 471 && pos.y < 564  && pos.lb != 0) //level 2
					{
						gameplay2(mouse, irq_set_timer,irq_set, irq_set_kb, irq_set_rtc);
						sleep(1);
						contagem = 1;
					}
					else if (pos.x > 291 && pos.x < 728 && pos.y > 596 && pos.y < 691  && pos.lb != 0) //level 3
					{
						gameplay3(mouse, irq_set_timer,irq_set, irq_set_kb, irq_set_rtc);
						sleep(1);
						contagem = 1;
					}
					else if (pos.x > 30 && pos.x < 170 && pos.y > 636 && pos.y < 691  && pos.lb != 0) //go back
					{
						loop_main_menu(mouse, irq_set_timer,irq_set, irq_set_kb, irq_set_rtc);
						sleep(1);
						contagem = 1;
						return 0;
					}
				}

				if (msg.NOTIFY_ARG & irq_set_timer)
				{
					c++;
				}

				if (msg.NOTIFY_ARG & irq_set_kb)
				{
					sys_inb(OUT_BUF, &conf);
				}
				if (msg.NOTIFY_ARG & irq_set_rtc)
				{
					day();
					month();
					year();
				}

			}
		}
	}
	return 0;
}

int menu_scores(mouse_data * mouse, unsigned long irq_set_timer, unsigned long irq_set, unsigned long irq_set_kb, unsigned long irq_set_rtc)
{
	drawHighscores();

	pos.x = 500;
	pos.y = 500;

	int contagem = 0;
	int c = 0;

	unsigned long packet[3];
	int r, ipc_status;
	int count = 0; // contagem dos packets
	message msg;
	unsigned long data;

	unsigned long conf;

	read_scores();
	read_scores2();
	read_scores3();

	//draw_scores('j','o','a','o','.',19,12,17,400);
	//draw_scores('m','i','n','d','a',19,12,17,500);
	//draw_scores('p','a','u','l','o',12,2,18,600);

	while (contagem != 1)
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
						aux_scores(packet);
					}


					if (pos.x > 30 && pos.x < 165 && pos.y > 35 && pos.y < 140  && pos.lb != 0) //go back
					{
						loop_main_menu(mouse, irq_set_timer,irq_set, irq_set_kb,irq_set_rtc);
						sleep(1);
						contagem = 1;
						return 0;
					}
				}

				if (msg.NOTIFY_ARG & irq_set_timer)
				{
					c++;
				}

				if (msg.NOTIFY_ARG & irq_set_kb)
				{
					sys_inb(OUT_BUF, &conf);
				}
				if (msg.NOTIFY_ARG & irq_set_rtc)
				{
					day();
					month();
					year();
				}

			}
		}
	}
	return 0;
}

int loop_main_menu(mouse_data * mouse, unsigned long irq_set_timer, unsigned long irq_set, unsigned long irq_set_kb, unsigned long irq_set_rtc)
{
	drawMenu();

	pos.x = 500;
	pos.y = 450;

	int contagem = 0;
	int c = 0;

	unsigned long packet[3];
	int r, ipc_status;
	int count = 0; // contagem dos packets
	message msg;
	unsigned long data;

	unsigned long conf;

	while ((contagem != 1) && (c < 30*60))
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
						aux_menu(packet);
					}


					if (pos.x > 291 && pos.x < 728 && pos.y > 347 && pos.y < 441  && pos.lb != 0) //play
					{
						menu_levels(mouse, irq_set_timer,irq_set, irq_set_kb, irq_set_rtc);
						sleep(1);
						contagem = 1;
					}

					else if (pos.x > 291 && pos.x < 728 && pos.y > 471 && pos.y < 564  && pos.lb != 0) //highscores
					{
						menu_scores(mouse, irq_set_timer,irq_set,irq_set_kb, irq_set_rtc);
						sleep(1);
						contagem = 1;
					}
					else if (pos.x > 291 && pos.x < 728 && pos.y > 596 && pos.y < 691  && pos.lb != 0) //exit
					{
						contagem = 1;
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

						timer_unsubscribe_int();
						kb_unsubscribe_int();
						exitGraphics();
						return 0;
					}
				}

				if (msg.NOTIFY_ARG & irq_set_timer)
				{
					c++;
				}

				if (msg.NOTIFY_ARG & irq_set_kb)
				{
					sys_inb(OUT_BUF, &conf);
				}
				if (msg.NOTIFY_ARG & irq_set_rtc)
				{
					day();
					month();
					year();
				}

			}
		}
	}
	return 0;
}

int menu_name(mouse_data * mouse, unsigned long irq_set_timer, unsigned long irq_set, unsigned long irq_set_kb, unsigned long irq_set_rtc)
{
	drawCongrats(); //Insert your name(max 5 letras) and then type enter

	int contagem = 0; //contagem de letras

	pos.x = 100;
	pos.y = 100;

	unsigned short assembly = 0;

	int c = 0;

	unsigned long packet[3];
	int r, ipc_status;
	int count = 0; // contagem dos packets
	message msg;
	unsigned long data;

	unsigned long conf;

	char char1;
	char char2;
	char char3;
	char char4;
	char char5;
	int dia;
	int mes;
	int ano;

	while((contagem != 5) && (conf != KEY_ENTER))
	{
		if ( (r = driver_receive(ANY, &msg, &ipc_status)) != 0 ) {
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
					}
				}

				if (msg.NOTIFY_ARG & irq_set_rtc)
				{
					day();
					month();
					year();
				}

				if (msg.NOTIFY_ARG & irq_set_timer)
				{
					c++;
				}
				if (msg.NOTIFY_ARG & irq_set_kb)
				{
					if (assembly == 0) // em c
					{
						sys_inb(OUT_BUF, &conf);
					}
					if (contagem == 0)
					{
						if (conf == KEY_Q)
						{
							drawQ(437,600);
							contagem = 1;
							conf = 0;
							char1 = 'q';
						}
						if (conf == KEY_W)
						{
							drawW(437,600);
							contagem = 1;
							conf = 0;
							char1 = 'w';
						}
						if (conf == KEY_E)
						{
							drawE(437,600);
							contagem = 1;
							conf = 0;
							char1 = 'e';
						}
						if (conf == KEY_R)
						{
							drawR(437,600);
							contagem = 1;
							conf = 0;
							char1 = 'r';
						}
						if (conf == KEY_T)
						{
							drawT(437,600);
							contagem = 1;
							conf = 0;
							char1 = 't';
						}
						if (conf == KEY_Y)
						{
							drawY(437,600);
							contagem = 1;
							conf = 0;
							char1 = 'y';
						}
						if (conf == KEY_U)
						{
							drawU(437,600);
							contagem = 1;
							conf = 0;
							char1 = 'u';
						}
						if (conf == KEY_I)
						{
							drawI(437,600);
							contagem = 1;
							conf = 0;
							char1 = 'i';
						}
						if (conf == KEY_O)
						{
							drawO(437,600);
							contagem = 1;
							conf = 0;
							char1 = 'o';
						}
						if (conf == KEY_P)
						{
							drawP(437,600);
							contagem = 1;
							conf = 0;
							char1 = 'p';
						}
						if (conf == KEY_A)
						{
							drawA(437,600);
							contagem = 1;
							conf = 0;
							char1 = 'a';
						}
						if (conf == KEY_S)
						{
							drawS(437,600);
							contagem = 1;
							conf = 0;
							char1 = 's';
						}
						if (conf == KEY_D)
						{
							drawD(437,600);
							contagem = 1;
							conf = 0;
							char1 = 'd';
						}
						if (conf == KEY_F)
						{
							drawF(437,600);
							contagem = 1;
							conf = 0;
							char1 = 'f';
						}
						if (conf == KEY_G)
						{
							drawG(437,600);
							contagem = 1;
							conf = 0;
							char1 = 'g';
						}
						if (conf == KEY_H)
						{
							drawH(437,600);
							contagem = 1;
							conf = 0;
							char1 = 'h';
						}
						if (conf == KEY_J)
						{
							drawJ(437,600);
							contagem = 1;
							conf = 0;
							char1 = 'j';
						}
						if (conf == KEY_K)
						{
							drawK(437,600);
							contagem = 1;
							conf = 0;
							char1 = 'k';
						}
						if (conf == KEY_L)
						{
							drawL(437,600);
							contagem = 1;
							conf = 0;
							char1 = 'l';
						}
						if (conf == KEY_Z)
						{
							drawZ(437,600);
							contagem = 1;
							conf = 0;
							char1 = 'z';
						}
						if (conf == KEY_X)
						{
							drawX(437,600);
							contagem = 1;
							conf = 0;
							char1 = 'x';
						}
						if (conf == KEY_C)
						{
							drawC(437,600);
							contagem = 1;
							conf = 0;
							char1 = 'c';
						}
						if (conf == KEY_V)
						{
							drawV(437,600);
							contagem = 1;
							conf = 0;
							char1 = 'v';
						}
						if (conf == KEY_B)
						{
							drawB(437,600);
							contagem = 1;
							conf = 0;
							char1 = 'b';
						}
						if (conf == KEY_N)
						{
							drawN(437,600);
							contagem = 1;
							conf = 0;
							char1 = 'n';
						}
						if (conf == KEY_M)
						{
							drawM(437,600);
							contagem = 1;
							conf = 0;
							char1 = 'm';
						}
					}
					if (contagem == 1)
					{
						if (conf == KEY_Q)
						{
							drawQ(467,600);
							contagem = 2;
							conf = 0;
							char2 = 'q';
						}
						if (conf == KEY_W)
						{
							drawW(467,600);
							contagem = 2;
							conf = 0;
							char2 = 'w';
						}
						if (conf == KEY_E)
						{
							drawE(467,600);
							contagem = 2;
							conf = 0;
							char2 = 'e';
						}
						if (conf == KEY_R)
						{
							drawR(467,600);
							contagem = 2;
							conf = 0;
							char2 = 'r';
						}
						if (conf == KEY_T)
						{
							drawT(467,600);
							contagem = 2;
							conf = 0;
							char2 = 't';
						}
						if (conf == KEY_Y)
						{
							drawY(467,600);
							contagem = 2;
							conf = 0;
							char2 = 'y';
						}
						if (conf == KEY_U)
						{
							drawU(467,600);
							contagem = 2;
							conf = 0;
							char2 = 'u';
						}
						if (conf == KEY_I)
						{
							drawI(467,600);
							contagem = 2;
							conf = 0;
							char2 = 'i';
						}
						if (conf == KEY_O)
						{
							drawO(467,600);
							contagem = 2;
							conf = 0;
							char2 = 'o';
						}
						if (conf == KEY_P)
						{
							drawP(467,600);
							contagem = 2;
							conf = 0;
							char2 = 'p';
						}
						if (conf == KEY_A)
						{
							drawA(467,600);
							contagem = 2;
							conf = 0;
							char2 = 'a';
						}
						if (conf == KEY_S)
						{
							drawS(467,600);
							contagem = 2;
							conf = 0;
							char2 = 's';
						}
						if (conf == KEY_D)
						{
							drawD(467,600);
							contagem = 2;
							conf = 0;
							char2 = 'd';
						}
						if (conf == KEY_F)
						{
							drawF(467,600);
							contagem = 2;
							conf = 0;
							char2 = 'f';
						}
						if (conf == KEY_G)
						{
							drawG(467,600);
							contagem = 2;
							conf = 0;
							char2 = 'g';
						}
						if (conf == KEY_H)
						{
							drawH(467,600);
							contagem = 2;
							conf = 0;
							char2 = 'h';
						}
						if (conf == KEY_J)
						{
							drawJ(467,600);
							contagem = 2;
							conf = 0;
							char2 = 'j';
						}
						if (conf == KEY_K)
						{
							drawK(467,600);
							contagem = 2;
							conf = 0;
							char2 = 'k';
						}
						if (conf == KEY_L)
						{
							drawL(467,600);
							contagem = 2;
							conf = 0;
							char2 = 'l';
						}
						if (conf == KEY_Z)
						{
							drawZ(467,600);
							contagem = 2;
							conf = 0;
							char2 = 'z';
						}
						if (conf == KEY_X)
						{
							drawX(467,600);
							contagem = 2;
							conf = 0;
							char2 = 'x';
						}
						if (conf == KEY_C)
						{
							drawC(467,600);
							contagem = 2;
							conf = 0;
							char2 = 'c';
						}
						if (conf == KEY_V)
						{
							drawV(467,600);
							contagem = 2;
							conf = 0;
							char2 = 'v';
						}
						if (conf == KEY_B)
						{
							drawB(467,600);
							contagem = 2;
							conf = 0;
							char2 = 'b';
						}
						if (conf == KEY_N)
						{
							drawN(467,600);
							contagem = 2;
							conf = 0;
							char2 = 'n';
						}
						if (conf == KEY_M)
						{
							drawM(467,600);
							contagem = 2;
							conf = 0;
							char2 = 'm';
						}
					}
					if (contagem == 2)
					{
						if (conf == KEY_Q)
						{
							drawQ(497,600);
							contagem = 3;
							conf = 0;
							char3 = 'q';
						}
						if (conf == KEY_W)
						{
							drawW(497,600);
							contagem = 3;
							conf = 0;
							char3 = 'w';
						}
						if (conf == KEY_E)
						{
							drawE(497,600);
							contagem = 3;
							conf = 0;
							char3 = 'e';
						}
						if (conf == KEY_R)
						{
							drawR(497,600);
							contagem = 3;
							conf = 0;
							char3 = 'r';
						}
						if (conf == KEY_T)
						{
							drawT(497,600);
							contagem = 3;
							conf = 0;
							char3 = 't';
						}
						if (conf == KEY_Y)
						{
							drawY(497,600);
							contagem = 3;
							conf = 0;
							char3 = 'y';
						}
						if (conf == KEY_U)
						{
							drawU(497,600);
							contagem = 3;
							conf = 0;
							char3 = 'u';
						}
						if (conf == KEY_I)
						{
							drawI(497,600);
							contagem = 3;
							conf = 0;
							char3 = 'i';
						}
						if (conf == KEY_O)
						{
							drawO(497,600);
							contagem = 3;
							conf = 0;
							char3 = 'o';
						}
						if (conf == KEY_P)
						{
							drawP(497,600);
							contagem = 3;
							conf = 0;
							char3 = 'p';
						}
						if (conf == KEY_A)
						{
							drawA(497,600);
							contagem = 3;
							conf = 0;
							char3 = 'a';
						}
						if (conf == KEY_S)
						{
							drawS(497,600);
							contagem = 3;
							conf = 0;
							char3 = 's';
						}
						if (conf == KEY_D)
						{
							drawD(497,600);
							contagem = 3;
							conf = 0;
							char3 = 'd';
						}
						if (conf == KEY_F)
						{
							drawF(497,600);
							contagem = 3;
							conf = 0;
							char3 = 'f';
						}
						if (conf == KEY_G)
						{
							drawG(497,600);
							contagem = 3;
							conf = 0;
							char3 = 'g';
						}
						if (conf == KEY_H)
						{
							drawH(497,600);
							contagem = 3;
							conf = 0;
							char3 = 'h';
						}
						if (conf == KEY_J)
						{
							drawJ(497,600);
							contagem = 3;
							conf = 0;
							char3 = 'j';
						}
						if (conf == KEY_K)
						{
							drawK(497,600);
							contagem = 3;
							conf = 0;
							char3 = 'k';
						}
						if (conf == KEY_L)
						{
							drawL(497,600);
							contagem = 3;
							conf = 0;
							char3 = 'l';
						}
						if (conf == KEY_Z)
						{
							drawZ(497,600);
							contagem = 3;
							conf = 0;
							char3 = 'z';
						}
						if (conf == KEY_X)
						{
							drawX(497,600);
							contagem = 3;
							conf = 0;
							char3 = 'x';
						}
						if (conf == KEY_C)
						{
							drawC(497,600);
							contagem = 3;
							conf = 0;
							char3 = 'c';
						}
						if (conf == KEY_V)
						{
							drawV(497,600);
							contagem = 3;
							conf = 0;
							char3 = 'v';
						}
						if (conf == KEY_B)
						{
							drawB(497,600);
							contagem = 3;
							conf = 0;
							char3 = 'b';
						}
						if (conf == KEY_N)
						{
							drawN(497,600);
							contagem = 3;
							conf = 0;
							char3 = 'n';
						}
						if (conf == KEY_M)
						{
							drawM(497,600);
							contagem = 3;
							conf = 0;
							char3 = 'm';
						}
					}
					if (contagem == 3)
					{
						if (conf == KEY_Q)
						{
							drawQ(527,600);
							contagem = 4;
							conf = 0;
							char4 = 'q';
						}
						if (conf == KEY_W)
						{
							drawW(527,600);
							contagem = 4;
							conf = 0;
							char4 = 'w';
						}
						if (conf == KEY_E)
						{
							drawE(527,600);
							contagem = 4;
							conf = 0;
							char4 = 'e';
						}
						if (conf == KEY_R)
						{
							drawR(527,600);
							contagem = 4;
							conf = 0;
							char4 = 'r';
						}
						if (conf == KEY_T)
						{
							drawT(527,600);
							contagem = 4;
							conf = 0;
							char4 = 't';
						}
						if (conf == KEY_Y)
						{
							drawY(527,600);
							contagem = 4;
							conf = 0;
							char4 = 'y';
						}
						if (conf == KEY_U)
						{
							drawU(527,600);
							contagem = 4;
							conf = 0;
							char4 = 'u';
						}
						if (conf == KEY_I)
						{
							drawI(527,600);
							contagem = 4;
							conf = 0;
							char4 = 'i';
						}
						if (conf == KEY_O)
						{
							drawO(527,600);
							contagem = 4;
							conf = 0;
							char4 = 'o';
						}
						if (conf == KEY_P)
						{
							drawP(527,600);
							contagem = 4;
							conf = 0;
							char4 = 'p';
						}
						if (conf == KEY_A)
						{
							drawA(527,600);
							contagem = 4;
							conf = 0;
							char4 = 'a';
						}
						if (conf == KEY_S)
						{
							drawS(527,600);
							contagem = 4;
							conf = 0;
							char4 = 's';
						}
						if (conf == KEY_D)
						{
							drawD(527,600);
							contagem = 4;
							conf = 0;
							char4 = 's';
						}
						if (conf == KEY_F)
						{
							drawF(527,600);
							contagem = 4;
							conf = 0;
							char4 = 'f';
						}
						if (conf == KEY_G)
						{
							drawG(527,600);
							contagem = 4;
							conf = 0;
							char4 = 'g';
						}
						if (conf == KEY_H)
						{
							drawH(527,600);
							contagem = 4;
							conf = 0;
							char4 = 'h';
						}
						if (conf == KEY_J)
						{
							drawJ(527,600);
							contagem = 4;
							conf = 0;
							char4 = 'j';
						}
						if (conf == KEY_K)
						{
							drawK(527,600);
							contagem = 4;
							conf = 0;
							char4 = 'k';
						}
						if (conf == KEY_L)
						{
							drawL(527,600);
							contagem = 4;
							conf = 0;
							char4 = 'l';
						}
						if (conf == KEY_Z)
						{
							drawZ(527,600);
							contagem = 4;
							conf = 0;
							char4 = 'z';
						}
						if (conf == KEY_X)
						{
							drawX(527,600);
							contagem = 4;
							conf = 0;
							char4 = 'x';
						}
						if (conf == KEY_C)
						{
							drawC(527,600);
							contagem = 4;
							conf = 0;
							char4 = 'c';
						}
						if (conf == KEY_V)
						{
							drawV(527,600);
							contagem = 4;
							conf = 0;
							char4 = 'v';
						}
						if (conf == KEY_B)
						{
							drawB(527,600);
							contagem = 4;
							conf = 0;
							char4 = 'b';
						}
						if (conf == KEY_N)
						{
							drawN(527,600);
							contagem = 4;
							conf = 0;
							char4 = 'n';
						}
						if (conf == KEY_M)
						{
							drawM(527,600);
							contagem = 4;
							conf = 0;
							char4 = 'm';
						}
					}
					if (contagem == 4)
					{
						if (conf == KEY_Q)
						{
							drawQ(557,600);
							contagem++;
							char5 = 'q';
						}
						if (conf == KEY_W)
						{
							drawW(557,600);
							contagem++;
							char5 = 'w';
						}
						if (conf == KEY_E)
						{
							drawE(557,600);
							contagem++;
							char5 = 'e';
						}
						if (conf == KEY_R)
						{
							drawR(557,600);
							contagem++;
							char5 = 'r';
						}
						if (conf == KEY_T)
						{
							drawT(557,600);
							contagem++;
							char5 = 't';
						}
						if (conf == KEY_Y)
						{
							drawY(557,600);
							contagem++;
							char5 = 'y';
						}
						if (conf == KEY_U)
						{
							drawU(557,600);
							contagem++;
							char5 = 'u';
						}
						if (conf == KEY_I)
						{
							drawI(557,600);
							contagem++;
							char5 = 'i';
						}
						if (conf == KEY_O)
						{
							drawO(557,600);
							contagem++;
							char5 = 'o';
						}
						if (conf == KEY_P)
						{
							drawP(557,600);
							contagem++;
							char5 = 'p';
						}
						if (conf == KEY_A)
						{
							drawA(557,600);
							contagem++;
							char5 = 'a';
						}
						if (conf == KEY_S)
						{
							drawS(557,600);
							contagem++;
							char5 = 's';
						}
						if (conf == KEY_D)
						{
							drawD(557,600);
							contagem++;
							char5 = 'd';
						}
						if (conf == KEY_F)
						{
							drawF(557,600);
							contagem++;
							char5 = 'f';
						}
						if (conf == KEY_G)
						{
							drawG(557,600);
							contagem++;
							char5 = 'g';
						}
						if (conf == KEY_H)
						{
							drawH(557,600);
							contagem++;
							char5 = 'h';
						}
						if (conf == KEY_J)
						{
							drawJ(557,600);
							contagem++;
							char5 = 'j';
						}
						if (conf == KEY_K)
						{
							drawK(557,600);
							contagem++;
							char5 = 'k';
						}
						if (conf == KEY_L)
						{
							drawL(557,600);
							contagem++;
							char5 = 'l';
						}
						if (conf == KEY_Z)
						{
							drawZ(557,600);
							contagem++;
							char5 = 'z';
						}
						if (conf == KEY_X)
						{
							drawX(557,600);
							contagem++;
							char5 = 'x';
						}
						if (conf == KEY_C)
						{
							drawC(557,600);
							contagem++;
							char5 = 'c';
						}
						if (conf == KEY_V)
						{
							drawV(557,600);
							contagem++;
							char5 = 'v';
						}
						if (conf == KEY_B)
						{
							drawB(557,600);
							contagem++;
							char5 = 'b';
						}
						if (conf == KEY_N)
						{
							drawN(557,600);
							contagem++;
							char5 = 'n';
						}
						if (conf == KEY_M)
						{
							drawM(557,600);
							contagem++;
							char5 = 'm';
						}
					}
				}
				break;
			default:
				break;
			}
		}

	}
	dia = (((day() & 0xF0) >> 4) * 10) + (day() & 0x0F);
	mes =(((month() & 0xF0) >> 4) * 10) + (month() & 0x0F);
	ano = (((year() & 0xF0) >> 4) * 10) + (year() & 0x0F);

	write_newscore3();
	write_newscore2();
	write_scores(char1, char2, char3, char4, char5, dia, mes, ano);
	sleep(1);
	loop_main_menu(mouse,irq_set_timer, irq_set, irq_set_kb, irq_set_rtc);

	return 0;
}


void write_scores(char c1, char c2, char c3, char c4, char c5, int dia, int mes, int ano)
{
	char name[6];
	FILE *file;
	file = fopen("/home/lcom/memgame/proj/res/scores.txt", "w");
	name[0] = c1;
	name[1] = c2;
	name[2] = c3;
	name[3] = c4;
	name[4] = c5;

	fprintf(file, "%s\n", name);

	if (dia == 1 || dia == 2 || dia == 3 || dia == 4 || dia == 5 || dia == 6 || dia == 7 || dia == 8 || dia == 9)
	{
		fputc('8', file);
		fprintf(file, "%d", dia);
	}
	else
		fprintf(file, "%d", dia);

	fputc(' ', file);

	if (mes == 1 || mes == 2 || mes == 3 || mes == 4 || mes == 5 || mes == 6 || mes == 7 || mes == 8 || mes == 9)
	{
		fputc('8', file);
		fprintf(file, "%d", mes);
	}
	else
		fprintf(file, "%d", mes);
	fputc(' ', file);
	fprintf(file, "%d", ano);
	fputc('\n', file);
	fclose(file);
}

void write_newscore2()
{

	FILE *file;
	char name[6];
	file = fopen("/home/lcom/memgame/proj/res/scores.txt", "r");

	char ch1, ch2;
	int dia, mes,ano;
	//name
	fgets(name, 6, file);

	ch1 = fgetc(file);

	//day
	ch1 = fgetc(file);
	ch2 = fgetc(file);
	dia = (ch1 - '0') * 10 + (ch2 - '0');


	// ignores the space ' '
	ch1 = fgetc(file);

	//month
	ch1 = fgetc(file);
	ch2 = fgetc(file);
	mes = (ch1 - '0') * 10 + (ch2 - '0');

	// ignores the space ' '
	ch1 = fgetc(file);

	//year
	ch1 = fgetc(file);
	ch2 = fgetc(file);
	ano = (ch1 - '0') * 10 + (ch2 - '0');

	fclose(file);

	FILE *file1;
	file1 = fopen("/home/lcom/memgame/proj/res/scores2.txt", "w");
	fprintf(file1, "%s\n", name);
	fprintf(file1, "%d", dia);
	fputc(' ', file1);
	fprintf(file1, "%d", mes);
	fputc(' ', file1);
	fprintf(file1, "%d", ano);
	fputc('\n', file1);
	fclose(file1);
}

void write_newscore3()
{
	FILE *file;
	char name[6];
	file = fopen("/home/lcom/memgame/proj/res/scores2.txt", "r");

	char ch1, ch2;
	int dia, mes,ano;
	//name
	fgets(name, 6, file);

	ch1 = fgetc(file);

	//day
	ch1 = fgetc(file);
	ch2 = fgetc(file);
	dia = (ch1 - '0') * 10 + (ch2 - '0');


	// ignores the space ' '
	ch1 = fgetc(file);

	//month
	ch1 = fgetc(file);
	ch2 = fgetc(file);
	mes = (ch1 - '0') * 10 + (ch2 - '0');

	// ignores the space ' '
	ch1 = fgetc(file);

	//year
	ch1 = fgetc(file);
	ch2 = fgetc(file);
	ano = (ch1 - '0') * 10 + (ch2 - '0');

	fclose(file);

	FILE *file1;
	file1 = fopen("/home/lcom/memgame/proj/res/scores3.txt", "w");
	fprintf(file1, "%s\n", name);
	fprintf(file1, "%d", dia);
	fputc(' ', file1);
	fprintf(file1, "%d", mes);
	fputc(' ', file1);
	fprintf(file1, "%d", ano);
	fputc('\n', file1);
	fclose(file1);
}

void read_scores()
{
	FILE *file;
	char name[6];
	file = fopen("/home/lcom/memgame/proj/res/scores.txt", "r");

	char ch1, ch2;
	int dia, mes,ano;
	//name
	fgets(name, 6, file);

	ch1 = fgetc(file);

	//day
	ch1 = fgetc(file);
	ch2 = fgetc(file);
	dia = (ch1 - '0') * 10 + (ch2 - '0');


	// ignores the space ' '
	ch1 = fgetc(file);

	//month
	ch1 = fgetc(file);
	ch2 = fgetc(file);
	mes = (ch1 - '0') * 10 + (ch2 - '0');

	// ignores the space ' '
	ch1 = fgetc(file);

	//year
	ch1 = fgetc(file);
	ch2 = fgetc(file);
	ano = (ch1 - '0') * 10 + (ch2 - '0');


	draw_scores(name[0],name[1],name[2],name[3],name[4],dia,mes,ano,400);
	fclose(file);
}


void read_scores2()
{
	FILE *file;
	char name[6];
	file = fopen("/home/lcom/memgame/proj/res/scores2.txt", "r");

	char ch1, ch2;
	int dia, mes,ano;
	//name
	fgets(name, 6, file);

	ch1 = fgetc(file);

	//day
	ch1 = fgetc(file);
	ch2 = fgetc(file);
	dia = (ch1 - '0') * 10 + (ch2 - '0');


	// ignores the space ' '
	ch1 = fgetc(file);

	//month
	ch1 = fgetc(file);
	ch2 = fgetc(file);
	mes = (ch1 - '0') * 10 + (ch2 - '0');

	// ignores the space ' '
	ch1 = fgetc(file);

	//year
	ch1 = fgetc(file);
	ch2 = fgetc(file);
	ano = (ch1 - '0') * 10 + (ch2 - '0');


	draw_scores(name[0],name[1],name[2],name[3],name[4],dia,mes,ano,500);
	fclose(file);
}

void read_scores3()
{
	FILE *file;
	char name[6];
	file = fopen("/home/lcom/memgame/proj/res/scores3.txt", "r");

	char ch1, ch2;
	int dia, mes,ano;
	//name
	fgets(name, 6, file);

	ch1 = fgetc(file);

	//day
	ch1 = fgetc(file);
	ch2 = fgetc(file);
	dia = (ch1 - '0') * 10 + (ch2 - '0');


	// ignores the space ' '
	ch1 = fgetc(file);

	//month
	ch1 = fgetc(file);
	ch2 = fgetc(file);
	mes = (ch1 - '0') * 10 + (ch2 - '0');

	// ignores the space ' '
	ch1 = fgetc(file);

	//year
	ch1 = fgetc(file);
	ch2 = fgetc(file);
	ano = (ch1 - '0') * 10 + (ch2 - '0');


	draw_scores(name[0],name[1],name[2],name[3],name[4],dia,mes,ano,600);
	fclose(file);
}

void draw_scores(char c1, char c2, char c3, char c4, char c5,int d1, int m1, int y1,int coord)
{

		if (c1 == 'q')
			drawQ(150,coord);
		if (c1 == 'w')
			drawW(150,coord);
		if (c1 == 'e')
			drawE(150,coord);
		if (c1 == 'r')
			drawR(150,coord);
		if (c1 == 't')
			drawT(150,coord);
		if (c1 == 'y')
			drawY(150,coord);
		if (c1 == 'u')
			drawU(150,coord);
		if (c1 == 'i')
			drawI(150,coord);
		if (c1 == 'o')
			drawO(150,coord);
		if (c1 == 'p')
			drawP(150,coord);
		if (c1 == 'a')
			drawA(150,coord);
		if (c1 == 's')
			drawS(150,coord);
		if (c1 == 'd')
			drawD(150,coord);
		if (c1 == 'f')
			drawF(150,coord);
		if (c1 == 'g')
			drawG(150,coord);
		if (c1 == 'h')
			drawH(150,coord);
		if (c1 == 'j')
			drawJ(150,coord);
		if (c1 == 'k')
			drawK(150,coord);
		if (c1 == 'l')
			drawL(150,coord);
		if (c1 == 'z')
			drawZ(150,coord);
		if (c1 == 'x')
			drawX(150,coord);
		if (c1 == 'c')
			drawC(150,coord);
		if (c1 == 'v')
			drawV(150,coord);
		if (c1 == 'b')
			drawB(150,coord);
		if (c1 == 'n')
			drawN(150,coord);
		if (c1 == 'm')
			drawM(150,coord);

		//

		if (c2 == 'q')
			drawQ(180,coord);
		if (c2 == 'w')
			drawW(180,coord);
		if (c2 == 'e')
			drawE(180,coord);
		if (c2 == 'r')
			drawR(180,coord);
		if (c2 == 't')
			drawT(180,coord);
		if (c2 == 'y')
			drawY(180,coord);
		if (c2 == 'u')
			drawU(180,coord);
		if (c2 == 'i')
			drawI(180,coord);
		if (c2 == 'o')
			drawO(180,coord);
		if (c2 == 'p')
			drawP(180,coord);
		if (c2 == 'a')
			drawA(180,coord);
		if (c2 == 's')
			drawS(180,coord);
		if (c2 == 'd')
			drawD(180,coord);
		if (c2 == 'f')
			drawF(180,coord);
		if (c2 == 'g')
			drawG(180,coord);
		if (c2 == 'h')
			drawH(180,coord);
		if (c2 == 'j')
			drawJ(180,coord);
		if (c2 == 'k')
			drawK(180,coord);
		if (c2 == 'l')
			drawL(180,coord);
		if (c2 == 'z')
			drawZ(180,coord);
		if (c2 == 'x')
			drawX(180,coord);
		if (c2 == 'c')
			drawC(180,coord);
		if (c2 == 'v')
			drawV(180,coord);
		if (c2 == 'b')
			drawB(180,coord);
		if (c2 == 'n')
			drawN(180,coord);
		if (c2 == 'm')
			drawM(180,coord);

		//

		if (c3 == 'q')
			drawQ(210,coord);
		if (c3 == 'w')
			drawW(210,coord);
		if (c3 == 'e')
			drawE(210,coord);
		if (c3 == 'r')
			drawR(210,coord);
		if (c3 == 't')
			drawT(210,coord);
		if (c3 == 'y')
			drawY(210,coord);
		if (c3 == 'u')
			drawU(210,coord);
		if (c3 == 'i')
			drawI(210,coord);
		if (c3 == 'o')
			drawO(210,coord);
		if (c3 == 'p')
			drawP(210,coord);
		if (c3 == 'a')
			drawA(210,coord);
		if (c3 == 's')
			drawS(210,coord);
		if (c3 == 'd')
			drawD(210,coord);
		if (c3 == 'f')
			drawF(210,coord);
		if (c3 == 'g')
			drawG(210,coord);
		if (c3 == 'h')
			drawH(210,coord);
		if (c3 == 'j')
			drawJ(210,coord);
		if (c3 == 'k')
			drawK(210,coord);
		if (c3 == 'l')
			drawL(210,coord);
		if (c3 == 'z')
			drawZ(210,coord);
		if (c3 == 'x')
			drawX(210,coord);
		if (c3 == 'c')
			drawC(210,coord);
		if (c3 == 'v')
			drawV(210,coord);
		if (c3 == 'b')
			drawB(210,coord);
		if (c3 == 'n')
			drawN(210,coord);
		if (c3 == 'm')
			drawM(210,coord);

		//

		if (c4 == 'q')
			drawQ(240,coord);
		if (c4 == 'w')
			drawW(240,coord);
		if (c4 == 'e')
			drawE(240,coord);
		if (c4 == 'r')
			drawR(240,coord);
		if (c4 == 't')
			drawT(240,coord);
		if (c4 == 'y')
			drawY(240,coord);
		if (c4 == 'u')
			drawU(240,coord);
		if (c4 == 'i')
			drawI(240,coord);
		if (c4 == 'o')
			drawO(240,coord);
		if (c4 == 'p')
			drawP(240,coord);
		if (c4 == 'a')
			drawA(240,coord);
		if (c4 == 's')
			drawS(240,coord);
		if (c4 == 'd')
			drawD(240,coord);
		if (c4 == 'f')
			drawF(240,coord);
		if (c4 == 'g')
			drawG(240,coord);
		if (c4 == 'h')
			drawH(240,coord);
		if (c4 == 'j')
			drawJ(240,coord);
		if (c4 == 'k')
			drawK(240,coord);
		if (c4 == 'l')
			drawL(240,coord);
		if (c4 == 'z')
			drawZ(240,coord);
		if (c4 == 'x')
			drawX(240,coord);
		if (c4 == 'c')
			drawC(240,coord);
		if (c4 == 'v')
			drawV(240,coord);
		if (c4 == 'b')
			drawB(240,coord);
		if (c4 == 'n')
			drawN(240,coord);
		if (c4 == 'm')
			drawM(240,coord);

		//

		if (c5 == 'q')
			drawQ(270,coord);
		if (c5 == 'w')
			drawW(270,coord);
		if (c5 == 'e')
			drawE(270,coord);
		if (c5 == 'r')
			drawR(270,coord);
		if (c5 == 't')
			drawT(270,coord);
		if (c5 == 'y')
			drawY(270,coord);
		if (c5 == 'u')
			drawU(270,coord);
		if (c5 == 'i')
			drawI(270,coord);
		if (c5 == 'o')
			drawO(270,coord);
		if (c5 == 'p')
			drawP(270,coord);
		if (c5 == 'a')
			drawA(270,coord);
		if (c5 == 's')
			drawS(270,coord);
		if (c5 == 'd')
			drawD(270,coord);
		if (c5 == 'f')
			drawF(270,coord);
		if (c5 == 'g')
			drawG(270,coord);
		if (c5 == 'h')
			drawH(270,coord);
		if (c5 == 'j')
			drawJ(270,coord);
		if (c5 == 'k')
			drawK(270,coord);
		if (c5 == 'l')
			drawL(270,coord);
		if (c5 == 'z')
			drawZ(270,coord);
		if (c5 == 'x')
			drawX(270,coord);
		if (c5 == 'c')
			drawC(270,coord);
		if (c5 == 'v')
			drawV(270,coord);
		if (c5 == 'b')
			drawB(270,coord);
		if (c5 == 'n')
			drawN(270,coord);
		if (c5 == 'm')
			drawM(270,coord);

		//

		if (d1 == 81)
			draw1(600,coord);
		if (d1 == 82)
			draw2(600,coord);
		if (d1 == 83)
			draw3(600,coord);
		if (d1 == 84)
			draw4(600,coord);
		if (d1 == 85)
			draw5(600,coord);
		if (d1 == 86)
			draw6(600,coord);
		if (d1 == 87)
			draw7(600,coord);
		if (d1 == 88)
			draw8(600,coord);
		if (d1 == 89)
			draw9(600,coord);
		if (d1 == 10)
			draw10(600,coord);
		if (d1 == 11)
			draw11(600,coord);
		if (d1 == 12)
			draw12(600,coord);
		if (d1 == 13)
			draw13(600,coord);
		if (d1 == 14)
			draw14(600,coord);
		if (d1 == 15)
			draw15(600,coord);
		if (d1 == 16)
			draw16(600,coord);
		if (d1 == 17)
			draw17(600,coord);
		if (d1 == 18)
			draw18(600,coord);
		if (d1 == 19)
			draw19(600,coord);
		if (d1 == 20)
			draw20(600,coord);
		if (d1 == 21)
			draw21(600,coord);
		if (d1 == 22)
			draw22(600,coord);
		if (d1 == 23)
			draw23(600,coord);
		if (d1 == 24)
			draw24(600,coord);
		if (d1 == 25)
			draw25(600,coord);
		if (d1 == 26)
			draw26(600,coord);
		if (d1 == 27)
			draw27(600,coord);
		if (d1 == 28)
			draw28(600,coord);
		if (d1 == 29)
			draw29(600,coord);
		if (d1 == 30)
			draw30(600,coord);
		if (d1 == 31)
			draw31(600,coord);

		//

		if (m1 == 81)
			draw1(700,coord);
		if (m1 == 82)
			draw2(700,coord);
		if (m1 == 83)
			draw3(700,coord);
		if (m1 == 84)
			draw4(700,coord);
		if (m1 == 85)
			draw5(700,coord);
		if (m1 == 86)
			draw6(700,coord);
		if (m1 == 87)
			draw7(700,coord);
		if (m1 == 88)
			draw8(700,coord);
		if (m1 == 89)
			draw9(700,coord);
		if (m1 == 10)
			draw10(700,coord);
		if (m1 == 11)
			draw11(700,coord);
		if (m1 == 12)
			draw12(700,coord);

		//

		if (y1 == 17)
			draw17(800,coord);
		if (y1 == 18)
			draw18(800,coord);

		drawBarra(670, coord);
		drawBarra(770, coord);


}

void displayTimer(int c)
{
	if (c/60 == 0)
		drawb20(900,110);
	if (c/60 == 1)
	{
		square(900,110,50,BLACK);
		drawb19(900,110);
	}
	if (c/60 == 2)
	{
		square(900,110,50,BLACK);
		drawb18(900,110);
	}
	if (c/60 == 3)
	{
		square(900,110,50,BLACK);
		drawb17(900,110);
	}

	if (c/60 == 4)
	{
		square(900,110,50,BLACK);
		drawb16(900,110);
	}
	if (c/60 == 5)
	{
		square(900,110,50,BLACK);
		drawb15(900,110);
	}

	if (c/60 == 6)
	{
		square(900,110,50,BLACK);
		drawb14(900,110);
	}

	if (c/60 == 7)
	{
		square(900,110,50,BLACK);
		drawb13(900,110);
	}

	if (c/60 == 8)
	{
		square(900,110,50,BLACK);
		drawb12(900,110);
	}

	if (c/60 == 9)
	{
		square(900,110,50,BLACK);
		drawb11(900,110);
	}

	if (c/60 == 10)
	{
		square(900,110,50,BLACK);
		drawb10(900,110);
	}

	if (c/60 == 11)
	{
		square(900,110,50,BLACK);
		drawb9(900,110);
	}

	if (c/60 == 12)
	{
		square(900,110,50,BLACK);
		drawb8(900,110);
	}

	if (c/60 == 13)
	{
		square(900,110,50,BLACK);
		drawb7(900,110);
	}
	if (c/60 == 14)
	{
		square(900,110,50,BLACK);
		drawb6(900,110);
	}
	if (c/60 == 15)
	{
		square(900,110,50,BLACK);
		drawb5(900,110);
	}

	if (c/60 == 16)
	{
		square(900,110,50,BLACK);
		drawb4(900,110);
	}

	if (c/60 == 17)
	{
		square(900,110,50,BLACK);
		drawb3(900,110);
	}

	if (c/60 == 18)
	{
		square(900,110,50,BLACK);
		drawb2(900,110);
	}

	if (c/60 == 19)
	{
		square(900,110,50,BLACK);
		drawb1(900,110);
	}
}
