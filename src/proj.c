#include <stdio.h>
#include "keyboard.h"
#include "timer.h"
#include "graphics.h"
#include "mouse.h"
#include "Bitmap.h"
#include "MemGame.h"
#include "vbe.h"
#include "rtc.h"


static Bitmap *fundo_jogo;
static Bitmap *fundo_menu;
static Bitmap *fundo_highscores;
static Bitmap *fundo_levels;
static Bitmap *youwin;
static Bitmap *youlose;
static Bitmap *rato;
static Bitmap *congrats1;
static Bitmap *fundo_black;
static Bitmap *memorize;
static Bitmap *reproduce;
//-----------------------------------------------------------------------------------------------------
static Bitmap *A;
static Bitmap *B;
static Bitmap *C;
static Bitmap *d;
static Bitmap *E;
static Bitmap *F;
static Bitmap *G;
static Bitmap *H;
static Bitmap *I;
static Bitmap *J;
static Bitmap *K;
static Bitmap *L;
static Bitmap *M;
static Bitmap *N;
static Bitmap *O;
static Bitmap *P;
static Bitmap *Q;
static Bitmap *R;
static Bitmap *s;
static Bitmap *t;
static Bitmap *U;
static Bitmap *V;
static Bitmap *X;
static Bitmap *W;
static Bitmap *Y;
static Bitmap *Z;
//-----------------------------------------------------------------------------------------------------
static Bitmap *n1;
static Bitmap *n2;
static Bitmap *n3;
static Bitmap *n4;
static Bitmap *n5;
static Bitmap *n6;
static Bitmap *n7;
static Bitmap *n8;
static Bitmap *n9;
static Bitmap *n10;
static Bitmap *n11;
static Bitmap *n12;
static Bitmap *n13;
static Bitmap *n14;
static Bitmap *n15;
static Bitmap *n16;
static Bitmap *n17;
static Bitmap *n18;
static Bitmap *n19;
static Bitmap *n20;
static Bitmap *n21;
static Bitmap *n22;
static Bitmap *n23;
static Bitmap *n24;
static Bitmap *n25;
static Bitmap *n26;
static Bitmap *n27;
static Bitmap *n28;
static Bitmap *n29;
static Bitmap *n30;
static Bitmap *n31;
static Bitmap *n0;
static Bitmap *barra;
//-----------------------------------------------------------------------------------------------------
static Bitmap *b1;
static Bitmap *b2;
static Bitmap *b3;
static Bitmap *b4;
static Bitmap *b5;
static Bitmap *b6;
static Bitmap *b7;
static Bitmap *b8;
static Bitmap *b9;
static Bitmap *b10;
static Bitmap *b11;
static Bitmap *b12;
static Bitmap *b13;
static Bitmap *b14;
static Bitmap *b15;
static Bitmap *b16;
static Bitmap *b17;
static Bitmap *b18;
static Bitmap *b19;
static Bitmap *b20;
//-----------------------------------------------------------------------------------------------------
static Bitmap *monster1;
static Bitmap *monster2;
static Bitmap *monster3;
static Bitmap *monster4;
static Bitmap *monster5;
static Bitmap *monster6;
static Bitmap *monster7;
static Bitmap *monster8;
static Bitmap *capa;

static vbe_mode_info_t vmi;

int main(int argc, char **argv) {


    sef_startup();
    startGraphics();
    vbe_get_mode_info(0x117, &vmi);
    pos.x = vmi.XResolution/2;
    pos.y = vmi.YResolution/2;
    loadAllBitmaps();
    main_menu();
    return 0;
}

//------------------------------------------------------------------------------------------------------------------
// Bitmaps

void loadAllBitmaps()
{
	fundo_jogo = loadBitmap("home/lcom/memgame/proj/res/images/fundo_jogo.bmp");
	fundo_levels = loadBitmap("home/lcom/memgame/proj/res/images/fundo_levels.bmp");
	fundo_menu = loadBitmap("home/lcom/memgame/proj/res/images/fundo_menu.bmp");
	fundo_highscores = loadBitmap("home/lcom/memgame/proj/res/images/fundo_highscores.bmp");
	youwin = loadBitmap("home/lcom/memgame/proj/res/images/youwin.bmp");
	youlose = loadBitmap("home/lcom/memgame/proj/res/images/youlose.bmp");
	capa = loadBitmap("home/lcom/memgame/proj/res/images/Capa.bmp");
	rato = loadBitmap("home/lcom/memgame/proj/res/images/mouse.bmp");
	congrats1 = loadBitmap("home/lcom/memgame/proj/res/images/congrats1.bmp");
	fundo_black = loadBitmap("home/lcom/memgame/proj/res/images/Black_Screen.bmp");
	memorize = loadBitmap("home/lcom/memgame/proj/res/images/memorize.bmp");
	reproduce = loadBitmap("home/lcom/memgame/proj/res/images/reproduce.bmp");

	//
	Q = loadBitmap("home/lcom/memgame/proj/res/images/q.bmp");
	W = loadBitmap("home/lcom/memgame/proj/res/images/w.bmp");
	E = loadBitmap("home/lcom/memgame/proj/res/images/e.bmp");
	R = loadBitmap("home/lcom/memgame/proj/res/images/r.bmp");
	t = loadBitmap("home/lcom/memgame/proj/res/images/t.bmp");
	Y = loadBitmap("home/lcom/memgame/proj/res/images/y.bmp");
	U = loadBitmap("home/lcom/memgame/proj/res/images/u.bmp");
	I = loadBitmap("home/lcom/memgame/proj/res/images/i.bmp");
	O = loadBitmap("home/lcom/memgame/proj/res/images/o.bmp");
	P = loadBitmap("home/lcom/memgame/proj/res/images/p.bmp");
	A = loadBitmap("home/lcom/memgame/proj/res/images/a.bmp");
	s = loadBitmap("home/lcom/memgame/proj/res/images/s.bmp");
	d = loadBitmap("home/lcom/memgame/proj/res/images/d.bmp");
	F = loadBitmap("home/lcom/memgame/proj/res/images/f.bmp");
	G = loadBitmap("home/lcom/memgame/proj/res/images/g.bmp");
	H = loadBitmap("home/lcom/memgame/proj/res/images/h.bmp");
	J = loadBitmap("home/lcom/memgame/proj/res/images/j.bmp");
	K = loadBitmap("home/lcom/memgame/proj/res/images/k.bmp");
	L = loadBitmap("home/lcom/memgame/proj/res/images/l.bmp");
	Z = loadBitmap("home/lcom/memgame/proj/res/images/z.bmp");
	X = loadBitmap("home/lcom/memgame/proj/res/images/x.bmp");
	C = loadBitmap("home/lcom/memgame/proj/res/images/c.bmp");
	V = loadBitmap("home/lcom/memgame/proj/res/images/v.bmp");
	B = loadBitmap("home/lcom/memgame/proj/res/images/b.bmp");
	N = loadBitmap("home/lcom/memgame/proj/res/images/n.bmp");
	M = loadBitmap("home/lcom/memgame/proj/res/images/m.bmp");
	//
	n1 = loadBitmap("home/lcom/memgame/proj/res/images/1.bmp");
	n2 = loadBitmap("home/lcom/memgame/proj/res/images/2.bmp");
	n3 = loadBitmap("home/lcom/memgame/proj/res/images/3.bmp");
	n4 = loadBitmap("home/lcom/memgame/proj/res/images/4.bmp");
	n5 = loadBitmap("home/lcom/memgame/proj/res/images/5.bmp");
	n6 = loadBitmap("home/lcom/memgame/proj/res/images/6.bmp");
	n7 = loadBitmap("home/lcom/memgame/proj/res/images/7.bmp");
	n8 = loadBitmap("home/lcom/memgame/proj/res/images/8.bmp");
	n9 = loadBitmap("home/lcom/memgame/proj/res/images/9.bmp");
	n10 = loadBitmap("home/lcom/memgame/proj/res/images/10.bmp");
	n11 = loadBitmap("home/lcom/memgame/proj/res/images/11.bmp");
	n12 = loadBitmap("home/lcom/memgame/proj/res/images/12.bmp");
	n13 = loadBitmap("home/lcom/memgame/proj/res/images/13.bmp");
	n14 = loadBitmap("home/lcom/memgame/proj/res/images/14.bmp");
	n15 = loadBitmap("home/lcom/memgame/proj/res/images/15.bmp");
	n16 = loadBitmap("home/lcom/memgame/proj/res/images/16.bmp");
	n17 = loadBitmap("home/lcom/memgame/proj/res/images/17.bmp");
	n18 = loadBitmap("home/lcom/memgame/proj/res/images/18.bmp");
	n19 = loadBitmap("home/lcom/memgame/proj/res/images/19.bmp");
	n20 = loadBitmap("home/lcom/memgame/proj/res/images/20.bmp");
	n21 = loadBitmap("home/lcom/memgame/proj/res/images/21.bmp");
	n22 = loadBitmap("home/lcom/memgame/proj/res/images/22.bmp");
	n23 = loadBitmap("home/lcom/memgame/proj/res/images/23.bmp");
	n24 = loadBitmap("home/lcom/memgame/proj/res/images/24.bmp");
	n25 = loadBitmap("home/lcom/memgame/proj/res/images/25.bmp");
	n26 = loadBitmap("home/lcom/memgame/proj/res/images/26.bmp");
	n27 = loadBitmap("home/lcom/memgame/proj/res/images/27.bmp");
	n28 = loadBitmap("home/lcom/memgame/proj/res/images/28.bmp");
	n29 = loadBitmap("home/lcom/memgame/proj/res/images/29.bmp");
	n30 = loadBitmap("home/lcom/memgame/proj/res/images/30.bmp");
	n31 = loadBitmap("home/lcom/memgame/proj/res/images/31.bmp");
	n0 = loadBitmap("home/lcom/memgame/proj/res/images/0.bmp");
	barra = loadBitmap("home/lcom/memgame/proj/res/images/barra.bmp");
	//
	b1 = loadBitmap("home/lcom/memgame/proj/res/images/1b.bmp");
	b2 = loadBitmap("home/lcom/memgame/proj/res/images/2b.bmp");
	b3 = loadBitmap("home/lcom/memgame/proj/res/images/3b.bmp");
	b4 = loadBitmap("home/lcom/memgame/proj/res/images/4b.bmp");
	b5 = loadBitmap("home/lcom/memgame/proj/res/images/5b.bmp");
	b6 = loadBitmap("home/lcom/memgame/proj/res/images/6b.bmp");
	b7 = loadBitmap("home/lcom/memgame/proj/res/images/7b.bmp");
	b8 = loadBitmap("home/lcom/memgame/proj/res/images/8b.bmp");
	b9 = loadBitmap("home/lcom/memgame/proj/res/images/9b.bmp");
	b10 = loadBitmap("home/lcom/memgame/proj/res/images/10b.bmp");
	b11 = loadBitmap("home/lcom/memgame/proj/res/images/11b.bmp");
	b12 = loadBitmap("home/lcom/memgame/proj/res/images/12b.bmp");
	b13 = loadBitmap("home/lcom/memgame/proj/res/images/13b.bmp");
	b14 = loadBitmap("home/lcom/memgame/proj/res/images/14b.bmp");
	b15 = loadBitmap("home/lcom/memgame/proj/res/images/15b.bmp");
	b16 = loadBitmap("home/lcom/memgame/proj/res/images/16b.bmp");
	b17 = loadBitmap("home/lcom/memgame/proj/res/images/17b.bmp");
	b18 = loadBitmap("home/lcom/memgame/proj/res/images/18b.bmp");
	b19 = loadBitmap("home/lcom/memgame/proj/res/images/19b.bmp");
	b20 = loadBitmap("home/lcom/memgame/proj/res/images/20b.bmp");
	//
	monster1 = loadBitmap("home/lcom/memgame/proj/res/images/Monstro1.bmp");
	monster2 = loadBitmap("home/lcom/memgame/proj/res/images/Monstro2.bmp");
	monster3 = loadBitmap("home/lcom/memgame/proj/res/images/Monstro3.bmp");
	monster4 = loadBitmap("home/lcom/memgame/proj/res/images/Monstro4.bmp");
	monster5 = loadBitmap("home/lcom/memgame/proj/res/images/Monstro5.bmp");
	monster6 = loadBitmap("home/lcom/memgame/proj/res/images/Monstro6.bmp");
	monster7 = loadBitmap("home/lcom/memgame/proj/res/images/Monstro7.bmp");
	monster8 = loadBitmap("home/lcom/memgame/proj/res/images/Monstro8.bmp");
}

void drawCards()
{
	drawBitmap(monster1, 100, 200, ALIGN_LEFT);
	drawBitmap(monster2, 300, 200, ALIGN_LEFT);
	drawBitmap(monster3, 500, 200, ALIGN_LEFT);
	drawBitmap(monster4, 700, 200, ALIGN_LEFT);
	drawBitmap(monster5, 100, 500, ALIGN_LEFT);
	drawBitmap(monster6, 300, 500, ALIGN_LEFT);
	drawBitmap(monster7, 500, 500, ALIGN_LEFT);
	drawBitmap(monster8, 700, 500, ALIGN_LEFT);
}

void drawBack()
{
	drawBitmap(capa, 100, 200, ALIGN_LEFT);
	drawBitmap(capa, 300, 200, ALIGN_LEFT);
	drawBitmap(capa, 500, 200, ALIGN_LEFT);
	drawBitmap(capa, 700, 200, ALIGN_LEFT);
	drawBitmap(capa, 100, 500, ALIGN_LEFT);
	drawBitmap(capa, 300, 500, ALIGN_LEFT);
	drawBitmap(capa, 500, 500, ALIGN_LEFT);
	drawBitmap(capa, 700, 500, ALIGN_LEFT);
}

//--------------------------------------------------------------------------------------------------------------------
// Mouse

void out_of_bonds()
{
        if (pos.x < 0)
                pos.x = 0;
        if (pos.y < 0)
                pos.y = 0;
        if (pos.x > 1023)
                pos.x = 1023;
        if (pos.y > 767)
                pos.y = 767;
}

//-----------------------------------------------------------------------------------------------------------------------
void drawRato(int x, int y)
{
	drawBitmap/*Transparent*/(rato,x,y,ALIGN_LEFT);
}

void drawFundo()
{
	drawBitmap(fundo_jogo,0,0, ALIGN_LEFT);
}

void drawMenu()
{
	drawBitmap(fundo_menu,0,0, ALIGN_LEFT);
}

void drawHighscores()
{
	drawBitmap(fundo_highscores,0,0,ALIGN_LEFT);
}

void drawLevels()
{
	drawBitmap(fundo_levels, 0, 0, ALIGN_LEFT);
}

void drawYouWin()
{
	drawBitmap(youwin,0,0,ALIGN_LEFT);
}

void drawYouLose()
{
	drawBitmap(youlose,0,0,ALIGN_LEFT);
}

void drawCongrats()
{
	drawBitmap(congrats1,0,0,ALIGN_LEFT);
}

void drawBlack()
{
	drawBitmap(fundo_black,0, 0, ALIGN_LEFT);
}

void drawMemorize()
{
	drawBitmap(memorize,150, 100, ALIGN_LEFT);
}

void drawReproduce()
{
	drawBitmap(reproduce,40, 100, ALIGN_LEFT);
}

void drawMonstro1()
{
	drawBitmap(monster1, 100, 200, ALIGN_LEFT);
}

void drawMonstro2()
{
	drawBitmap(monster2, 300, 200, ALIGN_LEFT);
}

void drawMonstro3()
{
	drawBitmap(monster3, 500, 200, ALIGN_LEFT);
}

void drawMonstro4()
{
	drawBitmap(monster4, 700, 200, ALIGN_LEFT);
}

void drawMonstro5()
{
	drawBitmap(monster5, 100, 500, ALIGN_LEFT);
}

void drawMonstro6()
{
	drawBitmap(monster6, 300, 500, ALIGN_LEFT);
}

void drawMonstro7()
{
	drawBitmap(monster7, 500, 500, ALIGN_LEFT);
}

void drawMonstro8()
{
	drawBitmap(monster8, 700, 500, ALIGN_LEFT);
}
//
void drawCapa1()
{
	drawBitmap(capa, 100, 200, ALIGN_LEFT);
}

void drawCapa2()
{
	drawBitmap(capa, 300, 200, ALIGN_LEFT);
}

void drawCapa3()
{
	drawBitmap(capa, 500, 200, ALIGN_LEFT);
}

void drawCapa4()
{
	drawBitmap(capa, 700, 200, ALIGN_LEFT);
}

void drawCapa5()
{
	drawBitmap(capa, 100, 500, ALIGN_LEFT);
}

void drawCapa6()
{
	drawBitmap(capa, 300, 500, ALIGN_LEFT);
}

void drawCapa7()
{
	drawBitmap(capa, 500, 500, ALIGN_LEFT);
}

void drawCapa8()
{
	drawBitmap(capa, 700, 500, ALIGN_LEFT);
}


//----------------------------------------------------------------------------------------------------------------------

void drawQ(unsigned int x, unsigned int y)
{
	drawBitmap(Q, x, y, ALIGN_LEFT);
}

void drawW(unsigned int x, unsigned int y)
{
	drawBitmap(W, x, y, ALIGN_LEFT);
}

void drawE(unsigned int x, unsigned int y)
{
	drawBitmap(E, x, y, ALIGN_LEFT);
}

void drawR(unsigned int x, unsigned int y)
{
	drawBitmap(R, x, y, ALIGN_LEFT);
}

void drawT(unsigned int x, unsigned int y)
{
	drawBitmap(t, x, y, ALIGN_LEFT);
}

void drawY(unsigned int x, unsigned int y)
{
	drawBitmap(Y, x, y, ALIGN_LEFT);
}

void drawU(unsigned int x, unsigned int y)
{
	drawBitmap(U, x, y, ALIGN_LEFT);
}

void drawI(unsigned int x, unsigned int y)
{
	drawBitmap(I, x, y, ALIGN_LEFT);
}

void drawO(unsigned int x, unsigned int y)
{
	drawBitmap(O, x, y, ALIGN_LEFT);
}

void drawP(unsigned int x, unsigned int y)
{
	drawBitmap(P, x, y, ALIGN_LEFT);
}

void drawA(unsigned int x, unsigned int y)
{
	drawBitmap(A, x, y, ALIGN_LEFT);
}

void drawS(unsigned int x, unsigned int y)
{
	drawBitmap(s, x, y, ALIGN_LEFT);
}

void drawD(unsigned int x, unsigned int y)
{
	drawBitmap(d, x, y, ALIGN_LEFT);
}

void drawF(unsigned int x, unsigned int y)
{
	drawBitmap(F, x, y, ALIGN_LEFT);
}

void drawG(unsigned int x, unsigned int y)
{
	drawBitmap(G, x, y, ALIGN_LEFT);
}

void drawH(unsigned int x, unsigned int y)
{
	drawBitmap(H, x, y, ALIGN_LEFT);
}

void drawJ(unsigned int x, unsigned int y)
{
	drawBitmap(J, x, y, ALIGN_LEFT);
}

void drawK(unsigned int x, unsigned int y)
{
	drawBitmap(K, x, y, ALIGN_LEFT);
}

void drawL(unsigned int x, unsigned int y)
{
	drawBitmap(L, x, y, ALIGN_LEFT);
}

void drawZ(unsigned int x, unsigned int y)
{
	drawBitmap(Z, x, y, ALIGN_LEFT);
}

void drawX(unsigned int x, unsigned int y)
{
	drawBitmap(X, x, y, ALIGN_LEFT);
}

void drawC(unsigned int x, unsigned int y)
{
	drawBitmap(C, x, y, ALIGN_LEFT);
}

void drawV(unsigned int x, unsigned int y)
{
	drawBitmap(V, x, y, ALIGN_LEFT);
}

void drawB(unsigned int x, unsigned int y)
{
	drawBitmap(B, x, y, ALIGN_LEFT);
}

void drawN(unsigned int x, unsigned int y)
{
	drawBitmap(N, x, y, ALIGN_LEFT);
}

void drawM(unsigned int x, unsigned int y)
{
	drawBitmap(M, x, y, ALIGN_LEFT);
}

//------------------------------------------------------------------------------------------------------------

void draw1(unsigned int x, unsigned int y)
{
	drawBitmap(n1, x, y, ALIGN_LEFT);
}

void draw2(unsigned int x, unsigned int y)
{
	drawBitmap(n2, x, y, ALIGN_LEFT);
}

void draw3(unsigned int x, unsigned int y)
{
	drawBitmap(n3, x, y, ALIGN_LEFT);
}

void draw4(unsigned int x, unsigned int y)
{
	drawBitmap(n4, x, y, ALIGN_LEFT);
}

void draw5(unsigned int x, unsigned int y)
{
	drawBitmap(n5, x, y, ALIGN_LEFT);
}

void draw6(unsigned int x, unsigned int y)
{
	drawBitmap(n6, x, y, ALIGN_LEFT);
}

void draw7(unsigned int x, unsigned int y)
{
	drawBitmap(n7, x, y, ALIGN_LEFT);
}

void draw8(unsigned int x, unsigned int y)
{
	drawBitmap(n8, x, y, ALIGN_LEFT);
}

void draw9(unsigned int x, unsigned int y)
{
	drawBitmap(n9, x, y, ALIGN_LEFT);
}

void draw10(unsigned int x, unsigned int y)
{
	drawBitmap(n10, x, y, ALIGN_LEFT);
}

void draw11(unsigned int x, unsigned int y)
{
	drawBitmap(n11, x, y, ALIGN_LEFT);
}

void draw12(unsigned int x, unsigned int y)
{
	drawBitmap(n12, x, y, ALIGN_LEFT);
}

void draw13(unsigned int x, unsigned int y)
{
	drawBitmap(n13, x, y, ALIGN_LEFT);
}

void draw14(unsigned int x, unsigned int y)
{
	drawBitmap(n14, x, y, ALIGN_LEFT);
}

void draw15(unsigned int x, unsigned int y)
{
	drawBitmap(n15, x, y, ALIGN_LEFT);
}

void draw16(unsigned int x, unsigned int y)
{
	drawBitmap(n16, x, y, ALIGN_LEFT);
}

void draw17(unsigned int x, unsigned int y)
{
	drawBitmap(n17, x, y, ALIGN_LEFT);
}

void draw18(unsigned int x, unsigned int y)
{
	drawBitmap(n18, x, y, ALIGN_LEFT);
}

void draw19(unsigned int x, unsigned int y)
{
	drawBitmap(n19, x, y, ALIGN_LEFT);
}

void draw20(unsigned int x, unsigned int y)
{
	drawBitmap(n20, x, y, ALIGN_LEFT);
}

void draw21(unsigned int x, unsigned int y)
{
	drawBitmap(n21, x, y, ALIGN_LEFT);
}
void draw22(unsigned int x, unsigned int y)
{
	drawBitmap(n22, x, y, ALIGN_LEFT);
}
void draw23(unsigned int x, unsigned int y)
{
	drawBitmap(n23, x, y, ALIGN_LEFT);
}
void draw24(unsigned int x, unsigned int y)
{
	drawBitmap(n24, x, y, ALIGN_LEFT);
}
void draw25(unsigned int x, unsigned int y)
{
	drawBitmap(n25, x, y, ALIGN_LEFT);
}
void draw26(unsigned int x, unsigned int y)
{
	drawBitmap(n26, x, y, ALIGN_LEFT);
}
void draw27(unsigned int x, unsigned int y)
{
	drawBitmap(n27, x, y, ALIGN_LEFT);
}
void draw28(unsigned int x, unsigned int y)
{
	drawBitmap(n28, x, y, ALIGN_LEFT);
}
void draw29(unsigned int x, unsigned int y)
{
	drawBitmap(n29, x, y, ALIGN_LEFT);
}
void draw30(unsigned int x, unsigned int y)
{
	drawBitmap(n30, x, y, ALIGN_LEFT);
}
void draw31(unsigned int x, unsigned int y)
{
	drawBitmap(n31, x, y, ALIGN_LEFT);
}

void draw0(unsigned int x, unsigned int y)
{
	drawBitmap(n0, x, y, ALIGN_LEFT);
}

void drawBarra(unsigned int x, unsigned int y)
{
	drawBitmap(barra, x, y, ALIGN_LEFT);
}

//-----------------------------------------------------------------------------------------------------------------

void drawb1(unsigned int x, unsigned int y)
{
	drawBitmap(b1, x, y, ALIGN_LEFT);
}

void drawb2(unsigned int x, unsigned int y)
{
	drawBitmap(b2, x, y, ALIGN_LEFT);
}

void drawb3(unsigned int x, unsigned int y)
{
	drawBitmap(b3, x, y, ALIGN_LEFT);
}

void drawb4(unsigned int x, unsigned int y)
{
	drawBitmap(b4, x, y, ALIGN_LEFT);
}

void drawb5(unsigned int x, unsigned int y)
{
	drawBitmap(b5, x, y, ALIGN_LEFT);
}

void drawb6(unsigned int x, unsigned int y)
{
	drawBitmap(b6, x, y, ALIGN_LEFT);
}

void drawb7(unsigned int x, unsigned int y)
{
	drawBitmap(b7, x, y, ALIGN_LEFT);
}

void drawb8(unsigned int x, unsigned int y)
{
	drawBitmap(b8, x, y, ALIGN_LEFT);
}

void drawb9(unsigned int x, unsigned int y)
{
	drawBitmap(b9, x, y, ALIGN_LEFT);
}

void drawb10(unsigned int x, unsigned int y)
{
	drawBitmap(b10, x, y, ALIGN_LEFT);
}

void drawb11(unsigned int x, unsigned int y)
{
	drawBitmap(b11, x, y, ALIGN_LEFT);
}

void drawb12(unsigned int x, unsigned int y)
{
	drawBitmap(b12, x, y, ALIGN_LEFT);
}

void drawb13(unsigned int x, unsigned int y)
{
	drawBitmap(b13, x, y, ALIGN_LEFT);
}

void drawb14(unsigned int x, unsigned int y)
{
	drawBitmap(b14, x, y, ALIGN_LEFT);
}

void drawb15(unsigned int x, unsigned int y)
{
	drawBitmap(b15, x, y, ALIGN_LEFT);
}

void drawb16(unsigned int x, unsigned int y)
{
	drawBitmap(b16, x, y, ALIGN_LEFT);
}

void drawb17(unsigned int x, unsigned int y)
{
	drawBitmap(b17, x, y, ALIGN_LEFT);
}

void drawb18(unsigned int x, unsigned int y)
{
	drawBitmap(b18, x, y, ALIGN_LEFT);
}

void drawb19(unsigned int x, unsigned int y)
{
	drawBitmap(b19, x, y, ALIGN_LEFT);
}

void drawb20(unsigned int x, unsigned int y)
{
	drawBitmap(b20, x, y, ALIGN_LEFT);
}


