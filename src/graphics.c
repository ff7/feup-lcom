#include <minix/syslib.h>
#include <minix/drivers.h>
#include <machine/int86.h>
#include <sys/mman.h>
#include <sys/types.h>
#include "vbe.h"

#include "timer.h"
#include "keyboard.h"
#include "mouse.h"

#define SQUARE_MODE 0x105
#define LINE_MODE 0x105
#define XPM_MODE 0x105
#define VRAM_PHYS_ADDR	0xE0000000
#define H_RES             1024
#define V_RES		  768
#define BITS_PER_PIXEL	  8
#define BLACK 0

static char *video_mem;

static char *mouse_buffer;
static char *double_buffer;

static unsigned h_res;		/* Horizontal screen resolution in pixels */
static unsigned v_res;		/* Vertical screen resolution in pixels */
static unsigned bits_per_pixel; /* Number of VRAM bits per pixel */

int vg_exit() {
	struct reg86u reg86;

	reg86.u.b.intno = 0x10; /* BIOS video services */
	reg86.u.b.ah = 0x00;    /* Set Video Mode function */
	reg86.u.b.al = 0x03;    /* 80x25 text mode*/

	if( sys_int86(&reg86) != OK ) {
		printf("\tvg_exit(): sys_int86() failed \n");
		return 1;
	} else
		return 0;
}



void *vg_init(unsigned short mode){

	struct mem_range mr;
	int ar;
	struct reg86u r;
	r.u.w.ax = 0x4F02; // VBE call, function 02 -- set VBE mode
	r.u.w.bx = 1<<14|mode; // set bit 14: linear framebuffer
	r.u.b.intno = 0x10;
	if( sys_int86(&r) != OK ) {
		printf("set_vbe_mode: sys_int86() failed \n");
	}


	vbe_mode_info_t vmi;
	vbe_get_mode_info(mode, &vmi);

	h_res = vmi.XResolution;
	v_res = vmi.YResolution;
	bits_per_pixel = vmi.BitsPerPixel;

	mr.mr_base = vmi.PhysBasePtr;
	mr.mr_limit = mr.mr_base + (vmi.XResolution * vmi.YResolution * vmi.BitsPerPixel / 8);

	if( OK != (ar = sys_privctl(SELF, SYS_PRIV_ADD_MEM, &mr)))
		panic("vg_init: sys_privctl (ADD_MEM) failed: %d\n", r);

	/* Map memory */

	video_mem = vm_map_phys(SELF, (void *)mr.mr_base, (vmi.XResolution * vmi.YResolution * vmi.BitsPerPixel / 8));


	if(video_mem == MAP_FAILED)
	{
		if ((double_buffer = malloc(h_res * v_res * bits_per_pixel / 8)) != NULL)
		{
			if ((mouse_buffer = malloc(h_res * v_res * bits_per_pixel / 8)) != NULL)
			{
				return video_mem;
			}
		}
	}

	return video_mem;
}

//----------------------------------------------------------------------------------------------------------

int *getGraphicsBuffer()
{
	return video_mem;
}

int getHorResolution()
{
	return h_res;
}

int getVerResolution()
{
	return v_res;
}

//------------------------------------------------------------------------------------------------------------

void startGraphics()
{
	vg_init(0x117);
}

void exitGraphics()
{
	vg_exit();
}

void pixel(unsigned short x, unsigned short y, unsigned long color)
{
	if (x < 0 || x >= h_res || y < 0 || y >= v_res){

	}else
		*(video_mem + (y*h_res * (bits_per_pixel/8)) + (x*(bits_per_pixel/8))) = (char) color;

}

void pixel_mouse(unsigned short x, unsigned short y, unsigned long color)
{
	if (x < 0 || x >= h_res || y < 0 || y >= v_res){

	}else
		*(mouse_buffer + (x + y * h_res)) = (char) color;

}

void paintScreen(unsigned long color)
{
	unsigned short x;
	unsigned short y;

	for (x = 0; x < 1024 ; x++)
	{
		for(y = 0; y < 768; y++)
			pixel(x, y, color);
	}
}

int square(unsigned short x, unsigned short y, unsigned short size, unsigned long color)
{
		unsigned short xf = x + (size/2);
		unsigned short yf = y + (size/2);


		unsigned int i, j;
		for(i=0; i<size ; i++)
		{
			for(j = 0; j < size; j++){
				pixel(xf -j, yf - i, color);
			}

		}

	return 0;
}

char rgb(unsigned char r, unsigned char g, unsigned char b){
	return ((r >> 3) << 11) | ((g >> 2) << 5) | (b >> 3);
}


void vg_swap_buffer()
{
	memcpy(mouse_buffer, double_buffer, h_res * v_res * bits_per_pixel / 8);
}

void vg_swap_mouse_buffer()
{
	memcpy(video_mem, mouse_buffer, h_res * v_res * bits_per_pixel / 8);
}

