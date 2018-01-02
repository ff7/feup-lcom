#ifndef __MEMGAME_H
#define __MEMGAME_H
#include "vbe.h"



/** @defgroup MemGame MemGame
 * @{
 * Functions of Game Engine
 */

mouse_pos pos;

/**
 * @briefLoads all the bitmaps necessary for the game
 *
 */
void loadAllBitmaps();

/**
 * @brief Draws all the cards with the backs
 *
 */
void drawBack();

/**
 * @brief Draws all the cards with the monsters shown
 *
 */
void drawCards();

/**
 * @brief updates the mouse position
 *
 * @param pos position of the mouse
 */
void update_pos(mouse_pos *pos);

/**
 * @brief Checks if the mouse is inside the graphic coordinates
 */
void out_of_bonds();

/**
 * @brief paints the mouse
 *
 * @param pos position of the mouse
 */
void drawMouse(mouse_pos *pos);

void drawFundo();

/**
 * @brief Draws main menu
 */
void drawMenu();

/**
 * @brief Draws High Scores menu
 */
void drawHighscores();

/**
 * @brief Draws Levels menu
 */
void drawLevels();

/**
 * @brief Draws You Win Menu
 */
void drawYouWin();

/**
 * @brief Draws You Lose
 */
void drawYouLose();


void drawMonstro1();
void drawMonstro2();
void drawMonstro3();
void drawMonstro4();
void drawMonstro5();
void drawMonstro6();
void drawMonstro7();
void drawMonstro8();
void drawCapa1();
void drawCapa2();
void drawCapa3();
void drawCapa4();
void drawCapa5();
void drawCapa6();
void drawCapa7();
void drawCapa8();

//----------------------------------------------------------------------------------

/**
 * @brief Responsible for the main menu functionalities
 *
 * @return Returns 0
 */
int main_menu();

/**
 * @brief Responsible for the main menu functionalities after playing or checking the scores
 *
 * @return Returns 0
 */
int loop_main_menu();

/**
 * @brief Responsible for the levels menu functionalities
 *
 * @return Returns 0
 */
int menu_levels();

/**
 * @brief Responsible for the scores menu functionalities
 *
 * @return Returns 0
 */
int menu_scores();

/**
 * @brief Responsible for the level1 functionalities
 *
 * @return Returns 0
 */
int gameplay1();

/**
 * @brief Responsible for the level2 functionalities
 *
 * @return Returns 0
 */
int gameplay2();

/**
 * @brief Responsible for the level3 functionalities
 *
 * @return Returns 0
 */
int gameplay3();

/**
 * @brief Responsible for the menu where the victorious player inserts his name
 *
 * @return Returns 0
 */
int menu_name();

/**
 * @brief Responsible for the menu where the victorious player inserts his name
 *
 * @param c1 Character n1 of the name
 * @param c2 Character n2 of the name
 * @param c3 Character n3 of the name
 * @param c4 Character n4 of the name
 * @param c5 Character n5 of the name
 * @param d1 Day
 * @param m1 Month
 * @param y1 Year
 * @param coord Coordinates of the y
 */
void draw_scores(char c1, char c2, char c3, char c4, char c5,int d1, int m1, int y1,int coord);
void draw_scorez();

#endif

/**@}*/
