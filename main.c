#include <agb_lib.h>
#include <string.h>
#include "levels.h"
#include "final.c"
#include "sprs.h"
#include "sprsdk.h"
#include "iamgod.c"
#include "titlescreen.c"
#include "music.c"
#include "wrong.c"
#include "rip.c"
int dir, newframe, px=112, py=120, level,tiley=8,tilex=6,anim,key, l3s,arpos,l4s,keys,udframe,udtemp,Phase, i, size, mus, musici, frames, rot,f1;
#define CHAR_BASE(n)		n<<2
void die();
void tstsndcmp(int s, int time);
void glidetime(int spr, int x1, int y1, int x2, int y2, int frames) {
    MoveSprite(&sprites[spr], x1, y1);
    int i, deltax, deltay, numpixels;
    int d, dinc1, dinc2;
    int x, xinc1, xinc2;
    int y, yinc1, yinc2;
    //calculate deltaX and deltaY
    deltax = abs(x2 - x1);
    deltay = abs(y2 - y1);
    //initialize
    if (deltax >= deltay) {
        //If x is independent variable
        numpixels = deltax + 1;
        d = (2 * deltay) - deltax;
        dinc1 = deltay << 1;
        dinc2 = (deltay - deltax) << 1;
        xinc1 = 1;
        xinc2 = 1;
        yinc1 = 0;
        yinc2 = 1;
    } else {
        //if y is independent variable
        numpixels = deltay + 1;
        d = (2 * deltax) - deltay;
        dinc1 = deltax << 1;
        dinc2 = (deltax - deltay) << 1;
        xinc1 = 0;
        xinc2 = 1;
        yinc1 = 1;
        yinc2 = 1;
    }
    //move the right direction
    if (x1 > x2) {
        xinc1 = -xinc1;
        xinc2 = -xinc2;
    }
    if (y1 > y2) {
        yinc1 = -yinc1;
        yinc2 = -yinc2;
    }
    x = x1;
    y = y1;
    //draw the pixels
    for (i = 1; i < numpixels; i++) {
        vsync
        tstsndcmp(1, sound[1].end);
        CopyOAM();
        MoveSprite(&sprites[spr], x, y);
        if (d < 0) {
            d = d + dinc1;
            x = x + xinc1;
            y = y + yinc1;
        } else {
            d = d + dinc2;
            x = x + xinc2;
            y = y + yinc2;
        }
    }
}
void playSound(int s) {
    REG_SOUNDCNT1_H = 0x0B0F;                                                       //REG_SOUNDCNT_H = 0000 1011 0000 0100, volume = 100, sound goes to the left, sound goes to the right, timer 0 is used, FIFO buffer reset
    REG_SOUNDCNT1_X = 0x0080;                                                       //REG_SOUNDCNT_X = 0000 0000 1000 0000, enable the sound system, DMA 1
    REG_SD1SAD = (unsigned long)sound[s].song;                                //REG_DM1SAD = NAME, address of DMA source is the digitized music sample
    REG_SD1DAD = 0x040000A0;                                                   //REG_DM1DAD = REG_SGFIFOA, address of DMA destination is FIFO buffer for direct sound A
    REG_SD1CNT_H = 0xB640;                                                       //REG_DM1CNT_H = 1011 0110 0100 0000, DMA destination is fixed, repeat transfer of 4 bytes when FIFO , buffer is empty, enable DMA 1 (number of DMA transfers is ignored), INTERRUPT
    REG_TM0SD = 65536 - (16777216 / sound[s].frequency);                          //REG_TM0D = 65536-(16777216/frequency);, play sample every 16777216/frequency CPU cycles
    REG_TMSDCNT = 0x00C0;
}

void tstsndcmp(int s, int time) {
    if (musici >= time) {
        REG_SOUNDCNT_H = 0;                                                      //REG_SOUNDCNT_H = 0000 1011 0000 0100, volume = 100, sound goes to the left, sound goes to the right, timer 0 is used, FIFO buffer reset
        REG_SOUNDCNT_X = 0;                                                       //REG_SOUNDCNT_X = 0000 0000 1000 0000, enable the sound system, DMA 1
        REG_DM1SAD = 0;                               //REG_DM1SAD = NAME, address of DMA source is the digitized music sample
        REG_DM1DAD = 0;                                                   //REG_DM1DAD = REG_SGFIFOA, address of DMA destination is FIFO buffer for direct sound A
        REG_DM1CNT_H = 0;                                                    //REG_DM1CNT_H = 1011 0110 0100 0000, DMA destination is fixed, repeat transfer of 4 bytes when FIFO , buffer is empty, enable DMA 1 (number of DMA transfers is ignored), INTERRUPT
        REG_TM0D = 0;                         //REG_TM0D = 65536-(16777216/frequency);, play sample every 16777216/frequency CPU cycles
        REG_TM0CNT = 0;
        playSound(s);
        musici = 0;
    } else {
        musici++;
    }
}

void end() {
    FadeOut(3);
    offsetOAM = 0;
    loadSpritePal((void*)sprsPalette);
    loadSpriteGraphics((void*)sprs, 2048);
    REG_SOUNDCNT_H = 0;                                                      //REG_SOUNDCNT_H = 0000 1011 0000 0100, volume = 100, sound goes to the left, sound goes to the right, timer 0 is used, FIFO buffer reset
    REG_SOUNDCNT_X = 0;                                                       //REG_SOUNDCNT_X = 0000 0000 1000 0000, enable the sound system, DMA 1
    REG_DM1SAD = 0;                               //REG_DM1SAD = NAME, address of DMA source is the digitized music sample
    REG_DM1DAD = 0;                                                   //REG_DM1DAD = REG_SGFIFOA, address of DMA destination is FIFO buffer for direct sound A
    REG_DM1CNT_H = 0;                                                    //REG_DM1CNT_H = 1011 0110 0100 0000, DMA destination is fixed, repeat transfer of 4 bytes when FIFO , buffer is empty, enable DMA 1 (number of DMA transfers is ignored), INTERRUPT
    REG_TM0D = 0;                         //REG_TM0D = 65536-(16777216/frequency);, play sample every 16777216/frequency CPU cycles
    REG_TM0CNT = 0;
    memcpy(videoBuffer, endBitmap, 76800);
    px = 112, py = 136;
    MoveSprite(&sprites[0], px, py);
    sprites[0].attribute1 = SIZE_16 | px;
    updateSprite(0, 16, 0, 0);
    RotateSprite(1, 0, 256, 256);
    CopyOAM();
    FadeIn(3);
    for (i = 0; i < 64; i++) {
        dir = 1;
        if ((py == 8)OR(GetPixel3(px, py - 1) == 0x0000)) {
            tiley++;
            break;
        }
        if ((level == 6)AND(tilex == 9)AND(tiley == 6)AND(l4s == 0)) {
            tiley++;
            break;
        }
        vsync
        udframe++;
        if (!(udframe % 8)) {
            anim++;
            if (anim >= 4) {
                anim = 0;
            }
        }
        if (anim == 0) {
            sprites[0].attribute1 = SIZE_16 | px;
            updateSprite(0, 16, 0, 0);
        } else if (anim == 1) {
            sprites[0].attribute1 = SIZE_16 | px;
            updateSprite(0, 24, 0, 0);
        } else if (anim == 2) {
            sprites[0].attribute1 = SIZE_16 | px;
            updateSprite(0, 16, 0, 0);
        } else {
            sprites[0].attribute1 = SIZE_16 | HORIZONTAL_FLIP | px;
            updateSprite(0, 24, 0, 0);
        }
        py--;
        MoveSprite(&sprites[0], px, py);
        CopyOAM();
        dir = 1;
    }
    i = 60;
    while (i--) {
        WaitForVblank();
    }
    glideSpritetoPos(1, 128 + 16, -8, 102, 24, 2.00);
    i = 60;
    while (i--) {
        WaitForVblank();
    }
    SetMode(MODE_3 | BG2_ENABLE);
    memcpy(videoBuffer, finalBitmap, 76800);
    while (!(keyDown(KEY_A)));
    FadeOutWhite(8);
    fillscreen3(0xFFFF);
    FadeInWhite(0);
    fillscreen3(0xFFFF);
    Print(0, 0, "WHEN THE CHILD GOT OUT", BLUE,WHITE);
    Print(0, 9, "THE BUILDING HAD", BLUE, WHITE);
	Print(0, 18, "DISAPPEARED.", BLUE, WHITE);
    while (!(keyDown(KEY_A)));
    while (keyDown(KEY_A));
    fillscreen3(0xFFFF);
    Print(0, 0, "NOBODY WILL EVER KNOW", BLUE, WHITE);
    Print(0, 9, "WHAT EXACTLY HAPPENED", BLUE, WHITE);
    Print(0, 18, "TO THE PEOPLE WHO", BLUE, WHITE);
    Print(0, 27, "WALKED INTO THAT", BLUE, WHITE);
    Print(0, 36, "BUILDING.", BLUE, WHITE);
    while (!(keyDown(KEY_A)));
    while (keyDown(KEY_A));
    fillscreen3(0xFFFF);
    Print(0, 0, "ON THE BRIGHT SIDE, THE", BLUE, WHITE);
    Print(0, 9, "CHILD HAD PUT THE ANGRY", BLUE, WHITE);
    Print(0, 18, "SPIRITS HAUNTING THE", BLUE, WHITE);
    Print(0, 27, "DESERT TO REST, AND", BLUE, WHITE);
	Print(0, 36, "RESTORED PEACE TO THE ", BLUE, WHITE);
    Print(0, 45, "WORLD.", BLUE, WHITE);
    while (!(keyDown(KEY_A)));
    while (keyDown(KEY_A));
    fillscreen3(0xFFFF);
    Print(0, 0, "THE END.", BLUE, WHITE);
    while (!(keyDown(KEY_A)));
    FadeOutWhite(8);
	asm("swi 0x01"::);
    asm("swi 0x26"::);
}
int main() {
    int s;
    REG_BLDMOD = 0x00D6;
    WaitForVblank();
    fillpal("bg", 0xFFFF);
    SetMode(MODE_4 | BG2_ENABLE);
    REG_BG2CNT = BG_MOSAIC_ENABLE;
    Sleep(25);
    initsound8(1, 22050, 416, (void*)music);
    initsound8(2, 22050, 208, (void*)rip+12);
    MoveSprite(&sprites[0], 240, 160);
    MoveSprite(&sprites[1], 240, 160);
    CopyOAM();
    level = 0;
    frames = 0;
    FadeOut(3);
    SetMode(MODE_4 | BG2_ENABLE | OBJ_ENABLE | OBJ_MAP_1D);
    SetPalette((void*)titlescreenPalette);
    memcpy(videoBuffer, titlescreenBitmap, 38400);
    FadeIn(8);
    Sleep(30);
    loadSpritePal((void*)sprsPalette);
    loadSpriteGraphics((void*)sprs,2048);
    initSprite(2, SIZE_8, 88);
    MoveSprite(&sprites[2], 0, 57);
    CopyOAM();
    sprites[32].attribute0 = COLOR_256 | WIDE | 160;
    sprites[32].attribute1 = SIZE_64 | 240;
    sprites[32].attribute2 = 512 + 112; // NOTE: mode4 doesn't support the first tiles, so offset of 512 is requirerd
    MoveSprite(&sprites[32], 192, 152);
    playSound(2);
    level = LoadInt(0);
    if (!(level == 0)) {
        arpos = 1;
    }
    while (!(keyDown(KEY_A))) {
        WaitForVblank();
        if (frames >= 208) {
            REG_SOUNDCNT_H = 0;                                                      //REG_SOUNDCNT_H = 0000 1011 0000 0100, volume = 100, sound goes to the left, sound goes to the right, timer 0 is used, FIFO buffer reset
            REG_SOUNDCNT_X = 0;                                                       //REG_SOUNDCNT_X = 0000 0000 1000 0000, enable the sound system, DMA 1
            REG_DM1SAD = 0;                               //REG_DM1SAD = NAME, address of DMA source is the digitized music sample
            REG_DM1DAD = 0;                                                   //REG_DM1DAD = REG_SGFIFOA, address of DMA destination is FIFO buffer for direct sound A
            REG_DM1CNT_H = 0;                                                    //REG_DM1CNT_H = 1011 0110 0100 0000, DMA destination is fixed, repeat transfer of 4 bytes when FIFO , buffer is empty, enable DMA 1 (number of DMA transfers is ignored), INTERRUPT
            REG_TM0D = 0;                         //REG_TM0D = 65536-(16777216/frequency);, play sample every 16777216/frequency CPU cycles
            REG_TM0CNT = 0;
            playSound(2);
            frames = 0;
        } else {
            frames++;
        }
        if (keyDown(KEY_UP)) {
            arpos = 0;
        }
        if (keyDown(KEY_DOWN)) {
            arpos = 1;
        }
        if (arpos == 0) {
            MoveSprite(&sprites[2], 0, 57);
        }
        if (arpos == 1) {
            MoveSprite(&sprites[2], 0, 70);
        }
        CopyOAM();
        level = LoadInt(0);
    }
    REG_SOUNDCNT_H = 0;                                                      //REG_SOUNDCNT_H = 0000 1011 0000 0100, volume = 100, sound goes to the left, sound goes to the right, timer 0 is used, FIFO buffer reset
    REG_SOUNDCNT_X = 0;                                                       //REG_SOUNDCNT_X = 0000 0000 1000 0000, enable the sound system, DMA 1
    REG_DM1SAD = 0;                               //REG_DM1SAD = NAME, address of DMA source is the digitized music sample
    REG_DM1DAD = 0;                                                   //REG_DM1DAD = REG_SGFIFOA, address of DMA destination is FIFO buffer for direct sound A
    REG_DM1CNT_H = 0;                                                    //REG_DM1CNT_H = 1011 0110 0100 0000, DMA destination is fixed, repeat transfer of 4 bytes when FIFO , buffer is empty, enable DMA 1 (number of DMA transfers is ignored), INTERRUPT
    REG_TM0D = 0;                         //REG_TM0D = 65536-(16777216/frequency);, play sample every 16777216/frequency CPU cycles
    REG_TM0CNT = 0;
    REG_BLDMOD = 0x00D6;
    FadeOut(8);
    initSprite(0, SIZE_16, 0);
    initSprite(2, SIZE_16, 64);
    MoveSprite(&sprites[0], 112, 120);
    sprites[1].attribute0 = COLOR_256 | TALL | ROTATION_FLAG | SIZE_DOUBLE | 160;
    sprites[1].attribute1 = SIZE_32 | ROTDATA(1) | 240;
    sprites[1].attribute2 = 512 + 48; // NOTE: mode4 doesn't support the first tiles, so offset of 512 is requirerd
    RotateSprite(1, 0, 256, 256);
    if (arpos == 1) {
        if (level == 40) {
            initSprite(2, SIZE_16, 64);
            MoveSprite(&sprites[2], 152, 121);
            memcpy(videoBuffer, l4Bitmap, 76800);
            initSprite(2, SIZE_16, 64);
            tilex = 6, tiley = 5;
            px = 120, py = 72;
            sprites[0].attribute1 = SIZE_16 | px;
            updateSprite(0, 16, 0, 0);
            MoveSprite(&sprites[0], px, py);
            level = 4;
            MoveSprite(&sprites[2], 152, 121);
            CopyOAM();
        }
        if (level == 80) {
            MoveSprite(&sprites[2], 152, 121);
            memcpy(videoBuffer, l8Bitmap, 76800);
            tilex = 5, tiley = 9;
            initSprite(2, SIZE_16, 64);
            px = 104, py = 136;
            sprites[0].attribute1 = SIZE_16 | px;
            updateSprite(0, 16, 0, 0);
            level = 8;
            l4s = 0;
            MoveSprite(&sprites[0], px, py);
            RotateSprite(1, 0, 256, 256);
            CopyOAM();
        }
        if (level == 17) {
            tilex = 6, tiley = 7;
            px = 120, py = 104;
            dir = 0;
            level = 17;
            memcpy(videoBuffer, l17Bitmap, 76800);
            sprites[0].attribute1 = SIZE_16 | px;
            updateSprite(0, 16, 0, 0);
            MoveSprite(&sprites[0], px, py);
            RotateSprite(1, 0, 256, 256);
            CopyOAM();
        }
		if (level == 27) {
			tilex = 5, tiley = 9;
			px = 104, py = 136;
			dir = 0;
			level = 27;
			memcpy(videoBuffer, l27Bitmap, 76800);
			sprites[0].attribute1 = SIZE_16 | px;
			updateSprite(0, 16, 0, 0);
			MoveSprite(&sprites[0], px, py);
			RotateSprite(1, 0, 256, 256);
			CopyOAM();
		}
		if (level == 30) {
			tilex = 5, tiley = 9;
			px = 104, py = 136;
			dir = 0;
			level = 30;
			memcpy(videoBuffer, l30Bitmap, 76800);
			sprites[0].attribute1 = SIZE_16 | px;
			updateSprite(0, 16, 0, 0);
			MoveSprite(&sprites[0], px, py);
			RotateSprite(1, 0, 256, 256);
			CopyOAM();
		}
    } else {
        SetMode(MODE_3 | BG2_ENABLE);
        fillscreen3(0x7c00);
        FadeIn(0);
        fillscreen3(0x7c00);
        Print(0, 0, "THERE IS A TEMPLE HIDDEN", WHITE, BLUE);
        Print(0, 9, "WITHIN THE DESERT.", WHITE, BLUE);
		while (!(keyDown(KEY_A)));
		while (keyDown(KEY_A));
		fillscreen3(0x7c00);
		Print(0, 0, "IT IS SAID TO HAVE BEEN", WHITE, BLUE);
		Print(0, 9, "USED AS A FORM OF SHELTER,", WHITE, BLUE);
		Print(0, 18, "FOR RELIGIOUS PURPOSES.", WHITE, BLUE);
		while (!(keyDown(KEY_A)));
		while (keyDown(KEY_A));
		fillscreen3(0x7c00);
		Print(0, 0, "ONE DAY, A MAN PERFORMED", WHITE, BLUE);
		Print(0, 9, "A DEMONIC RITUAL, CAUING", WHITE, BLUE);
		Print(0, 18, "HIM TO BECOME INSANE", WHITE, BLUE);
		Print(0, 27, "AND COMMIT A MURDER IN THE", WHITE, BLUE);
		Print(0, 36, "BUILDING.", WHITE, BLUE);
		while (!(keyDown(KEY_A)));
		while (keyDown(KEY_A));
		fillscreen3(0x7c00);
		Print(0, 0, "THE TEMPLE HAD TO BE", WHITE, BLUE);
		Print(0, 9, "ABANDONED, AND IT WAS", WHITE, BLUE);
		Print(0, 18, "RUMORED TO BE EXTREMELY", WHITE, BLUE);
		Print(0, 27, "HAUNTED BY THE VICTIM.", WHITE, BLUE);
		while (!(keyDown(KEY_A)));
		while (keyDown(KEY_A));
		fillscreen3(0x7c00);
		Print(0, 0, "MANY YEARS LATER...", WHITE, BLUE);
		while (!(keyDown(KEY_A)));
		while (keyDown(KEY_A));
		fillscreen3(0x7c00);
		Print(0, 0, "LEGEND HAS IT THAT ANYBODY", WHITE, BLUE);
		Print(0, 9, "WHO ENTERS THIS TEMPLE NEVER", WHITE, BLUE);
		Print(0, 18, "RETURN, AND ARE PRESUMED DEAD.", WHITE, BLUE);
        while (!(keyDown(KEY_A)));
        while (keyDown(KEY_A));
        fillscreen3(0x7c00);
        Print(0, 0, "ONE DAY, A BOY GOT LOST IN", WHITE, BLUE);
        Print(0, 9, "THE DESERT, SO HE", WHITE, BLUE);
        Print(0, 18, "WALKED UNTIL HE FOUND", WHITE, BLUE);
        Print(0, 27, "THIS ANCIENT BUILDING...", WHITE, BLUE);
        while (!(keyDown(KEY_A)));
        while (keyDown(KEY_A));
        FadeOut(8);
        REG_BLDMOD = 0x00D6;
        memcpy(videoBuffer, l0Bitmap, 76800);
        level = 0;
    }
    CopyOAM();
    SetMode(MODE_3 | BG2_ENABLE | OBJ_MAP_1D | OBJ_ENABLE);
    FadeIn(8);
    musici = 420;
    while (1) {
        if (level == 0) {
            REG_SOUNDCNT_H = 0;                                                      //REG_SOUNDCNT_H = 0000 1011 0000 0100, volume = 100, sound goes to the left, sound goes to the right, timer 0 is used, FIFO buffer reset
            REG_SOUNDCNT_X = 0;                                                       //REG_SOUNDCNT_X = 0000 0000 1000 0000, enable the sound system, DMA 1
            REG_DM1SAD = 0;                               //REG_DM1SAD = NAME, address of DMA source is the digitized music sample
            REG_DM1DAD = 0;                                                   //REG_DM1DAD = REG_SGFIFOA, address of DMA destination is FIFO buffer for direct sound A
            REG_DM1CNT_H = 0;                                                    //REG_DM1CNT_H = 1011 0110 0100 0000, DMA destination is fixed, repeat transfer of 4 bytes when FIFO , buffer is empty, enable DMA 1 (number of DMA transfers is ignored), INTERRUPT
            REG_TM0D = 0;                         //REG_TM0D = 65536-(16777216/frequency);, play sample every 16777216/frequency CPU cycles
            REG_TM0CNT = 0;
            musici = 0;
        }
        WaitForVblank();
        if(level>0) {
            tstsndcmp(1, sound[1].end);
        }
        if (level == 0) {
			if (py > 135)
			{
				SetMode(MODE_3 | BG2_ENABLE);
				memcpy(videoBuffer, wrongBitmap, 76800);
				while (!(keyDown(KEY_A)));
				asm("swi 0x26"::);
			}
            if ((tiley < 2)AND(tilex == 6)) {
                u32 temp = frames;
                s8 Phase;
                REG_BLDMOD = 0x00F7;
                for (Phase = 0; Phase < 17; Phase++) {
                    i=2;
                    REG_COLEY = Phase;
                    while (i--) {
                        WaitForVblank();
                    }
                }
                level++;
                memcpy(videoBuffer, l1Bitmap, 76800);
                px = 112, py = 136;
                MoveSprite(&sprites[0], px, py);
                CopyOAM();
                playSound(1);
                for (Phase = 0; Phase < 17; Phase++) {
                    i = 2;
                    REG_COLEY = 16-Phase;
                    while (i--) {
                        WaitForVblank();
                        tstsndcmp(1, sound[1].end);
                    }
                }
                tiley--;
                sprites[0].attribute1 = SIZE_16 | px;
                updateSprite(0, 16, 0, 0);
                frames = 0;
                for (i = 0; i < 64; i++) {
                    dir = 1;
                    if ((py == 8)OR(GetPixel3(px, py - 1) == 0x0000)) {
                        tiley++;
                        break;
                    }
                    if ((level == 6)AND(tilex == 9)AND(tiley == 6)AND(l4s == 0)) {
                        tiley++;
                        break;
                    }
                    vsync
                    tstsndcmp(1, sound[1].end);
                    udframe++;
                    if (!(udframe % 8)) {
                        anim++;
                        if (anim >= 4) {
                            anim = 0;
                        }
                    }
                    if (anim == 0) {
                        sprites[0].attribute1 = SIZE_16 | px;
                        updateSprite(0, 16, 0, 0);
                    } else if (anim == 1) {
                        sprites[0].attribute1 = SIZE_16 | px;
                        updateSprite(0, 24, 0, 0);
                    } else if (anim == 2) {
                        sprites[0].attribute1 = SIZE_16 | px;
                        updateSprite(0, 16, 0, 0);
                    } else {
                        sprites[0].attribute1 = SIZE_16 | HORIZONTAL_FLIP | px;
                        updateSprite(0, 24, 0, 0);
                    }
                    py--;
                    MoveSprite(&sprites[0], px, py);
                    CopyOAM();
                    dir = 1;
                }
                i = 60;
                while (i--) {
                    WaitForVblank();
                    tstsndcmp(1, sound[1].end);
                }
                glidetime(1, 128 + 16, -8, 102, 24, 2);
                i = 60;
                while (i--) {
                    WaitForVblank();
                    tstsndcmp(1, sound[1].end);
                }
                level = 1;
                memcpy(videoBuffer, l1bBitmap, 76800);
                while (!(keyDown(KEY_A))) {
                    WaitForVblank();
                    tstsndcmp(1, sound[1].end);
                }
                while (keyDown(KEY_A)) {
                    WaitForVblank();
                    tstsndcmp(1, sound[1].end);
                }
                memcpy(videoBuffer, l1cBitmap, 76800);
                while (!(keyDown(KEY_A))) {
                    WaitForVblank();
                    tstsndcmp(1, sound[1].end);
                }
                while (keyDown(KEY_A)) {
                    WaitForVblank();
                    tstsndcmp(1, sound[1].end);
                }
                for (Phase = 0; Phase < 17; Phase++) {
                    i = 2;
                    REG_COLEY = Phase;
                    while (i--) {
                        WaitForVblank();
                        tstsndcmp(1, sound[1].end);
                    }
                }
                px = 104, py = 8;
                MoveSprite(&sprites[1], 240, 160);
                MoveSprite(&sprites[0], px, py);
                memcpy(videoBuffer, l2Bitmap, 76800);
                sprites[0].attribute1 = SIZE_16 | px;
                updateSprite(0, 32, 0, 0);
                tilex = 5, tiley = 1;
                dir = 2;
                CopyOAM();
                memcpy(videoBuffer, l2Bitmap, 76800);
                for (Phase = 0; Phase < 17; Phase++) {
                    i = 2;
                    REG_COLEY = 16-Phase;
                    while (i--) {
                        WaitForVblank();
                        tstsndcmp(1, sound[1].end);
                    }
                }
                i = 60;
                while (i--) {
                    WaitForVblank();
                    tstsndcmp(1, sound[1].end);
                }
                memcpy(videoBuffer, l2bBitmap, 76800);
                while (!(keyDown(KEY_A))) {
                    WaitForVblank();
                    tstsndcmp(1, sound[1].end);
                }
                while (keyDown(KEY_A)) {
                    WaitForVblank();
                    tstsndcmp(1, sound[1].end);
                }
                memcpy(videoBuffer, l2Bitmap, 76800);
                level = 2;
            }
        } else if (level == 2) {
            if ((tilex == 3)AND(tiley == 2)) {
                die();
                return 0;

            }
            if ((tilex == 8)AND(tiley == 2)) {
                for (Phase = 0; Phase < 17; Phase++) {
                    i = 2;
                    REG_COLEY = Phase;
                    while (i--) {
                        WaitForVblank();
                        tstsndcmp(1, sound[1].end);
                    }
                }
                tilex = 1, tiley = 5;
                px = 40, py = 72;
                initSprite(2, SIZE_16, 104);
                MoveSprite(&sprites[2], 184, 56);
                dir = 0;
                memcpy(videoBuffer, l3Bitmap, 76800);
                DrawLine3(120, 104, 135, 104, 0x0000);
                sprites[0].attribute1 = SIZE_16 | px;
                updateSprite(0, 0, 0, 0);
                MoveSprite(&sprites[0], px, py);
                CopyOAM();
                for (Phase = 0; Phase < 17; Phase++) {
                    i = 2;
                    REG_COLEY = 16-Phase;
                    while (i--) {
                        WaitForVblank();
                        tstsndcmp(1, sound[1].end);
                    }
                }
                level++;
            }
            if ((tilex == 8)AND(tiley == 5)) {
                die();
                return 0;
            }
            if ((tilex == 3)AND(tiley == 5)) {
                die();
                return 0;

            }
        } else if (level == 3) {
            if ((tilex == 10)AND(tiley == 4)) {
                key = 1;
                MoveSprite(&sprites[2], 240, 160);
            }
            if ((tilex == 1)AND(tiley == 7)) {
                if ((keyDown(KEY_A))AND(l3s == 0)) {
                    while (keyDown(KEY_A)) {
                        WaitForVblank();
                        tstsndcmp(1, sound[1].end);
                    }
                    MoveSprite(&sprites[0], 240, 160);
                    CopyOAM();
                    memcpy(videoBuffer, l3bBitmap, 76800);
                    while (!(keyDown(KEY_A))) {
                        WaitForVblank();
                        tstsndcmp(1, sound[1].end);
                    }

                    memcpy(videoBuffer, l3cBitmap, 76800);
                    DrawLine3(120, 104, 135, 104, 0x0000);
                    l3s = 1;
                }
            }
            if ((key == 1)AND(keys==0)) {
                memcpy(videoBuffer, l3cBitmap, 76800);
                keys = 1;
            }
            if ((tilex == 9)AND(tiley == 8)) {
                die();
                return 0;
            }
            if ((tilex == 3)AND(tiley == 8)) {
                for (Phase = 0; Phase < 17; Phase++) {
                    i = 2;
                    REG_COLEY = Phase;
                    while (i--) {
                        WaitForVblank();
                        tstsndcmp(1, sound[1].end);
                    }
                }
                tilex = 6, tiley = 5;
                px = 120, py = 72;
                dir = 3;
                MoveSprite(&sprites[0], px, py);
                CopyOAM();
                level++;
                memcpy(videoBuffer, l4Bitmap, 76800);
                for (Phase = 0; Phase < 17; Phase++) {
                    i = 2;
                    REG_COLEY = 16 - Phase;
                    while (i--) {
                        WaitForVblank();
                        tstsndcmp(1, sound[1].end);
                    }
                }
                i = 60;
                while (i--) {
                    WaitForVblank();
                    tstsndcmp(1, sound[1].end);
                }
                glidetime(1, 128 + 16, -8, 63, 50, 2);
                i = 5;
                while (i--) {
                    WaitForVblank();
                    tstsndcmp(1, sound[1].end);
                }
                updateSprite(1, 72, 0, 0);
                CopyOAM();
                i = 30;
                while (i--) {
                    WaitForVblank();
                    tstsndcmp(1, sound[1].end);
                }
                memcpy(videoBuffer, l4bBitmap, 76800);
                i = 25;
                while (i--) {
                    WaitForVblank();
                    tstsndcmp(1, sound[1].end);
                }
                sprites[2].attribute0 = COLOR_256 | SQUARE | 160;
                sprites[2].attribute1 = SIZE_8 | 240;
                sprites[2].attribute2 = 512 + 88;
                while (!(keyDown(KEY_A))) {
                    WaitForVblank();
                    tstsndcmp(1, sound[1].end);
                    if (keyDown(KEY_LEFT)) {
                        arpos = 0;
                    }
                    if (keyDown(KEY_RIGHT)) {
                        arpos = 1;
                    }
                    if (arpos == 0) {
                        MoveSprite(&sprites[2], 76, 136);
                    } else {
                        MoveSprite(&sprites[2], 128, 136);
                    }
                    CopyOAM();
                }
                if (arpos == 0) {
                    SaveInt(0, level*10);
                }
                memcpy(videoBuffer, l4Bitmap, 76800);
                initSprite(2, SIZE_16, 64);
                MoveSprite(&sprites[2], 152, 121);
                rot = 0;
                for (i = 256; i < 1764; i+=15) {
                    rot+=15;
                    WaitForVblank();
                    tstsndcmp(1, sound[1].end);
                    RotateSprite(1, rot, i, i);
                    CopyOAM();
                }
                MoveSprite(&sprites[1], 240, 160);
            }
        } else if (level == 4) {
            if ((tilex == 7)AND(tiley == 8)AND(keyDown(KEY_A))AND(l4s == 0)) {
                glidetime(2, 152, 121, 169, 121, 2);
                DrawLine3(169, 121, 169, 137, 0x0000);
                l4s = 1;
            }
            if ((tilex == 8)AND(tiley == 7)) {
                for (Phase = 0; Phase < 17; Phase++) {
                    REG_COLEY = Phase;
                    i = 2;
                    while (i--) {
                        WaitForVblank();
                        tstsndcmp(1, sound[1].end);
                    }
                }
                MoveSprite(&sprites[2], 240, 160);
                memcpy(videoBuffer, l5Bitmap, 76800);
                tilex = 1, tiley = 6;
                px = 40, py = 88;
                dir = 0;
                updateSprite(0, 0, 0, 0);
                level++;
                MoveSprite(&sprites[0], px, py);
                CopyOAM();
                for (Phase = 0; Phase < 17; Phase++) {
                    i = 2;
                    REG_COLEY = 16-Phase;
                    while (i--) {
                        WaitForVblank();
                        tstsndcmp(1, sound[1].end);
                    }
                }
            }
            if ((tilex == 6)AND(tiley == 1)) {
                die();
                return 0;
            }
        } else if (level == 5) {
            if ((tilex == 5)AND(tiley == 3)AND(keyDown(KEY_A))) {
                while (keyDown(KEY_A)) {
                    WaitForVblank();
                    tstsndcmp(1, sound[1].end);
                }
                CopyOAM();
                memcpy(videoBuffer, l5bBitmap, 76800);
                while (!(keyDown(KEY_A))) {
                    WaitForVblank();
                    tstsndcmp(1, sound[1].end);
                }
                memcpy(videoBuffer, l5Bitmap, 76800);
                while (keyDown(KEY_A)) {
                    WaitForVblank();
                    tstsndcmp(1, sound[1].end);
                }
            }
            if ((tilex == 10)AND(tiley == 3)) {
                for (Phase = 0; Phase < 17; Phase++) {
                    i = 2;
                    REG_COLEY = Phase;
                    while (i--) {
                        WaitForVblank();
                        tstsndcmp(1, sound[1].end);
                    }
                }
                memcpy(videoBuffer, l6Bitmap, 76800);
                initSprite(2, SIZE_16, 96);
                MoveSprite(&sprites[2], 168, 72);
                tilex = 1, tiley = 5;
                px = 40, py = 72;
                dir = 0;
                updateSprite(0, 0, 0, 0);
                level++;
                l4s = 0;
                DrawLine3(168, 87, 184, 87, 0x0000);
                MoveSprite(&sprites[0], px, py);
                CopyOAM();
                for (Phase = 0; Phase < 17; Phase++) {
                    i = 2;
                    REG_COLEY = 16 - Phase;
                    while (i--) {
                        WaitForVblank();
                        tstsndcmp(1, sound[1].end);
                    }
                }
            }
        } else if (level == 6) {
            if ((tilex == 9)AND(tiley == 6)AND(keyDown(KEY_A))AND(l4s == 0)) {
                memcpy(videoBuffer, l6Bitmap, 76800);
                glidetime(2, 168, 72, 168, 55, 2);
                DrawLine3(168, 55, 184, 55, 0x0000);
                l4s = 1;
            }
            if ((tilex == 10)AND(tiley == 5)) {
                for (Phase = 0; Phase < 17; Phase++) {
                    i = 2;
                    REG_COLEY = Phase;
                    while (i--) {
                        WaitForVblank();
                        tstsndcmp(1, sound[1].end);
                    }
                }
                memcpy(videoBuffer, l7Bitmap, 76800);
                tilex = 6, tiley = 9;
                px = 120, py = 136;
                dir = 0;
                updateSprite(0, 0, 0, 0);
                level++;
                l4s = 0;
                MoveSprite(&sprites[0], px, py);
                CopyOAM();
                for (Phase = 0; Phase < 17; Phase++) {
                    i = 2;
                    REG_COLEY = 16 - Phase;
                    while (i--) {
                        WaitForVblank();
                        tstsndcmp(1, sound[1].end);
                    }
                }
            }
        } else if (level == 7) {
            if ((tilex == 5)AND(tiley == 3)) {
                for (Phase = 0; Phase < 17; Phase++) {
                    i = 2;
                    REG_COLEY = Phase;
                    while (i--) {
                        WaitForVblank();
                        tstsndcmp(1, sound[1].end);
                    }
                }
                memcpy(videoBuffer, l8Bitmap, 76800);
                tilex = 5, tiley = 9;
                MoveSprite(&sprites[2], 240, 160);
                px = 104, py = 136;
                dir = 0;
                sprites[0].attribute1 = SIZE_16 | px;
                updateSprite(0, 16, 0, 0);
                level++;
                l4s = 0;
                MoveSprite(&sprites[0], px, py);
                RotateSprite(1, 0, 256, 256);
                CopyOAM();
                for (Phase = 0; Phase < 17; Phase++) {
                    i = 2;
                    REG_COLEY = 16 - Phase;
                    while (i--) {
                        WaitForVblank();
                        tstsndcmp(1, sound[1].end);
                    }
                }
                sprites[1].attribute2 = 512 + 48; // NOTE: mode4 doesn't support the first tiles, so offset of 512 is requirerd
                glidetime(1, 128 + 16, -8, 96, 50, 2);
                i = 5;
                while (i--) {
                    WaitForVblank();
                    tstsndcmp(1, sound[1].end);
                }
                memcpy(videoBuffer, l8bBitmap, 76800);
                sprites[2].attribute0 = COLOR_256 | SQUARE | 160;
                sprites[2].attribute1 = SIZE_8 | 240;
                sprites[2].attribute2 = 512 + 88;
                MoveSprite(&sprites[0], 240, 160);
                while (!(keyDown(KEY_A)))

                {
                    WaitForVblank();
                    tstsndcmp(1, sound[1].end);
                    if (keyDown(KEY_LEFT)) {
                        arpos = 0;
                    }
                    if (keyDown(KEY_RIGHT)) {
                        arpos = 1;
                    }
                    if (arpos == 0) {
                        MoveSprite(&sprites[2], 76, 136);
                    } else {
                        MoveSprite(&sprites[2], 128, 136);
                    }
                    CopyOAM();
                }
                if (arpos == 0) {
                    SaveInt(0, level*10);
                }
                memcpy(videoBuffer, l8Bitmap, 76800);
                MoveSprite(&sprites[2], 240, 160);
                MoveSprite(&sprites[0], px, py);
                rot = 0;
                for (i = 256; i < 1764; i += 15) {
                    rot += 15;
                    WaitForVblank();
                    tstsndcmp(1, sound[1].end);
                    RotateSprite(1, rot, i, i);
                    CopyOAM();
                }
                MoveSprite(&sprites[1], 240, 160);
            }
        } else if (level == 8) {
            if (GetPixel3(px, py) == 0x7ea0) {
                if ((tilex == 4)AND(tiley == 2)) {
                    for (Phase = 0; Phase < 17; Phase++) {
                        i = 2;
                        REG_COLEY = Phase;
                        while (i--) {
                            WaitForVblank();
                            tstsndcmp(1, sound[1].end);
                        }
                    }
                    tilex = 5, tiley = 9;
                    px = 104, py = 136;
                    dir = 0;
                    memcpy(videoBuffer, l9Bitmap, 76800);
                    sprites[0].attribute1 = SIZE_16 | px;
                    updateSprite(0, 0, 0, 0);
                    MoveSprite(&sprites[0], px, py);
                    CopyOAM();
                    for (Phase = 0; Phase < 17; Phase++) {
                        i = 2;
                        REG_COLEY = 16 - Phase;
                        while (i--) {
                            WaitForVblank();
                            tstsndcmp(1, sound[1].end);
                        }
                    }
                    level++;
                } else {
                    die();
                    return 0;
                }
            }
        } else if (level == 9) {
            if (GetPixel3(px, py) == 0x7ea0) {
                if ((tilex == 1)AND(tiley == 3)) {
                    for (Phase = 0; Phase < 17; Phase++) {
                        i = 2;
                        REG_COLEY = Phase;
                        while (i--) {
                            WaitForVblank();
                            tstsndcmp(1, sound[1].end);
                        }
                    }
                    tilex = 5, tiley = 9;
                    px = 112, py = 136;
                    dir = 0;
                    MoveSprite(&sprites[0], px, py);
                    CopyOAM();
                    memcpy(videoBuffer, l10Bitmap, 76800);
                    sprites[0].attribute1 = SIZE_16 | px;
                    updateSprite(0, 0, 0, 0);
                    for (Phase = 0; Phase < 17; Phase++) {
                        i = 2;
                        REG_COLEY = 16 - Phase;
                        while (i--) {
                            WaitForVblank();
                            tstsndcmp(1, sound[1].end);
                        }
                    }
                    level++;
                } else {
                    die();
                    return 0;
                }
            }
        } else if (level == 10) {
            if ((tilex == 5)AND(tiley == 2)) {
                if (keyDown(KEY_A)) {
                    memcpy(videoBuffer, l10bBitmap, 76800);
                    while (keyDown(KEY_A)) {
                        WaitForVblank();
                        tstsndcmp(1, sound[1].end);
                    }
                    while (!((keyDown(KEY_A))OR(keyDown(KEY_B)))) {
                        WaitForVblank();
                        tstsndcmp(1, sound[1].end);
                    }
                    if (keyDown(KEY_A)) {
                        memcpy(videoBuffer, l10cBitmap, 76800);
                        while (keyDown(KEY_A)) {
                            WaitForVblank();
                            tstsndcmp(1, sound[1].end);
                        }
                        while (!(keyDown(KEY_A))) {
                            WaitForVblank();
                            tstsndcmp(1, sound[1].end);
                        }
                        die();
                        return 0;
                    } else {
                        memcpy(videoBuffer, l10dBitmap, 76800);
                        while (keyDown(KEY_A)) {
                            WaitForVblank();
                            tstsndcmp(1, sound[1].end);
                        }
                        while (!(keyDown(KEY_A))) {
                            WaitForVblank();
                            tstsndcmp(1, sound[1].end);
                        }
                        for (Phase = 0; Phase < 17; Phase++) {
                            i = 2;
                            REG_COLEY = Phase;
                            while (i--) {
                                WaitForVblank();
                                tstsndcmp(1, sound[1].end);
                            }
                        }
                        tilex = 6, tiley = 9;
                        px = 120, py = 136;
                        dir = 1;
                        memcpy(videoBuffer, l11Bitmap, 76800);
                        sprites[0].attribute1 = SIZE_16 | px;
                        updateSprite(0, 16, 0, 0);
                        MoveSprite(&sprites[0], px, py);
                        CopyOAM();
                        for (Phase = 0; Phase < 17; Phase++) {
                            i = 2;
                            REG_COLEY = 16 - Phase;
                            while (i--) {
                                WaitForVblank();
                                tstsndcmp(1, sound[1].end);
                            }
                        }
                        level++;
                    }
                }
            }
        } else if (level == 11) {
            if (GetPixel3(px, py) == 0x7ea0) {
                if ((tilex == 6)AND(tiley == 2)) {
                    for (Phase = 0; Phase < 17; Phase++) {
                        i = 2;
                        REG_COLEY = Phase;
                        while (i--) {
                            WaitForVblank();
                            tstsndcmp(1, sound[1].end);
                        }
                    }
                    tilex = 5, tiley = 4;
                    px = 104, py = 56;
                    dir = 0;
                    MoveSprite(&sprites[0], px, py);
                    CopyOAM();
                    memcpy(videoBuffer, l12Bitmap, 76800);
                    sprites[0].attribute1 = SIZE_16 | px;
                    updateSprite(0, 0, 0, 0);
                    MoveSprite(&sprites[0], px, py);
                    CopyOAM();
                    for (Phase = 0; Phase < 17; Phase++) {
                        i = 2;
                        REG_COLEY = 16 - Phase;
                        while (i--) {
                            WaitForVblank();
                            tstsndcmp(1, sound[1].end);
                        }
                    }
                    level++;
                } else {
                    die();
                    return 0;
                }
            }
        } else if (level == 12) {
            if (GetPixel3(px, py) == 0x7ea0) {
                if ((tilex == 9)AND(tiley == 4)) {
                    for (Phase = 0; Phase < 17; Phase++) {
                        i = 2;
                        REG_COLEY = Phase;
                        while (i--) {
                            WaitForVblank();
                            tstsndcmp(1, sound[1].end);
                        }
                    }
                    tilex = 6, tiley = 5;
                    px = 120, py = 72;
                    dir = 0;
                    memcpy(videoBuffer, l13Bitmap, 76800);
                    sprites[0].attribute1 = SIZE_16 | px;
                    updateSprite(0, 0, 0, 0);
                    MoveSprite(&sprites[0], px, py);
                    CopyOAM();
                    for (Phase = 0; Phase < 17; Phase++) {
                        i = 2;
                        REG_COLEY = 16 - Phase;
                        while (i--) {
                            WaitForVblank();
                            tstsndcmp(1, sound[1].end);
                        }
                    }
                    level++;
                } else {
                    die();
                    return 0;
                }
            }
        } else if (level == 13) {
            if (GetPixel3(px, py) == 0x7ea0) {
                if ((tilex == 10)AND(tiley == 7)) {
                    for (Phase = 0; Phase < 17; Phase++) {
                        i = 2;
                        REG_COLEY = Phase;
                        while (i--) {
                            WaitForVblank();
                            tstsndcmp(1, sound[1].end);
                        }
                    }
                    tilex = 1, tiley = 5;
                    px = 40, py = 72;
                    dir = 0;
                    memcpy(videoBuffer, l14Bitmap, 76800);
                    sprites[0].attribute1 = SIZE_16 | px;
                    updateSprite(0, 0, 0, 0);
                    MoveSprite(&sprites[0], px, py);
                    CopyOAM();
                    for (Phase = 0; Phase < 17; Phase++) {
                        i = 2;
                        REG_COLEY = 16 - Phase;
                        while (i--) {
                            WaitForVblank();
                            tstsndcmp(1, sound[1].end);
                        }
                    }
                    level++;
                } else {
                    die();
                    return 0;
                }
            }
        } else if (level == 14) {
            if (GetPixel3(px, py) == 0x7ea0) {
                if ((tilex == 2)AND(tiley == 9)) {
                    for (Phase = 0; Phase < 17; Phase++) {
                        i = 2;
                        REG_COLEY = Phase;
                        while (i--) {
                            WaitForVblank();
                            tstsndcmp(1, sound[1].end);
                        }
                    }
                    tilex = 10, tiley = 6;
                    px = 184, py = 88;
                    dir = 3;
                    memcpy(videoBuffer, l15Bitmap, 76800);
                    sprites[0].attribute1 = SIZE_16 | HORIZONTAL_FLIP | px;
                    updateSprite(0, 0, 0, 0);
                    MoveSprite(&sprites[0], px, py);
                    CopyOAM();
                    for (Phase = 0; Phase < 17; Phase++) {
                        i = 2;
                        REG_COLEY = 16 - Phase;
                        while (i--) {
                            WaitForVblank();
                            tstsndcmp(1, sound[1].end);
                        }
                    }
                    level++;
                } else {
                    die();
                    return 0;
                }
            }
        } else if (level == 15) {
            if (GetPixel3(px, py) == 0x7ea0) {
                if ((tilex == 1)AND(tiley == 6)) {
                    for (Phase = 0; Phase < 17; Phase++) {
                        i = 2;
                        REG_COLEY = Phase;
                        while (i--) {
                            WaitForVblank();
                            tstsndcmp(1, sound[1].end);
                        }
                    }
                    tilex = 7, tiley = 1;
                    px = 136, py = 8;
                    dir = 2;
                    memcpy(videoBuffer, l16Bitmap, 76800);
                    sprites[0].attribute1 = SIZE_16 | px;
                    updateSprite(0, 32, 0, 0);
                    MoveSprite(&sprites[0], px, py);
                    CopyOAM();
                    for (Phase = 0; Phase < 17; Phase++) {
                        i = 2;
                        REG_COLEY = 16 - Phase;
                        while (i--) {
                            WaitForVblank();
                            tstsndcmp(1, sound[1].end);
                        }
                    }
                    level++;
                } else {
                    die();
                    return 0;
                }
            }
        } else if (level == 16) {
            if (GetPixel3(px, py) == 0x7ea0) {
                if ((tilex == 5)AND(tiley == 1)) {
                    for (Phase = 0; Phase < 17; Phase++) {
                        i = 2;
                        REG_COLEY = Phase;
                        while (i--) {
                            WaitForVblank();
                            tstsndcmp(1, sound[1].end);
                        }
                    }
                    tilex = 6, tiley = 7;
                    px = 120, py = 104;
                    dir = 0;
                    memcpy(videoBuffer, l17Bitmap, 76800);
                    sprites[0].attribute1 = SIZE_16 | px;
                    updateSprite(0, 16, 0, 0);
                    MoveSprite(&sprites[0], px, py);
                    CopyOAM();
                    for (Phase = 0; Phase < 17; Phase++) {
                        i = 2;
                        REG_COLEY = 16 - Phase;
                        while (i--) {
                            WaitForVblank();
                            tstsndcmp(1, sound[1].end);
                        }
                    }
                    level++;
                    i = 60;
                    while (i--) {
                        WaitForVblank();
                        tstsndcmp(1, sound[1].end);
                    }
                    RotateSprite(1, 0, 256, 256);
                    glidetime(1, 240, 160, 112, 50, 2);
                    i = 5;
                    while (i--) {
                        WaitForVblank();
                        tstsndcmp(1, sound[1].end);
                    }
                    memcpy(videoBuffer, l17bBitmap, 76800);
                    sprites[2].attribute0 = COLOR_256 | SQUARE | 160;
                    sprites[2].attribute1 = SIZE_8 | 240;
                    sprites[2].attribute2 = 512 + 88;
                    MoveSprite(&sprites[0], 240, 160);
                    while (!(keyDown(KEY_A)))

                    {
                        WaitForVblank();
                        tstsndcmp(1, sound[1].end);
                        if (keyDown(KEY_LEFT)) {
                            arpos = 0;
                        }
                        if (keyDown(KEY_RIGHT)) {
                            arpos = 1;
                        }
                        if (arpos == 0) {
                            MoveSprite(&sprites[2], 76, 136);
                        } else {
                            MoveSprite(&sprites[2], 128, 136);
                        }
                        CopyOAM();
                    }
                    if (arpos == 0) {
                        SaveInt(0, level);
                    }
                    memcpy(videoBuffer, l17Bitmap, 76800);
                    MoveSprite(&sprites[2], 240, 160);
                    MoveSprite(&sprites[0], px, py);
                    rot = 0;
                    for (i = 256; i < 1764; i += 15) {
                        rot += 15;
                        WaitForVblank();
                        tstsndcmp(1, sound[1].end);
                        RotateSprite(1, rot, i, i);
                        CopyOAM();
                    }
                    MoveSprite(&sprites[1], 240, 160);

                } else {
                    die();
                    return 0;
                }
            }
        } else if (level == 17) {
            if (GetPixel3(px, py) == 0x7ea0) {
                if ((tilex == 3)AND(tiley == 3)) {
                    for (Phase = 0; Phase < 17; Phase++) {
                        i = 2;
                        REG_COLEY = Phase;
                        while (i--) {
                            WaitForVblank();
                            tstsndcmp(1, sound[1].end);
                        }
                    }
                    tilex = 5, tiley = 5;
                    px = 104, py = 72;
                    dir = 2;
                    memcpy(videoBuffer, l18Bitmap, 76800);
                    sprites[0].attribute1 = SIZE_16 | px;
                    updateSprite(0, 0, 0, 0);
                    MoveSprite(&sprites[0], px, py);
                    CopyOAM();
                    for (Phase = 0; Phase < 17; Phase++) {
                        i = 2;
                        REG_COLEY = 16 - Phase;
                        while (i--) {
                            WaitForVblank();
                            tstsndcmp(1, sound[1].end);
                        }
                    }
                    level++;
                } else {
                    die();
                    return 0;
                }
            }
        } else if (level == 18) {
            if (GetPixel3(px, py) == 0x7ea0) {
                if ((tilex == 7)AND(tiley == 8)) {
                    for (Phase = 0; Phase < 17; Phase++) {
                        i = 2;
                        REG_COLEY = Phase;
                        while (i--) {
                            WaitForVblank();
                            tstsndcmp(1, sound[1].end);
                        }
                    }
                    tilex = 6, tiley = 1;
                    px = 120, py = 8;
                    dir = 2;
                    memcpy(videoBuffer, l19Bitmap, 76800);
                    sprites[0].attribute1 = SIZE_16 | px;
                    updateSprite(0, 32, 0, 0);
                    MoveSprite(&sprites[0], px, py);
                    CopyOAM();
                    for (Phase = 0; Phase < 17; Phase++) {
                        i = 2;
                        REG_COLEY = 16 - Phase;
                        while (i--) {
                            WaitForVblank();
                            tstsndcmp(1, sound[1].end);
                        }
                    }
                    level++;
                } else {
                    die();
                    return 0;
                }
            }
        } else if (level == 19) {
            if (GetPixel3(px, py) == 0x7ea0) {
                if ((tilex == 1)AND(tiley == 7)) {
                    for (Phase = 0; Phase < 17; Phase++) {
                        i = 2;
                        REG_COLEY = Phase;
                        while (i--) {
                            WaitForVblank();
                            tstsndcmp(1, sound[1].end);
                        }
                    }
                    tilex = 4, tiley = 6;
                    px = 88, py = 88;
                    dir = 0;
                    memcpy(videoBuffer, l20Bitmap, 76800);
                    sprites[0].attribute1 = SIZE_16 | px;
                    updateSprite(0, 0, 0, 0);
                    MoveSprite(&sprites[0], px, py);
                    CopyOAM();
                    for (Phase = 0; Phase < 17; Phase++) {
                        i = 2;
                        REG_COLEY = 16 - Phase;
                        while (i--) {
                            WaitForVblank();
                            tstsndcmp(1, sound[1].end);
                        }
                    }
                    level++;
                } else {
                    die();
                    return 0;
                }
            }
        } else if (level == 20) {
            if (GetPixel3(px, py) == 0x7ea0) {
                if ((tilex == 10)AND(tiley == 6)) {
                    for (Phase = 0; Phase < 17; Phase++) {
                        i = 2;
                        REG_COLEY = Phase;
                        while (i--) {
                            WaitForVblank();
                            tstsndcmp(1, sound[1].end);
                        }
                    }
                    tilex = 2, tiley = 1;
                    px = 56, py = 8;
                    dir = 0;
                    memcpy(videoBuffer, l21Bitmap, 76800);
                    sprites[0].attribute1 = SIZE_16 | px;
                    updateSprite(0, 0, 0, 0);
                    MoveSprite(&sprites[0], px, py);
                    CopyOAM();
                    for (Phase = 0; Phase < 17; Phase++) {
                        i = 2;
                        REG_COLEY = 16 - Phase;
                        while (i--) {
                            WaitForVblank();
                            tstsndcmp(1, sound[1].end);
                        }
                    }
                    level++;
                } else {
                    die();
                    return 0;
                }
            }
        } else if (level == 21) {
            if (GetPixel3(px, py) == 0x7ea0) {
                if ((tilex == 8)AND(tiley == 4)) {
                    for (Phase = 0; Phase < 17; Phase++) {
                        i = 2;
                        REG_COLEY = Phase;
                        while (i--) {
                            WaitForVblank();
                            tstsndcmp(1, sound[1].end);
                        }
                    }
                    tilex = 1, tiley = 1;
                    px =40, py = 8;
                    dir = 0;
                    memcpy(videoBuffer, l22Bitmap, 76800);
                    sprites[0].attribute1 = SIZE_16 | px;
                    updateSprite(0, 0, 0, 0);
                    MoveSprite(&sprites[0], px, py);
                    offsetOAM = 0;
                    loadSpritePal((void*)sprsdkPalette);
                    loadSpriteGraphics((void*)sprsdk, 2048);

                    CopyOAM();
                    for (Phase = 0; Phase < 17; Phase++) {
                        i = 2;
                        REG_COLEY = 16 - Phase;
                        while (i--) {
                            WaitForVblank();
                            tstsndcmp(1, sound[1].end);
                        }
                    }
                    level++;
                } else {
                    die();
                    return 0;
                }
            }
        } else if (level == 22) {
            if ((tilex == 4)AND(tiley = 1)) {
                if (keyDown(KEY_A)) {
                    while (keyDown(KEY_A)) {
                        WaitForVblank();
                        tstsndcmp(1, sound[1].end);
                    }
                    CopyOAM();
                    memcpy(videoBuffer, l22bBitmap, 76800);
                    while (!(keyDown(KEY_A))) {
                        WaitForVblank();
                        tstsndcmp(1, sound[1].end);
                    }
                    memcpy(videoBuffer, l22Bitmap, 76800);
                    while (keyDown(KEY_A)) {
                        WaitForVblank();
                        tstsndcmp(1, sound[1].end);
                    }
                }
            }
            if (GetPixel3(px, py) == 0x7ea0) {
                if ((tilex == 3)AND(tiley == 1)) {
                    for (Phase = 0; Phase < 17; Phase++) {
                        i = 2;
                        REG_COLEY = Phase;
                        while (i--) {
                            WaitForVblank();
                            tstsndcmp(1, sound[1].end);
                        }
                    }
                    tilex = 4, tiley = 9;
                    px = 88, py = 136;
                    dir = 0;
                    memcpy(videoBuffer, l23Bitmap, 76800);
                    sprites[0].attribute1 = SIZE_16 | px;
                    updateSprite(0, 0, 0, 0);
                    MoveSprite(&sprites[0], px, py);
                    CopyOAM();
                    for (Phase = 0; Phase < 17; Phase++) {
                        i = 2;
                        REG_COLEY = 16 - Phase;
                        while (i--) {
                            WaitForVblank();
                            tstsndcmp(1, sound[1].end);
                        }
                    }
                    level++;
                } else {
                    die();
                    return 0;
                }
            }
        } else if (level == 23) {
            if (GetPixel3(px, py) == 0x7ea0) {
                if ((tilex == 10)AND(tiley == 7)) {
                    for (Phase = 0; Phase < 17; Phase++) {
                        i = 2;
                        REG_COLEY = Phase;
                        while (i--) {
                            WaitForVblank();
                            tstsndcmp(1, sound[1].end);
                        }
                    }
                    tilex = 1, tiley = 1;
                    px = 40, py = 8;
                    dir = 0;
                    memcpy(videoBuffer, l24Bitmap, 76800);
                    sprites[0].attribute1 = SIZE_16 | px;
                    updateSprite(0, 0, 0, 0);
                    MoveSprite(&sprites[0], px, py);
                    CopyOAM();
                    for (Phase = 0; Phase < 17; Phase++) {
                        i = 2;
                        REG_COLEY = 16 - Phase;
                        while (i--) {
                            WaitForVblank();
                            tstsndcmp(1, sound[1].end);
                        }
                    }
                    level++;
                } else {
                    die();
                    return 0;
                }
            }
        } else if (level == 24) {
            if (GetPixel3(px, py) == 0x7ea0) {
                if ((tilex == 8)AND(tiley == 6)) {
                    for (Phase = 0; Phase < 17; Phase++) {
                        i = 2;
                        REG_COLEY = Phase;
                        while (i--) {
                            WaitForVblank();
                            tstsndcmp(1, sound[1].end);
                        }
                    }
                    tilex = 1, tiley = 1;
                    px = 40, py = 8;
                    dir = 0;
                    memcpy(videoBuffer, l25Bitmap, 76800);
                    sprites[0].attribute1 = SIZE_16 | px;
                    updateSprite(0, 0, 0, 0);
                    MoveSprite(&sprites[0], px, py);
                    CopyOAM();
                    for (Phase = 0; Phase < 17; Phase++) {
                        i = 2;
                        REG_COLEY = 16 - Phase;
                        while (i--) {
                            WaitForVblank();
                            tstsndcmp(1, sound[1].end);
                        }
                    }
                    level++;
                } else {
                    die();
                    return 0;
                }
            }
        } else if (level == 25) {
            if (GetPixel3(px, py) == 0x7ea0) {
                if ((tilex == 7)AND(tiley == 7)) {
					for (Phase = 0; Phase < 17; Phase++) {
						i = 2;
						REG_COLEY = Phase;
						while (i--) {
							WaitForVblank();
							tstsndcmp(1, sound[1].end);
						}
					}
					tilex = 3, tiley = 9;
					px = 72, py = 136;
					dir = 0;
					memcpy(videoBuffer, l26Bitmap, 76800);
					sprites[0].attribute1 = SIZE_16 | px;
					updateSprite(0, 0, 0, 0);
					MoveSprite(&sprites[0], px, py);
					CopyOAM();
					for (Phase = 0; Phase < 17; Phase++) {
						i = 2;
						REG_COLEY = 16 - Phase;
						while (i--) {
							WaitForVblank();
							tstsndcmp(1, sound[1].end);
						}
					}
					level++;
                } else {
                    die();
                    return 0;
                }
            }
        }
		else if (level == 26) {
			if (GetPixel3(px, py) == 0x7ea0) {
				if ((tilex == 1)AND(tiley == 9)) {
					for (Phase = 0; Phase < 17; Phase++) {
						i = 2;
						REG_COLEY = Phase;
						while (i--) {
							WaitForVblank();
							tstsndcmp(1, sound[1].end);
						}
					}
					tilex = 5, tiley = 9;
					px = 104, py = 136;
					dir = 0;	
					memcpy(videoBuffer, l27Bitmap, 76800);
					offsetOAM = 0;
					loadSpritePal((void*)sprsPalette);
					loadSpriteGraphics((void*)sprs, 2048);
					sprites[0].attribute1 = SIZE_16 | px;
					updateSprite(0, 16, 0, 0);
					MoveSprite(&sprites[0], px, py);
					CopyOAM();
					for (Phase = 0; Phase < 17; Phase++) {
						i = 2;
						REG_COLEY = 16 - Phase;
						while (i--) {
							WaitForVblank();
							tstsndcmp(1, sound[1].end);
						}
					}
					level++;
					i = 60;
					while (i--) {
						WaitForVblank();
						tstsndcmp(1, sound[1].end);
					}
					RotateSprite(1, 0, 256, 256);
					glidetime(1, 240, 160, 96, 50, 2);
					i = 5;
					while (i--) {
						WaitForVblank();
						tstsndcmp(1, sound[1].end);
					}
					memcpy(videoBuffer, l27bBitmap, 76800);
					sprites[2].attribute0 = COLOR_256 | SQUARE | 160;
					sprites[2].attribute1 = SIZE_8 | 240;
					sprites[2].attribute2 = 512 + 88;
					MoveSprite(&sprites[0], 240, 160);
					while (!(keyDown(KEY_A)))

					{
						WaitForVblank();
						tstsndcmp(1, sound[1].end);
						if (keyDown(KEY_LEFT)) {
							arpos = 0;
						}
						if (keyDown(KEY_RIGHT)) {
							arpos = 1;
						}
						if (arpos == 0) {
							MoveSprite(&sprites[2], 76, 136);
						}
						else {
							MoveSprite(&sprites[2], 128, 136);
						}
						CopyOAM();
					}
					if (arpos == 0) {
						SaveInt(0, level);
					}
					memcpy(videoBuffer, l27Bitmap, 76800);
					MoveSprite(&sprites[2], 240, 160);
					MoveSprite(&sprites[0], px, py);
					rot = 0;
					for (i = 256; i < 1764; i += 15) {
						rot += 15;
						WaitForVblank();
						tstsndcmp(1, sound[1].end);
						RotateSprite(1, rot, i, i);
						CopyOAM();
					}
					MoveSprite(&sprites[1], 240, 160);


				}
				else {
					die();
					return 0;
				}
			}
		}
		else if (level == 27) {
			if (GetPixel3(px, py) == 0x7ea0) {
				if ((tilex == 1)AND(tiley == 1)) {
					for (Phase = 0; Phase < 17; Phase++) {
						i = 2;
						REG_COLEY = Phase;
						while (i--) {
							WaitForVblank();
							tstsndcmp(1, sound[1].end);
						}
					}
					tilex = 3, tiley = 9;
					px = 72, py = 136;
					dir = 0;
					memcpy(videoBuffer, l28Bitmap, 76800);
					sprites[0].attribute1 = SIZE_16 | px;
					updateSprite(0, 0, 0, 0);
					MoveSprite(&sprites[0], px, py);
					CopyOAM();
					for (Phase = 0; Phase < 17; Phase++) {
						i = 2;
						REG_COLEY = 16 - Phase;
						while (i--) {
							WaitForVblank();
							tstsndcmp(1, sound[1].end);
						}
					}
					level++;
				}
				else {
					die();
					return 0;
				}
			}
		}
		else if (level == 28) {
			if (GetPixel3(px, py) == 0x7c14) {
				tilex = 6, tiley = 2;
				px = 120, py = 24;
			}
			if (GetPixel3(px, py) == 0x7ea0) {
				if ((tilex == 3)AND(tiley == 1)) {
					for (Phase = 0; Phase < 17; Phase++) {
						i = 2;
						REG_COLEY = Phase;
						while (i--) {
							WaitForVblank();
							tstsndcmp(1, sound[1].end);
						}
					}
					tilex = 3, tiley = 9;
					px = 72, py = 136;
					dir = 0;
					memcpy(videoBuffer, l29Bitmap, 76800);
					DrawLine3(120, 135, 136, 135, 0x0000);
					sprites[0].attribute1 = SIZE_16 | px;
					updateSprite(0, 0, 0, 0);
					MoveSprite(&sprites[0], px, py);
					CopyOAM();
					for (Phase = 0; Phase < 17; Phase++) {
						i = 2;
						REG_COLEY = 16 - Phase;
						while (i--) {
							WaitForVblank();
							tstsndcmp(1, sound[1].end);
						}
					}
					level++;
				}
				else {
					die();
					return 0;
				}
			}
		}
		else if (level == 29) {
			if ((tilex == 3)AND(tiley == 9))
			{
				if (keyDown(KEY_A))
				{
					RotateSprite(1, 0, 256, 256);
					REG_SOUNDCNT_H = 0;                                                      //REG_SOUNDCNT_H = 0000 1011 0000 0100, volume = 100, sound goes to the left, sound goes to the right, timer 0 is used, FIFO buffer reset
					REG_SOUNDCNT_X = 0;                                                       //REG_SOUNDCNT_X = 0000 0000 1000 0000, enable the sound system, DMA 1
					REG_DM1SAD = 0;                               //REG_DM1SAD = NAME, address of DMA source is the digitized music sample
					REG_DM1DAD = 0;                                                   //REG_DM1DAD = REG_SGFIFOA, address of DMA destination is FIFO buffer for direct sound A
					REG_DM1CNT_H = 0;                                                    //REG_DM1CNT_H = 1011 0110 0100 0000, DMA destination is fixed, repeat transfer of 4 bytes when FIFO , buffer is empty, enable DMA 1 (number of DMA transfers is ignored), INTERRUPT
					REG_TM0D = 0;                         //REG_TM0D = 65536-(16777216/frequency);, play sample every 16777216/frequency CPU cycles
					REG_TM0CNT = 0;
					Sleep(60);
					glideSpritetoPos(1, 0,  160, px-16, py-16, 0);
					SetMode(MODE_3 | BG2_ENABLE);
					FadeOut(0);
					fillscreen3(0x0000);
					die();
				}
			}
			if ((tilex == 4)AND(tiley == 9))
			{
				if (keyDown(KEY_A))
				{
					memcpy(videoBuffer, l29Bitmap, 76800);
				}
			}
			if (GetPixel3(px, py) == 0x7ea0) {
				if ((tilex == 10)AND(tiley == 4)) {
					for (Phase = 0; Phase < 17; Phase++) {
						i = 2;
						REG_COLEY = Phase;
						while (i--) {
							WaitForVblank();
							tstsndcmp(1, sound[1].end);
						}
					}
					tilex = 5, tiley = 9;
					px = 104, py = 136;
					dir = 0;
					memcpy(videoBuffer, l30Bitmap, 76800);
					sprites[0].attribute1 = SIZE_16 | px;
					updateSprite(0, 16, 0, 0);
					MoveSprite(&sprites[0], px, py);
					CopyOAM();
					for (Phase = 0; Phase < 17; Phase++) {
						i = 2;
						REG_COLEY = 16 - Phase;
						while (i--) {
							WaitForVblank();
							tstsndcmp(1, sound[1].end);
						}
					}
					level++;
					i = 60;
					while (i--) {
						WaitForVblank();
						tstsndcmp(1, sound[1].end);
					}
					RotateSprite(1, 0, 256, 256);
					glidetime(1, 240, 160, 96, 50, 2);
					i = 5;
					while (i--) {
						WaitForVblank();
						tstsndcmp(1, sound[1].end);
					}
					memcpy(videoBuffer, l30cBitmap, 76800);
					sprites[2].attribute0 = COLOR_256 | SQUARE | 160;
					sprites[2].attribute1 = SIZE_8 | 240;
					sprites[2].attribute2 = 512 + 88;
					MoveSprite(&sprites[0], 240, 160);
					CopyOAM();
					while (!(keyDown(KEY_A))) {
						WaitForVblank();
						tstsndcmp(1, sound[1].end);
					}
					while (keyDown(KEY_A)) {
						WaitForVblank();
						tstsndcmp(1, sound[1].end);
					}
					memcpy(videoBuffer, l30bBitmap, 76800);
					while (!(keyDown(KEY_A))) {
						WaitForVblank();
						tstsndcmp(1, sound[1].end);
					}
					while (keyDown(KEY_A)) {
						WaitForVblank();
						tstsndcmp(1, sound[1].end);
					}
					memcpy(videoBuffer, l30dBitmap, 76800);
					while (!(keyDown(KEY_A)))

					{
						WaitForVblank();
						tstsndcmp(1, sound[1].end);
						if (keyDown(KEY_LEFT)) {
							arpos = 0;
						}
						if (keyDown(KEY_RIGHT)) {
							arpos = 1;
						}
						if (arpos == 0) {
							MoveSprite(&sprites[2], 76, 136);
						}
						else {
							MoveSprite(&sprites[2], 128, 136);
						}
						CopyOAM();
					}
					if (arpos == 0) {
						SaveInt(0, level);
					}
					memcpy(videoBuffer, l30Bitmap, 76800);
					MoveSprite(&sprites[2], 240, 160);
					MoveSprite(&sprites[0], px, py);
					rot = 0;
					for (i = 256; i < 1764; i += 15) {
						rot += 15;
						WaitForVblank();
						tstsndcmp(1, sound[1].end);
						RotateSprite(1, rot, i, i);
						CopyOAM();
					}
					MoveSprite(&sprites[1], 240, 160);

				}
				else {
					die();
					return 0;
				}
			}
		}
		else if (level == 30) {
			if (GetPixel3(px, py) == 0x7ea0) {
				if ((tilex == 1)AND(tiley == 1)) {
					for (Phase = 0; Phase < 17; Phase++) {
						i = 2;
						REG_COLEY = Phase;
						while (i--) {
							WaitForVblank();
							tstsndcmp(1, sound[1].end);
						}
					}
					tilex = 1, tiley = 9;
					px = 40, py = 136;
					dir = 0;
					memcpy(videoBuffer, l31Bitmap, 76800);
					offsetOAM = 0;
					sprites[0].attribute1 = SIZE_16 | px;
					updateSprite(0, 16, 0, 0);
					MoveSprite(&sprites[0], px, py);
					CopyOAM();
					for (Phase = 0; Phase < 17; Phase++) {
						i = 2;
						REG_COLEY = 16 - Phase;
						while (i--) {
							WaitForVblank();
							tstsndcmp(1, sound[1].end);
						}
					}
					level++;

				}
				else {
					die();
					return 0;
				}
			}
		}
		else if (level == 31) {
			if ((tilex == 5)AND(tiley == 6)) {
				if (keyDown(KEY_A))
				{
					while (keyDown(KEY_A)) {
						WaitForVblank();
						tstsndcmp(1, sound[1].end);
					}
					CopyOAM();
					memcpy(videoBuffer, l31bBitmap, 76800);
					while (!(keyDown(KEY_A))) {
						WaitForVblank();
						tstsndcmp(1, sound[1].end);
					}
					memcpy(videoBuffer, l31Bitmap, 76800);
					while (keyDown(KEY_A)) {
						WaitForVblank();
						tstsndcmp(1, sound[1].end);
					}
				}
			}

			if (GetPixel3(px, py) == 0x7ea0) {
				if ((tilex == 10)AND(tiley == 1)) {
					for (Phase = 0; Phase < 17; Phase++) {
						i = 2;
						REG_COLEY = Phase;
						while (i--) {
							WaitForVblank();
							tstsndcmp(1, sound[1].end);
						}
					}
					tilex = 1, tiley = 1;
					px = 40, py = 8;
					dir = 0;
					memcpy(videoBuffer, l32Bitmap, 76800);
					offsetOAM = 0;
					sprites[0].attribute1 = SIZE_16 | px;
					updateSprite(0, 16, 0, 0);
					MoveSprite(&sprites[0], px, py);
					CopyOAM();
					for (Phase = 0; Phase < 17; Phase++) {
						i = 2;
						REG_COLEY = 16 - Phase;
						while (i--) {
							WaitForVblank();
							tstsndcmp(1, sound[1].end);
						}
					}
					level++;

				}
				else {
					die();
					return 0;
				}
			}
		}
		else if (level == 32) {
			if (GetPixel3(px, py) == 0x7ea0) {
				if ((tilex == 9)AND(tiley == 4)) {
					for (Phase = 0; Phase < 17; Phase++) {
						i = 2;
						REG_COLEY = Phase;
						while (i--) {
							WaitForVblank();
							tstsndcmp(1, sound[1].end);
						}
					}
				tilex =5, tiley = 6;
				px = 104, py = 88;
				dir = 0;
				memcpy(videoBuffer, l33Bitmap, 76800);
				offsetOAM = 0;
				sprites[0].attribute1 = SIZE_16 | px;
				updateSprite(0, 0, 0, 0);
				MoveSprite(&sprites[0], px, py);
				CopyOAM();
				for (Phase = 0; Phase < 17; Phase++) {
					i = 2;
					REG_COLEY = 16 - Phase;
					while (i--) {
						WaitForVblank();
						tstsndcmp(1, sound[1].end);
					}
				}
				level++;
			}
				else {
					die();
					return 0;
				}
			}
		}
		else if (level == 33) {
			if (GetPixel3(px, py) == 0x7ea0) {
				if ((tilex == 2)AND(tiley == 1)) {
					for (Phase = 0; Phase < 17; Phase++) {
						i = 2;
						REG_COLEY = Phase;
						while (i--) {
							WaitForVblank();
							tstsndcmp(1, sound[1].end);
						}
					}
					tilex = 1, tiley = 1;
					px = 40, py = 8;
					dir = 0;
					memcpy(videoBuffer, l34Bitmap, 76800);
					offsetOAM = 0;
					sprites[0].attribute1 = SIZE_16 | px;
					updateSprite(0, 0, 0, 0);
					MoveSprite(&sprites[0], px, py);
					CopyOAM();
					for (Phase = 0; Phase < 17; Phase++) {
						i = 2;
						REG_COLEY = 16 - Phase;
						while (i--) {
							WaitForVblank();
							tstsndcmp(1, sound[1].end);
						}
					}
					level++;
				}
				else {
					die();
					return 0;
				}
			}
		}
		else if (level == 34) {
			if (GetPixel3(px, py) == 0x7ea0) {
				if ((tilex == 7)AND(tiley == 5)) {
					for (Phase = 0; Phase < 17; Phase++) {
						i = 2;
						REG_COLEY = Phase;
						while (i--) {
							WaitForVblank();
							tstsndcmp(1, sound[1].end);
						}
					}
					tilex = 1, tiley = 1;
					px = 40, py = 8;
					dir = 0;
					memcpy(videoBuffer, l35Bitmap, 76800);
					offsetOAM = 0;
					sprites[0].attribute1 = SIZE_16 | px;
					updateSprite(0, 0, 0, 0);
					MoveSprite(&sprites[0], px, py);
					CopyOAM();
					for (Phase = 0; Phase < 17; Phase++) {
						i = 2;
						REG_COLEY = 16 - Phase;
						while (i--) {
							WaitForVblank();
							tstsndcmp(1, sound[1].end);
						}
					}
					level++;
				}
				else {
					die();
					return 0;
				}
			}
		}
		else if (level == 35) {
			if (GetPixel3(px, py) == 0x7ea0) {
				if ((tilex == 1)AND(tiley == 6)) {
					end();
				}
				else {
					die();
					return 0;
				}
			}
		}
        if (keyDown(KEY_RIGHT)) {
            sprites[0].attribute1 = SIZE_16 | px;
            updateSprite(0, 0, 0, 0);
            frames = 0;
            tilex++;
            dir = 0;
            for (i = 0; i < 16; i++) {
                if ((px == 184)OR(GetPixel3(px + 16, py) == 0x0000)OR((level == 4)AND(tilex == 8)AND(tiley == 8)AND(l4s == 0))) {
                    tilex--;
                    break;
                }

                vsync
                tstsndcmp(1, sound[1].end);
				frames++;
				if (keyDown(KEY_B))
				{
						frames++;
						px++;
						i++;;
				}
                if (!(frames % 8)) {
                    anim++;
                    if (anim >= 4) {
                        anim = 0;
                    }
                }
                if (anim == 0) {
                    updateSprite(0, 0, 0, 0);
                } else if (anim == 1) {
                    updateSprite(0, 8, 0, 0);
                } else if (anim == 2) {
                    updateSprite(0, 0, 0, 0);
                } else {
                    updateSprite(0, 8, 0, 0);
                }
                px++;
                MoveSprite(&sprites[0], px, py);
                CopyOAM();
                dir = 0;
            }
            i = 0;

        }
        if (!((dir == 2)OR(dir == 1))) {
            anim = 0;
        }
        if (keyDown(KEY_UP)) {
            tiley--;
            sprites[0].attribute1 = SIZE_16 | px;
            updateSprite(0, 16, 0, 0);
            frames = 0;
            for (i = 0; i < 16; i++) {
                dir = 1;
                if ((py == 8)OR(GetPixel3(px, py - 1) == 0x0000)) {
                    tiley++;
                    break;
                }
                if ((level == 6)AND(tilex == 9)AND(tiley == 6)AND(l4s == 0)) {
                    tiley++;
                    break;
                }
                vsync
                tstsndcmp(1, sound[1].end);
                udframe++;
				if (keyDown(KEY_B))
				{
					udframe++;;
					py--;
					i++;;
				}
                if (!(udframe % 8)) {
                    anim++;
                    if (anim >= 4) {
                        anim = 0;
                    }
                }
                if (anim == 0) {
                    sprites[0].attribute1 = SIZE_16 | px;
                    updateSprite(0, 16, 0, 0);
                } else if(anim==1) {
                    sprites[0].attribute1 = SIZE_16 | px;
                    updateSprite(0, 24, 0, 0);
                } else if (anim == 2) {
                    sprites[0].attribute1 = SIZE_16 | px;
                    updateSprite(0, 16, 0, 0);
                } else {
                    sprites[0].attribute1 = SIZE_16 | HORIZONTAL_FLIP | px;
                    updateSprite(0, 24, 0, 0);
                }
                py--;
                MoveSprite(&sprites[0], px, py);
                CopyOAM();
                dir = 1;
            }
            i = 0;
        }
        if (!((dir == 2)OR(dir == 1))) {
            anim = 0;
        }
        if (keyDown(KEY_LEFT)) {
            dir = 3;
            tilex--;
            sprites[0].attribute1 = SIZE_16 | HORIZONTAL_FLIP | px;
            updateSprite(0, 0, 0, 0);
            frames = 0;
            for (i = 0; i < 16; i++) {
                dir = 3;
                if ((px == 40)OR(GetPixel3(px - 1, py) == 0x0000)) {
                    tilex++;
                    break;
                }
                vsync
                tstsndcmp(1, sound[1].end);
                frames++;
				if (keyDown(KEY_B))
				{
					frames++;
					px--;
					i++;;
				}
                if (!(frames % 8)) {
                    anim++;
                    if (anim >= 4) {
                        anim = 0;
                    }
                }
                if (anim == 0) {
                    updateSprite(0, 0, 0, 0);
                } else if(anim == 1) {
                    updateSprite(0, 8, 0, 0);
                } else if (anim == 2) {
                    updateSprite(0, 0, 0, 0);
                } else {
                    updateSprite(0, 8, 0, 0);
                }

                px--;
                MoveSprite(&sprites[0], px, py);
                CopyOAM();
            }
            i = 0;
        }
        if (!((dir == 2)OR(dir == 1))) {
            anim = 0;
        }
        if (keyDown(KEY_DOWN)) {
            dir = 2;
            tiley++;
            sprites[0].attribute1 = SIZE_16 | px;
            updateSprite(0, 32, 0, 0);
            frames = 0;
            for (i = 0; i < 16; i++) {
                if ((py == 136)OR(GetPixel3(px, py + 16) == 0x0000)OR((tilex == 6)AND(tiley == 6)AND(level == 3)AND(key == 0))) {
                    tiley--;
                    break;
                }
                vsync
                tstsndcmp(1, sound[1].end);
                udframe++;
				if (keyDown(KEY_B))
				{
					udframe++;
					py++;
						i++;
				}
                if (!(udframe % 8)) {
                    anim++;
                    if (anim >= 4) {
                        anim = 0;
                    }
                }
                if ((level > 21)AND(level<27)) {
                    if (anim == 0) {
                        sprites[0].attribute1 = SIZE_16 | px;
                        updateSprite(0, 16, 0, 0);
                    } else if (anim == 1) {
                        sprites[0].attribute1 = SIZE_16 | px;
                        updateSprite(0, 24, 0, 0);
                    } else if (anim == 2) {
                        sprites[0].attribute1 = SIZE_16 | px;
                        updateSprite(0, 16, 0, 0);
                    } else {
                        sprites[0].attribute1 = SIZE_16 | HORIZONTAL_FLIP | px;
                        updateSprite(0, 24, 0, 0);
                    }
                } else {
                    if (anim == 0) {
                        sprites[0].attribute1 = SIZE_16 | px;
                        updateSprite(0, 32, 0, 0);
                    } else if (anim == 1) {
                        sprites[0].attribute1 = SIZE_16 | px;
                        updateSprite(0, 40, 0, 0);
                    } else if (anim == 2) {
                        sprites[0].attribute1 = SIZE_16 | px;
                        updateSprite(0, 32, 0, 0);
                    } else {
                        sprites[0].attribute1 = SIZE_16 | HORIZONTAL_FLIP | px;
                        updateSprite(0, 40, 0, 0);
                    }
                }
                py++;
                MoveSprite(&sprites[0], px, py);
                CopyOAM();
                dir = 2;
            }
            i = 0;
        }
        MoveSprite(&sprites[0], px, py);
        CopyOAM();
    }
    if (!((dir == 2)OR(dir == 1))) {
        anim = 0;
    }
    return 0;
}
void die() {
    int s;
    initsound32(1, 22050, 208, (void*)rip);
    REG_BLDMOD = 0x00D6;
    REG_SOUNDCNT_H = 0;                                                      //REG_SOUNDCNT_H = 0000 1011 0000 0100, volume = 100, sound goes to the left, sound goes to the right, timer 0 is used, FIFO buffer reset
    REG_SOUNDCNT_X = 0;                                                       //REG_SOUNDCNT_X = 0000 0000 1000 0000, enable the sound system, DMA 1
    REG_DM1SAD = 0;                               //REG_DM1SAD = NAME, address of DMA source is the digitized music sample
    REG_DM1DAD = 0;                                                   //REG_DM1DAD = REG_SGFIFOA, address of DMA destination is FIFO buffer for direct sound A
    REG_DM1CNT_H = 0;                                                    //REG_DM1CNT_H = 1011 0110 0100 0000, DMA destination is fixed, repeat transfer of 4 bytes when FIFO , buffer is empty, enable DMA 1 (number of DMA transfers is ignored), INTERRUPT
    REG_TM0D = 0;                         //REG_TM0D = 65536-(16777216/frequency);, play sample every 16777216/frequency CPU cycles
    REG_TM0CNT = 0;
    FadeOut(8);
    REG_SOUNDCNT_H = 0;                                                      //REG_SOUNDCNT_H = 0000 1011 0000 0100, volume = 100, sound goes to the left, sound goes to the right, timer 0 is used, FIFO buffer reset
    REG_SOUNDCNT_X = 0;                                                       //REG_SOUNDCNT_X = 0000 0000 1000 0000, enable the sound system, DMA 1
    REG_DM1SAD = 0;                               //REG_DM1SAD = NAME, address of DMA source is the digitized music sample
    REG_DM1DAD = 0;                                                   //REG_DM1DAD = REG_SGFIFOA, address of DMA destination is FIFO buffer for direct sound A
    REG_DM1CNT_H = 0;                                                    //REG_DM1CNT_H = 1011 0110 0100 0000, DMA destination is fixed, repeat transfer of 4 bytes when FIFO , buffer is empty, enable DMA 1 (number of DMA transfers is ignored), INTERRUPT
    REG_TM0D = 0;                         //REG_TM0D = 65536-(16777216/frequency);, play sample every 16777216/frequency CPU cycles
    REG_TM0CNT = 0;
    SetMode(MODE_4 | BG2_ENABLE | OBJ_MAP_1D);
    SetPalette((void*)iamgodPalette);
    memcpy(videoBuffer, iamgodBitmap, 38400);
    FadeIn(8);
    musici = 0;
    musici = 0;
    musici = 0;
    musici = 0;
    musici = 0;
    musici = 0;
    musici = 0;
    musici = 0;
    musici = 0;
    musici = 0;
    musici = 0;
    REG_SOUNDCNT1_H = 0x0B0F;                                                       //REG_SOUNDCNT_H = 0000 1011 0000 0100, volume = 100, sound goes to the left, sound goes to the right, timer 0 is used, FIFO buffer reset
    REG_SOUNDCNT1_X = 0x0080;                                                       //REG_SOUNDCNT_X = 0000 0000 1000 0000, enable the sound system, DMA 1
    REG_SD1SAD = (unsigned long)sound[1].song;                                //REG_DM1SAD = NAME, address of DMA source is the digitized music sample
    REG_SD1DAD = 0x040000A0;                                                   //REG_DM1DAD = REG_SGFIFOA, address of DMA destination is FIFO buffer for direct sound A
    REG_SD1CNT_H = 0xB640;                                                       //REG_DM1CNT_H = 1011 0110 0100 0000, DMA destination is fixed, repeat transfer of 4 bytes when FIFO , buffer is empty, enable DMA 1 (number of DMA transfers is ignored), INTERRUPT
    REG_TM0SD = 65536 - (16777216 / sound[1].frequency);                          //REG_TM0D = 65536-(16777216/frequency);, play sample every 16777216/frequency CPU cycles
    REG_TMSDCNT = 0x00C0;
    while (!(keyDown(KEY_A))) {
        WaitForVblank();
        tstsndcmp(1, 208);
    }
    REG_SOUNDCNT_H = 0;                                                      //REG_SOUNDCNT_H = 0000 1011 0000 0100, volume = 100, sound goes to the left, sound goes to the right, timer 0 is used, FIFO buffer reset
    REG_SOUNDCNT_X = 0;                                                       //REG_SOUNDCNT_X = 0000 0000 1000 0000, enable the sound system, DMA 1
    REG_DM1SAD = 0;                               //REG_DM1SAD = NAME, address of DMA source is the digitized music sample
    REG_DM1DAD = 0;                                                   //REG_DM1DAD = REG_SGFIFOA, address of DMA destination is FIFO buffer for direct sound A
    REG_DM1CNT_H = 0;                                                    //REG_DM1CNT_H = 1011 0110 0100 0000, DMA destination is fixed, repeat transfer of 4 bytes when FIFO , buffer is empty, enable DMA 1 (number of DMA transfers is ignored), INTERRUPT
    REG_TM0D = 0;                         //REG_TM0D = 65536-(16777216/frequency);, play sample every 16777216/frequency CPU cycles
    REG_TM0CNT = 0;
    FadeOutWhite(8);
	asm("swi 0x01"::);
    asm("swi 0x26"::);
}
