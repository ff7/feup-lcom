#ifndef __VIDEO_GR_H
#define __VIDEO_GR_H

/* Constants for VBE 0x105 mode */

/* The physical address may vary from VM to VM.
 * At one time it was 0xD0000000
 *  #define VRAM_PHYS_ADDR    0xD0000000
 * Currently on lab B107 is 0xF0000000
 * Better run my version of lab5 as follows:
 *     service run `pwd`/lab5 -args "mode 0x105"
 */
#define VRAM_PHYS_ADDR	0xE0000000
#define H_RES             1024 //hard coded value for horizontal resolution
#define V_RES		  768 //hard coded value for vertical resolution
#define BITS_PER_PIXEL	  8

/* Private global variables */


/** @defgroup video_gr video_gr
 * @{
 *
 * Functions for outputing data to screen in graphics mode
 */

/**
 * @brief Initializes the video module in graphics mode
 *
 * Uses the VBE INT 0x10 interface to set the desired
 *  graphics mode, maps VRAM to the process' address space and
 *  initializes static global variables with the resolution of the screen,
 *  and the number of colors
 *
 * @param mode 16-bit VBE mode to set
 * @return Virtual address VRAM was mapped to. NULL, upon failure.
 */
void *vg_init(unsigned short mode);

/**
 * @brief Returns to default Minix 3 text mode (0x03: 25 x 80, 16 colors)
 *
 * @return 0 upon success, non-zero upon failure
 */
int vg_exit(void);

/**
 * @brief Returns the graphics buffer
 *
 * @return the graphics buffer
 */
int *getGraphicsBuffer();

/**
 * @brief Returns the horizontal resolution
 *
 * @return the horizontal resolution
 */
int getHorResolution();

/**
 * @brief Returns the vertical resolution
 *
 * @return the vertical resolution
 */
int getVerResolution();

//---------------------------------------------------------------------------------------------

/**
 * @brief Fills a pixel from the position (x,y) with the color given
 *
 * @param x position of the x coordinates
 * @param y position of the y coordinates
 * @param color color
 *
 * @return Returns color code
 */
void fill_pixel(unsigned short x, unsigned short y, unsigned long color) ;

/**
 * @brief Fills a square of size size from the position (x,y) with the color given
 *
 * @param x position of the x coordinates
 * @param y position of the y coordinates
 * @param size size of the side of the square
 * @param color color
 *
 * @return Returns color code
 */
int square(unsigned short x, unsigned short y, unsigned short size,unsigned long color);

/**
 * @brief Fills the screen with the color given
 *
 * @param color color of the screen
 */
void paintScreen(unsigned long color);

/**
 * @brief Starts the graphics mode
 *
 */
void startGraphics();

/**
 * @brief Exits the graphics mode and returns to the text mode
 *
 */
void exitGraphics();

/**
 * @brief Exchande the double buffer for the mouse buffer
 *
 */
void vg_swap_buffer();

/**
 * @brief Exchande the mouse buffer for the video memory
 *
 */
void vg_swap_mouse_buffer();

/**
 * @brief Convert every component to rgb
 *
 * @param r red component
 * @param g green component
 * @param b blue component
 *
 * @return Returns color code
 */
char rgb(unsigned char r, unsigned char g, unsigned char b);

//----------------------------------------------------------------------------------------------

// Useful Colors

#define RED 4
#define BLUE 9
#define ORANGE 20
#define GREEN 26
#define YELLOW 54
#define WHITE 63
#define BLACK 0


/** @} end of graphics */

#endif /* __VIDEO_GR_H */
