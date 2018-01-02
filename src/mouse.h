#ifndef __MOUSE_H
#define __MOUSE_H

/** @defgroup mouse mouse
 * @{
 *
 * Functions for using the mouse code
 */

#include <minix/drivers.h>

//static unsigned long packet[3];

//--------------------------------------------------------

typedef struct {
	unsigned char pack[3];
    int xSign, ySign;
    int xx, yy;
    int leftButtonDown;
    int middleButtonDown;
    int rightButtonDown;
} mouse_data;

typedef struct{
	int x;
	int y;
	int lb;
} mouse_pos;


//--------------------------------------------------------

/**
 * @brief Subscribes mouse
 */
int mouse_subscribe_int();

/**
 * @brief Unsubscribes mouse
 */
int mouse_unsubscribe_int();

int mouse_readByte(unsigned long *data);

/**
 * @brief Enables mouse
 */
void enable_mouse();

/**
 * @brief Disables mouse
 */
void disable_mouse();
void mouse_aux();

/**
 * @brief Analizes the packet related with the mouse interrupsts
 *
 * @param packet[3] packet of 3 bytes received from the mouse
 *
 * @return returns mouse data
 */
mouse_data mouse_get_packet(unsigned long packet[3]);

/**
 * @brief paints the mouse
 */
void draw_mouse();

/**
 * @brief paints the mouse with its actual position in the gameplay menu
 *
 * @param packet[3] packet of 3 bytes received from the mouse
 */
void aux(unsigned long packet[3], int c);

/**
 * @brief paints the mouse with its actual position in the mainmenu
 *
 * @param packet[3] packet of 3 bytes received from the mouse
 */
void aux_menu(unsigned long packet[3]);

/**
 * @brief paints the mouse with its actual position in the levels menu
 *
 * @param packet[3] packet of 3 bytes received from the mouse
 */
void aux_levels(unsigned long packet[3]);

/**
 * @brief paints the mouse with its actual position in the scores menu
 *
 * @param packet[3] packet of 3 bytes received from the mouse
 */
void aux_scores(unsigned long packet[3]);


// Macros

#define BIT(n) (0x01<<(n))
#define DELAY_US 20000
#define MOUSE_IRQ 12
#define TIMER0_IRQ 0
#define OUT_BUF 0x60
#define IN_BUF 0x60
#define OBF 0x01
#define WBTM 0xD4
#define SET_SM 0xEA
#define ENABLE_SM 0XF4
#define DIS_SM 0XF5
#define ENABLE_RM 0XF0



#endif

