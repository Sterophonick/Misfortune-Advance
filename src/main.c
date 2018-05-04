#include <libheart.h>
#include "../inc/defs.h"
#include "../inc/soundbank.h"
extern u8 soundbank_bin[];
mm_sfxhand bgm2 = 0;
mm_sfxhand rip2 = 0;
void initSprite(int spr, int size, int offset)
{
    int 	x, y;
    x = 240;
    y = 160;
    // set sprite offscreen, and set it up (size,etc)
    sprites[spr].attribute0 = COLOR_256 | SQUARE | x;
    sprites[spr].attribute1 = size | y;
    sprites[spr].attribute2 = 512 + offset; // NOTE: mode4 doesn't support the first tiles, so offset of 512 is requirerd
}
void updateSprite(int spr, int offset, int sprsize, int ani)
{
    int frame;
    int size;
    size = sprsize * 2;
    frame = size * ani;
    sprites[spr].attribute2 = (512 + offset) + frame; // NOTE: mode4 doesn't support the first tiles, so offset of 512 is requirerd
}
extern int hrt_offsetOAMData;
extern int hrt_offsetOAMPal;
extern int hrt_offsetBGMap;
extern int hrt_offsetBGTile;
extern int hrt_offsetBGPal;
s16 l29k, dir, newframe, px=112, py=120, level,tiley=8,tilex=6,anim,key, l3s,arpos,l4s,keys,udframe,udtemp,Phase, i, size, mus, musici, frames, rot,f1;
#define CHAR_BASE(n)		n<<2
void die();
void tstsndcmp(int s, int time);
void glidetime(int spr, int x1, int y1, int x2, int y2, int frames)
{
    hrt_SetOBJXY(&sprites[spr], x1, y1);
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
    }
    else {
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
        hrt_VblankIntrWait();
        tstsndcmp(1, 416);
        hrt_CopyOAM();
        hrt_SetOBJXY(&sprites[spr], x, y);
        if (d < 0) {
            d = d + dinc1;
            x = x + xinc1;
            y = y + yinc1;
        }
        else {
            d = d + dinc2;
            x = x + xinc2;
            y = y + yinc2;
        }
    }
}

void tstsndcmp(int s, int time)
{
    mm_sound_effect bgm = {
        { SFX_BGM },			// id
        (int)(1.0f * (1 << 10)),	// rate
        0,		// handle
        255,	// volume
        128,	// panning
    };
    mm_sound_effect rip = {
        { SFX_RIP },			// id
        (int)(1.0f * (1 << 10)),	// rate
        0,		// handle
        255,	// volume
        0,	// panning
    };
    if (musici >= time) {
        if(s == 1) {
            bgm2 = mmEffectEx(&bgm);
        }
        else {
            rip2 = mmEffectEx(&rip);
        }
        musici = 0;
    }
    else {
        musici++;
    }
}

void end()
{
	mmEffectCancelAll();
    hrt_SetFXMode(1, 1, 1, 1, 1, 1, 3, 0, 0, 0, 0, 0, 0);
    for (i = 0; i < 17; i++) {
        hrt_SetFXLevel(i);
        hrt_SleepF(2);
    }
    hrt_offsetOAMData = 0;
	hrt_offsetOAMPal = 0;
    hrt_LoadOBJPal((void*)sprsPal, 256);
    hrt_LoadOBJGFX((void*)sprsTiles, 2048);
    memcpy(VRAM, endBitmap, 76800);
    px = 112, py = 136;
    hrt_SetOBJXY(&sprites[0], px, py);
    sprites[0].attribute1 = 0x4000 | px;
    hrt_CreateOBJ(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 16);
    hrt_AffineOBJ(1, 0, 256, 256);
    hrt_CopyOAM();
    for (i = 0; i < 17; i++) {
        hrt_SetFXLevel(16 - i);
        hrt_SleepF(3);
    }
    for (i = 0; i < 64; i++) {
        dir = 1;
        if ((py == 8)OR(hrt_GetPixelInMode3(px, py - 1) == 0x0000)) {
            tiley++;
            break;
        }
        if ((level == 6)AND(tilex == 9)AND(tiley == 6)AND(l4s == 0)) {
            tiley++;
            break;
        }
        hrt_VblankIntrWait();
        udframe++;
        if (!(udframe % 8)) {
            anim++;
            if (anim >= 4) {
                anim = 0;
            }
        }
        if (anim == 0) {
            sprites[0].attribute1 = 0x4000 | px;
            updateSprite(0, 16, 0, 0);
        }
        else if (anim == 1) {
            sprites[0].attribute1 = 0x4000 | px;
            updateSprite(0, 24, 0, 0);
        }
        else if (anim == 2) {
            sprites[0].attribute1 = 0x4000 | px;
            updateSprite(0, 16, 0, 0);
        }
        else {
            sprites[0].attribute1 = 0x4000 | 0x1000 | px;
            updateSprite(0, 24, 0, 0);
        }
        py--;
        hrt_SetOBJXY(&sprites[0], px, py);
        hrt_CopyOAM();
        dir = 1;
    }
    i = 60;
    while (i--) {
        hrt_VblankIntrWait();
    }
    hrt_GlideSpritetoPos(1, 128 + 16, -8, 102, 24, 2.00);
    i = 60;
    while (i--) {
        hrt_VblankIntrWait();
    }
    hrt_SetDSPMode(4, //Mode
                   0,								  //CGB Mode
                   0,								  //Frame Select
                   0,                               //Unlocked HBlank
                   0,                               //Linear OBJ Tile Mapping
                   0,                               //Force Blank
                   0,                               //BG 0
                   0,                               //BG 1
                   1,                               //BG 2
                   0,                               //BG 3
                   0,                               //OBJ
                   0,                               //Win 0
                   0,                               //Win 1
                   0);							  //OBJWin
	hrt_offsetBGPal = 0;
	hrt_LoadBGPal((void*)finalPal, 16);
    memcpy(VRAM, finalBitmap, 76800);
    while (!(keyDown(KEY_A))) {
        hrt_VblankIntrWait();
    }
    hrt_SetFXMode(1, 1, 1, 1, 1, 1, 2, 0, 0, 0, 0, 0, 0);
    for (i = 0; i < 17; i++) {
        hrt_SetFXLevel(i);
        hrt_SleepF(8);
    }
	hrt_SetDSPMode(3, //Mode
		0,								  //CGB Mode
		0,								  //Frame Select
		0,                               //Unlocked HBlank
		0,                               //Linear OBJ Tile Mapping
		0,                               //Force Blank
		0,                               //BG 0
		0,                               //BG 1
		1,                               //BG 2
		0,                               //BG 3
		0,                               //OBJ
		0,                               //Win 0
		0,                               //Win 1
		0);							  //OBJWin
    hrt_FillScreen(0xFFFF);
    hrt_SetFXMode(1, 1, 1, 1, 1, 1, 2, 0, 0, 0, 0, 0, 0);
    for (i = 0; i < 17; i++) {
        hrt_SetFXLevel(16-i);
        hrt_SleepF(8);
    }
    hrt_FillScreen(0xFFFF);
    hrt_PrintOnBitmap(0, 0, "When the child got out,");
    hrt_PrintOnBitmap(0, 9, "the building had");
    hrt_PrintOnBitmap(0, 18, "disappeared.");
    while (!(keyDown(KEY_A))) {
        hrt_VblankIntrWait();
    }
    while (keyDown(KEY_A)) {
        hrt_VblankIntrWait();
    }
    hrt_FillScreen(0xFFFF);
    hrt_PrintOnBitmap(0, 0, "Nobody will ever know");
    hrt_PrintOnBitmap(0, 9, "what exactly happened");
    hrt_PrintOnBitmap(0, 18, "to the people who");
    hrt_PrintOnBitmap(0, 27, "walked into that");
    hrt_PrintOnBitmap(0, 36, "building.");
    while (!(keyDown(KEY_A))) {
        hrt_VblankIntrWait();
    }
    while (keyDown(KEY_A)) {
        hrt_VblankIntrWait();
    }
    hrt_FillScreen(0xFFFF);
    hrt_PrintOnBitmap(0, 0, "On the bright side, the");
    hrt_PrintOnBitmap(0, 9, "child had put the angry");
    hrt_PrintOnBitmap(0, 18, "spirits haunting the");
    hrt_PrintOnBitmap(0, 27, "desert to rest and");
    hrt_PrintOnBitmap(0, 36, "restored peace to the");
    hrt_PrintOnBitmap(0, 45, "world.");
    while (!(keyDown(KEY_A))) {
        hrt_VblankIntrWait();
    }
    while (keyDown(KEY_A)) {
        hrt_VblankIntrWait();
    }
    hrt_FillScreen(0xFFFF);
    hrt_PrintOnBitmap(0, 0, "THE END.");
    while (!(keyDown(KEY_A))) {
        hrt_VblankIntrWait();
    }
    hrt_SetFXMode(1, 1, 1, 1, 1, 1, 2, 0, 0, 0, 0, 0, 0);
    for (i = 0; i < 17; i++) {
        hrt_SetFXLevel(i);
        hrt_SleepF(8);
    }
	hrt_SaveByte(0, 0);
	asm volatile("swi 0x26"::); //resets console
}
extern void hrt_InitNoIntro();
int main()
{
    hrt_EnableSoftReset();
	hrt_InitNoIntro();
    mmInitDefault((mm_addr)soundbank_bin, 8);
	mm_sound_effect enter = {
		{ SFX_DOOR },			// id
		(int)(1.0f * (1 << 10)),	// rate
		0,		// handle
		255,	// volume
		128,	// panning
	};
	mm_sound_effect save = {
		{ SFX_SAVE },			// id
		(int)(1.0f * (1 << 10)),	// rate
		0,		// handle
		255,	// volume
		128,	// panning
	};
	mm_sound_effect load = {
		{ SFX_LOAD },			// id
		(int)(1.0f * (1 << 10)),	// rate
		0,		// handle
		255,	// volume
		128,	// panning
	};
	mm_sound_effect keyuse = {
		{ SFX_KEY },			// id
		(int)(1.0f * (1 << 10)),	// rate
		0,		// handle
		255,	// volume
		128,	// panning
	};
	mm_sfxhand usekey = 0;
	mm_sfxhand fileload = 0;
	mm_sfxhand door = 0;
	mm_sfxhand sav = 0;
    int s;
    REG_BLDCNT = 0x00D6;
    hrt_VblankIntrWait();
    hrt_FillPalette(0, 0xFFFF);
    hrt_SetDSPMode(4, //Mode
                   0,								  //CGB Mode
                   0,								  //Frame Select
                   0,                               //Unlocked HBlank
                   0,                               //Linear OBJ Tile Mapping
                   0,                               //Force Blank
                   0,                               //BG 0
                   0,                               //BG 1
                   1,                               //BG 2
                   0,                               //BG 3
                   0,                               //OBJ
                   0,                               //Win 0
                   0,                               //Win 1
                   0);							  //OBJWin
    REG_BG2CNT = 0x40;
    hrt_SleepF(25);
    hrt_SetOBJXY(&sprites[0], 240, 160);
    hrt_SetOBJXY(&sprites[1], 240, 160);
    hrt_CopyOAM();
    level = 0;
    frames = 0;
    hrt_SetFXMode(1, 1, 1, 1, 1, 1, 2, 0, 0, 0, 0, 0, 0);
    for (i = 0; i < 17; i++) {
        hrt_SetFXLevel(i);
        hrt_SleepF(3);
    }
    hrt_SetDSPMode(4, //Mode
                   0,								  //CGB Mode
                   0,								  //Frame Select
                   0,                               //Unlocked HBlank
                   1,                               //Linear OBJ Tile Mapping
                   0,                               //Force Blank
                   0,                               //BG 0
                   0,                               //BG 1
                   1,                               //BG 2
                   0,                               //BG 3
                   1,                               //OBJ
                   0,                               //Win 0
                   0,                               //Win 1
                   0);							  //OBJWin
    hrt_offsetBGPal = 0;
    hrt_LoadBGPal((void*)titlescreenPal, 256);
    memcpy(VRAM, titlescreenBitmap, 38400);
    hrt_SetFXMode(1, 1, 1, 1, 1, 1, 2, 0, 0, 0, 0, 0, 0);
    for (i = 0; i < 17; i++) {
        hrt_SetFXLevel(16-i);
        hrt_SleepF(8);
    }
    hrt_SleepF(30);
	hrt_offsetOAMData = 0;
	hrt_offsetOAMPal = 0;
    hrt_LoadOBJPal((void*)sprsPal, 256);
    hrt_LoadOBJGFX((void*)sprsTiles,2048);
    initSprite(2, SIZE_8, 88);
    hrt_SetOBJXY(&sprites[2], 0, 57);
    hrt_CopyOAM();
    sprites[32].attribute0 = COLOR_256 | WIDE | 160;
    sprites[32].attribute1 = SIZE_64 | 240;
    sprites[32].attribute2 = 512 + 112; // NOTE: mode4 doesn't support the first tiles, so offset of 512 is requirerd
    hrt_SetOBJXY(&sprites[32], 192, 152);
    level = hrt_LoadByte(0);
    if (!(level == 0)) {
        arpos = 1;
    }
	musici = 208;
    while (!(keyDown(KEY_A))) {
        hrt_VblankIntrWait();
        tstsndcmp(0, 208);
		if (arpos < 0)
		{
			arpos = 0;
		}
		if (arpos > 2)
		{
			arpos = 2;
		}
        if (keyDown(KEY_UP)) {
            arpos--;
			while (keyDown(KEY_UP))
			{
				hrt_VblankIntrWait();
				tstsndcmp(0, 208);
			}
        }
        if (keyDown(KEY_DOWN)) {
            arpos++;
			while (keyDown(KEY_DOWN))
			{
				hrt_VblankIntrWait();
				tstsndcmp(0, 208);
			}
        }
        if (arpos == 0) {
            hrt_SetOBJXY(&sprites[2], 0, 57);
        }
        if (arpos == 1) {
            hrt_SetOBJXY(&sprites[2], 0, 70);
        }
		if (arpos == 2)
		{
			hrt_SetOBJXY(&sprites[2], 0, 83);
		}
        hrt_CopyOAM();
        level = hrt_LoadByte(0);
    }
	mmEffectCancelAll();
	if (arpos == 1) {
		fileload = mmEffectEx(&load);
	}
    REG_BLDCNT = 0x00D6;
    hrt_SetFXMode(1, 1, 1, 1, 1, 1, 3, 0, 0, 0, 0, 0, 0);
    for (i = 0; i < 17; i++) {
        hrt_SetFXLevel(i);
        hrt_SleepF(8);
    }
	if (arpos == 2) {
		hrt_EZ4Exit();
	}
	if (arpos == 0)
	{
		hrt_SaveByte(0, 0);
	}
    initSprite(0, 0x4000, 0);
    initSprite(2, 0x4000, 64);
    hrt_SetOBJXY(&sprites[0], 112, 120);
    sprites[1].attribute0 = COLOR_256 | TALL | ROTATION_FLAG | SIZE_DOUBLE | 160;
    sprites[1].attribute1 = SIZE_32 | ROTDATA(1) | 240;
    sprites[1].attribute2 = 512 + 48; // NOTE: mode4 doesn't support the first tiles, so offset of 512 is requirerd
    hrt_AffineOBJ(1, 0, 256, 256);
	if (arpos == 1)
	{
		if (!(level == 0))
		{
			if (level == 40) {
				initSprite(2, 0x4000, 64);
				hrt_SetOBJXY(&sprites[2], 152, 121);
				memcpy(VRAM, l4Bitmap, 76800);
				initSprite(2, 0x4000, 64);
				tilex = 6, tiley = 5;
				px = 120, py = 72;
				sprites[0].attribute1 = 0x4000 | px;
				updateSprite(0, 16, 0, 0);
				hrt_SetOBJXY(&sprites[0], px, py);
				level = 4;
				hrt_SetOBJXY(&sprites[2], 152, 121);
				hrt_CopyOAM();
			}
			if (level == 80) {
				hrt_SetOBJXY(&sprites[2], 152, 121);
				memcpy(VRAM, l8Bitmap, 76800);
				tilex = 5, tiley = 9;
				initSprite(2, 0x4000, 64);
				px = 104, py = 136;
				sprites[0].attribute1 = 0x4000 | px;
				updateSprite(0, 16, 0, 0);
				level = 8;
				l4s = 0;
				hrt_SetOBJXY(&sprites[0], px, py);
				hrt_AffineOBJ(1, 0, 256, 256);
				hrt_CopyOAM();
			}
			if (level == 17) {
				tilex = 6, tiley = 7;
				px = 120, py = 104;
				dir = 0;
				level = 17;
				memcpy(VRAM, l17Bitmap, 76800);
				sprites[0].attribute1 = 0x4000 | px;
				updateSprite(0, 16, 0, 0);
				hrt_SetOBJXY(&sprites[0], px, py);
				hrt_AffineOBJ(1, 0, 256, 256);
				hrt_CopyOAM();
			}
			if (level == 27) {
				tilex = 5, tiley = 9;
				px = 104, py = 136;
				dir = 0;
				level = 27;
				memcpy(VRAM, l27Bitmap, 76800);
				sprites[0].attribute1 = 0x4000 | px;
				updateSprite(0, 16, 0, 0);
				hrt_SetOBJXY(&sprites[0], px, py);
				hrt_AffineOBJ(1, 0, 256, 256);
				hrt_CopyOAM();
			}
			if (level == 30) {
				tilex = 5, tiley = 9;
				px = 104, py = 136;
				dir = 0;
				level = 30;
				memcpy(VRAM, l30Bitmap, 76800);
				sprites[0].attribute1 = 0x4000 | px;
				updateSprite(0, 16, 0, 0);
				hrt_SetOBJXY(&sprites[0], px, py);
				hrt_AffineOBJ(1, 0, 256, 256);
				hrt_CopyOAM();
			}
		}
		else {
			hrt_SetDSPMode(3, //Mode
				0,								  //CGB Mode
				0,								  //Frame Select
				0,                               //Unlocked HBlank
				0,                               //Linear OBJ Tile Mapping
				0,                               //Force Blank
				0,                               //BG 0
				0,                               //BG 1
				1,                               //BG 2
				0,                               //BG 3
				0,                               //OBJ
				0,                               //Win 0
				0,                               //Win 1
				0);							  //OBJWin
			hrt_FillScreen(0x7c00);
			hrt_SetFXMode(1, 1, 1, 1, 1, 1, 3, 0, 0, 0, 0, 0, 0);
			for (i = 0; i < 17; i++) {
				hrt_SetFXLevel(i);
				hrt_SleepF(0);
			}
			hrt_FillScreen(0x7c00);
			hrt_SetFXLevel(0);
			hrt_PrintOnBitmap(0, 0, "There is a temple hidden");
			hrt_PrintOnBitmap(0, 9, "within the desert.");
			while (!(keyDown(KEY_A))) {
				hrt_VblankIntrWait();
			}
			while (keyDown(KEY_A)) {
				hrt_VblankIntrWait();
			}
			hrt_FillScreen(0x7c00);
			hrt_PrintOnBitmap(0, 0, "It is said to have been");
			hrt_PrintOnBitmap(0, 9, "used as a form of shelter,");
			hrt_PrintOnBitmap(0, 18, "for religious purposes.");
			while (!(keyDown(KEY_A))) {
				hrt_VblankIntrWait();
			}
			while (keyDown(KEY_A)) {
				hrt_VblankIntrWait();
			}
			hrt_FillScreen(0x7c00);
			hrt_PrintOnBitmap(0, 0, "One day, a man performed");
			hrt_PrintOnBitmap(0, 9, "a demonic ritual, causing");
			hrt_PrintOnBitmap(0, 18, "him to become insane,");
			hrt_PrintOnBitmap(0, 27, "and commit a murder in the");
			hrt_PrintOnBitmap(0, 36, "building.");
			while (!(keyDown(KEY_A))) {
				hrt_VblankIntrWait();
			}
			while (keyDown(KEY_A)) {
				hrt_VblankIntrWait();
			}
			hrt_FillScreen(0x7c00);
			hrt_PrintOnBitmap(0, 0, "The temple had to be");
			hrt_PrintOnBitmap(0, 9, "abandoned and it was");
			hrt_PrintOnBitmap(0, 18, "rumored to be extremely");
			hrt_PrintOnBitmap(0, 27, "haunted by the victim.");
			while (!(keyDown(KEY_A))) {
				hrt_VblankIntrWait();
			}
			while (keyDown(KEY_A)) {
				hrt_VblankIntrWait();
			}
			hrt_FillScreen(0x7c00);
			hrt_PrintOnBitmap(0, 0, "Many years later...");
			while (!(keyDown(KEY_A))) {
				hrt_VblankIntrWait();
			}
			while (keyDown(KEY_A)) {
				hrt_VblankIntrWait();
			}
			hrt_FillScreen(0x7c00);
			hrt_PrintOnBitmap(0, 0, "Legend has it that anybody");
			hrt_PrintOnBitmap(0, 9, "who enters this building never");
			hrt_PrintOnBitmap(0, 18, "return, and are presumed dead.");
			while (!(keyDown(KEY_A))) {
				hrt_VblankIntrWait();
			}
			while (keyDown(KEY_A)) {
				hrt_VblankIntrWait();
			}
			hrt_FillScreen(0x7c00);
			hrt_PrintOnBitmap(0, 0, "One day, a boy got lost in");
			hrt_PrintOnBitmap(0, 9, "the desert, so he walked");
			hrt_PrintOnBitmap(0, 18, "until he found this");
			hrt_PrintOnBitmap(0, 27, "ancient building...");
			while (!(keyDown(KEY_A))) {
				hrt_VblankIntrWait();
			}
			while (keyDown(KEY_A)) {
				hrt_VblankIntrWait();
			}
			hrt_SetFXMode(1, 1, 1, 1, 1, 1, 2, 0, 0, 0, 0, 0, 0);
			for (i = 0; i < 17; i++) {
				hrt_SetFXLevel(i);
				hrt_SleepF(8);
			}
			REG_BLDCNT = 0x00D6;
			memcpy(VRAM, l0Bitmap, 76800);
			level = 0;
		}
	}
    else {
        hrt_SetDSPMode(3, //Mode
                       0,								  //CGB Mode
                       0,								  //Frame Select
                       0,                               //Unlocked HBlank
                       0,                               //Linear OBJ Tile Mapping
                       0,                               //Force Blank
                       0,                               //BG 0
                       0,                               //BG 1
                       1,                               //BG 2
                       0,                               //BG 3
                       0,                               //OBJ
                       0,                               //Win 0
                       0,                               //Win 1
                       0);							  //OBJWin
        hrt_FillScreen(0x7c00);
        hrt_SetFXMode(1, 1, 1, 1, 1, 1, 3, 0, 0, 0, 0, 0, 0);
        for (i = 0; i < 17; i++) {
            hrt_SetFXLevel(i);
            hrt_SleepF(0);
        }
        hrt_FillScreen(0x7c00);
		hrt_SetFXLevel(0);
        hrt_PrintOnBitmap(0, 0, "There is a temple hidden");
        hrt_PrintOnBitmap(0, 9, "within the desert.");
        while (!(keyDown(KEY_A))) {
            hrt_VblankIntrWait();
        }
        while (keyDown(KEY_A)) {
            hrt_VblankIntrWait();
        }
        hrt_FillScreen(0x7c00);
        hrt_PrintOnBitmap(0, 0, "It is said to have been");
        hrt_PrintOnBitmap(0, 9, "used as a form of shelter,");
        hrt_PrintOnBitmap(0, 18, "for religious purposes.");
        while (!(keyDown(KEY_A))) {
            hrt_VblankIntrWait();
        }
        while (keyDown(KEY_A)) {
            hrt_VblankIntrWait();
        }
        hrt_FillScreen(0x7c00);
        hrt_PrintOnBitmap(0, 0, "One day, a man performed");
        hrt_PrintOnBitmap(0, 9, "a demonic ritual, causing");
        hrt_PrintOnBitmap(0, 18, "him to become insane,");
        hrt_PrintOnBitmap(0, 27, "and commit a murder in the");
        hrt_PrintOnBitmap(0, 36, "building.");
        while (!(keyDown(KEY_A))) {
            hrt_VblankIntrWait();
        }
        while (keyDown(KEY_A)) {
            hrt_VblankIntrWait();
        }
        hrt_FillScreen(0x7c00);
        hrt_PrintOnBitmap(0, 0, "The temple had to be");
        hrt_PrintOnBitmap(0, 9, "abandoned and it was");
        hrt_PrintOnBitmap(0, 18, "rumored to be extremely");
        hrt_PrintOnBitmap(0, 27, "haunted by the victim.");
        while (!(keyDown(KEY_A))) {
            hrt_VblankIntrWait();
        }
        while (keyDown(KEY_A)) {
            hrt_VblankIntrWait();
        }
        hrt_FillScreen(0x7c00);
        hrt_PrintOnBitmap(0, 0, "Many years later...");
        while (!(keyDown(KEY_A))) {
            hrt_VblankIntrWait();
        }
        while (keyDown(KEY_A)) {
            hrt_VblankIntrWait();
        }
        hrt_FillScreen(0x7c00);
        hrt_PrintOnBitmap(0, 0, "Legend has it that anybody");
        hrt_PrintOnBitmap(0, 9, "who enters this building never");
        hrt_PrintOnBitmap(0, 18, "return, and are presumed dead.");
        while (!(keyDown(KEY_A))) {
            hrt_VblankIntrWait();
        }
        while (keyDown(KEY_A)) {
            hrt_VblankIntrWait();
        }
        hrt_FillScreen(0x7c00);
        hrt_PrintOnBitmap(0, 0, "One day, a boy got lost in");
        hrt_PrintOnBitmap(0, 9, "the desert, so he walked");
        hrt_PrintOnBitmap(0, 18, "until he found this");
        hrt_PrintOnBitmap(0, 27, "ancient building...");
        while (!(keyDown(KEY_A))) {
            hrt_VblankIntrWait();
        }
        while (keyDown(KEY_A)) {
            hrt_VblankIntrWait();
        }
        hrt_SetFXMode(1, 1, 1, 1, 1, 1, 2, 0, 0, 0, 0, 0, 0);
        for (i = 0; i < 17; i++) {
            hrt_SetFXLevel(i);
            hrt_SleepF(8);
        }
        REG_BLDCNT = 0x00D6;
        memcpy(VRAM, l0Bitmap, 76800);
        level = 0;
    }
    hrt_CopyOAM();
    hrt_SetDSPMode(3, //Mode
                   0,								  //CGB Mode
                   0,								  //Frame Select
                   0,                               //Unlocked HBlank
                   1,                               //Linear OBJ Tile Mapping
                   0,                               //Force Blank
                   0,                               //BG 0
                   0,                               //BG 1
                   1,                               //BG 2
                   0,                               //BG 3
                   1,                               //OBJ
                   0,                               //Win 0
                   0,                               //Win 1
                   0);							  //OBJWin
    hrt_SetFXMode(1, 1, 1, 1, 1, 1, 3, 0, 0, 0, 0, 0, 0);
    for (i = 0; i < 17; i++) {
        hrt_SetFXLevel(16-i);
        hrt_SleepF(8);
    }
	hrt_SetFXMode(1, 1, 1, 1, 1, 1, 3, 0, 0, 0, 0, 0, 0);
    musici = 420;
	arpos = 0;
    while (1) {
        if (level == 0) {
            musici = 0;
        }
        hrt_VblankIntrWait();
        if(level>0) {
            tstsndcmp(1, 416);
        }
        if (level == 0) {
            if (py > 135) {
                hrt_SetDSPMode(3, //Mode
                               0,								  //CGB Mode
                               0,								  //Frame Select
                               0,                               //Unlocked HBlank
                               0,                               //Linear OBJ Tile Mapping
                               0,                               //Force Blank
                               0,                               //BG 0
                               0,                               //BG 1
                               1,                               //BG 2
                               0,                               //BG 3
                               0,                               //OBJ
                               0,                               //Win 0
                               0,                               //Win 1
                               0);							  //OBJWin
                memcpy(VRAM, wrongBitmap, 76800);
                while (!(keyDown(KEY_A)));
				asm volatile("swi 0x00"::); //resets console
            }
            if ((tiley < 3)AND(tilex == 6)AND(keyDown(KEY_UP))) {
				memcpy(VRAM, l0bBitmap, 76800);
				usekey = mmEffectEx(&keyuse);
				hrt_SleepF(15);
				for (i = 0; i < 16; i++)
				{
					dir = 1;
					if ((py == 8)OR(hrt_GetPixelInMode3(px, py - 1) == 0x0000)) {
						tiley++;
						break;
					}
					if ((level == 6)AND(tilex == 9)AND(tiley == 6)AND(l4s == 0)) {
						tiley++;
						break;
					}
					hrt_VblankIntrWait();
					tstsndcmp(1, 416);
					udframe++;
					if (!(udframe % 8)) {
						anim++;
						if (anim >= 4) {
							anim = 0;
						}
					}
					if (anim == 0) {
						sprites[0].attribute1 = 0x4000 | px;
						updateSprite(0, 16, 0, 0);
					}
					else if (anim == 1) {
						sprites[0].attribute1 = 0x4000 | px;
						updateSprite(0, 24, 0, 0);
					}
					else if (anim == 2) {
						sprites[0].attribute1 = 0x4000 | px;
						updateSprite(0, 16, 0, 0);
					}
					else {
						sprites[0].attribute1 = 0x4000 | 0x1000 | px;
						updateSprite(0, 24, 0, 0);
					}
					py--;
					hrt_SetOBJXY(&sprites[0], px, py);
					hrt_CopyOAM();
					dir = 1;
				}
                u32 temp = frames;
                s8 Phase;
                REG_BLDCNT = 0x00F7;
				door = mmEffectEx(&enter);
                for (Phase = 0; Phase < 17; Phase++) {
                    i=2;
                    REG_BLDY = Phase;
                    while (i--) {
                        hrt_VblankIntrWait();
                    }
                }
                level++;
                memcpy(VRAM, l1Bitmap, 76800);
                px = 112, py = 136;
                hrt_SetOBJXY(&sprites[0], px, py);
                hrt_CopyOAM();
				musici = 416;
                for (Phase = 0; Phase < 17; Phase++) {
                    i = 2;
                    REG_BLDY = 16-Phase;
                    while (i--) {
                        hrt_VblankIntrWait();
                        tstsndcmp(1, 416);
                    }
                }
                tiley--;
                sprites[0].attribute1 = 0x4000 | px;
                updateSprite(0, 16, 0, 0);
                frames = 0;
                for (i = 0; i < 64; i++) {
                    dir = 1;
                    if ((py == 8)OR(hrt_GetPixelInMode3(px, py - 1) == 0x0000)) {
                        tiley++;
                        break;
                    }
                    if ((level == 6)AND(tilex == 9)AND(tiley == 6)AND(l4s == 0)) {
                        tiley++;
                        break;
                    }
                    hrt_VblankIntrWait();
                    tstsndcmp(1, 416);
                    udframe++;
                    if (!(udframe % 8)) {
                        anim++;
                        if (anim >= 4) {
                            anim = 0;
                        }
                    }
                    if (anim == 0) {
                        sprites[0].attribute1 = 0x4000 | px;
                        sprites[0].attribute2 = 512 + 16;
                    }
                    else if (anim == 1) {
                        sprites[0].attribute1 = 0x4000 | px;
                        sprites[0].attribute2 = 512 + 24;
                    }
                    else if (anim == 2) {
                        sprites[0].attribute1 = 0x4000 | px;
                        sprites[0].attribute2 = 512 + 16;
                    }
                    else {
                        sprites[0].attribute1 = 0x4000 | 0x1000 | px;
                        sprites[0].attribute2 = 512 + 24;
                    }
                    py--;
                    hrt_SetOBJXY(&sprites[0], px, py);
                    hrt_CopyOAM();
                    dir = 1;
                }
                i = 60;
                while (i--) {
                    hrt_VblankIntrWait();
                    tstsndcmp(1, 416);
                }
                glidetime(1, 128 + 16, -8, 102, 24, 2);
                i = 60;
                while (i--) {
                    hrt_VblankIntrWait();
                    tstsndcmp(1, 416);
                }
                level = 1;
                memcpy(VRAM, l1bBitmap, 76800);
				sprites[2].attribute0 = COLOR_256 | SQUARE | 160;
				sprites[2].attribute1 = SIZE_8 | 240;
				sprites[2].attribute2 = 512 + 88;
				while (!(keyDown(KEY_A))) {
					hrt_VblankIntrWait();
					tstsndcmp(1, 416);
					if (keyDown(KEY_LEFT)) {
						arpos = 0;
					}
					if (keyDown(KEY_RIGHT)) {
						arpos = 1;
					}
					if (arpos == 0) {
						hrt_SetOBJXY(&sprites[2], 76, 136);
					}
					else {
						hrt_SetOBJXY(&sprites[2], 128, 136);
					}
					hrt_CopyOAM();
				}
				if (arpos == 1)
				{
					die();
				}
                while (keyDown(KEY_A)) {
                    hrt_VblankIntrWait();
                    tstsndcmp(1, 416);
                }
				hrt_SetOBJXY(&sprites[2], 240, 160);
                memcpy(VRAM, l1cBitmap, 76800);
                while (!(keyDown(KEY_A))) {
                    hrt_VblankIntrWait();
                    tstsndcmp(1, 416);
                }
                while (keyDown(KEY_A)) {
                    hrt_VblankIntrWait();
                    tstsndcmp(1, 416);
                }
                for (Phase = 0; Phase < 17; Phase++) {
                    i = 2;
                    REG_BLDY = Phase;
                    while (i--) {
                        hrt_VblankIntrWait();
                        tstsndcmp(1, 416);
                    }
                }
                px = 104, py = 8;
                hrt_SetOBJXY(&sprites[1], 240, 160);
                hrt_SetOBJXY(&sprites[0], px, py);
                memcpy(VRAM, l2Bitmap, 76800);
                sprites[0].attribute1 = 0x4000 | px;
                sprites[0].attribute2 = 512 + 32;
                tilex = 5, tiley = 1;
                dir = 2;
                hrt_CopyOAM();
                memcpy(VRAM, l2Bitmap, 76800);
                for (Phase = 0; Phase < 17; Phase++) {
                    i = 2;
                    REG_BLDY = 16-Phase;
                    while (i--) {
                        hrt_VblankIntrWait();
                        tstsndcmp(1, 416);
                    }
                }
                i = 60;
                while (i--) {
                    hrt_VblankIntrWait();
                    tstsndcmp(1, 416);
                }
                memcpy(VRAM, l2bBitmap, 76800);
				sprites[2].attribute0 = COLOR_256 | SQUARE | 160;
				sprites[2].attribute1 = SIZE_8 | 240;
				sprites[2].attribute2 = 512 + 88;
				while (!(keyDown(KEY_A))) {
					hrt_VblankIntrWait();
					tstsndcmp(1, 416);
					if (keyDown(KEY_LEFT)) {
						arpos = 0;
					}
					if (keyDown(KEY_RIGHT)) {
						arpos = 1;
					}
					if (arpos == 0) {
						hrt_SetOBJXY(&sprites[2], 76, 136);
					}
					else {
						hrt_SetOBJXY(&sprites[2], 128, 136);
					}
					hrt_CopyOAM();
				}
				if (arpos == 1)
				{
					die();
				}
				hrt_SetOBJXY(&sprites[2], 240, 160);
                while (keyDown(KEY_A)) {
                    hrt_VblankIntrWait();
                    tstsndcmp(1, 416);
                }
                memcpy(VRAM, l2Bitmap, 76800);
                level = 2;
            }
        }
        else if (level == 2) {
            if ((tilex == 3)AND(tiley == 2)) {
                die();
                return 0;
            }
            if ((tilex == 8)AND(tiley == 2)) {
				door = mmEffectEx(&enter);
                for (Phase = 0; Phase < 17; Phase++) {
                    i = 2;
                    REG_BLDY = Phase;
                    while (i--) {
                        hrt_VblankIntrWait();
                        tstsndcmp(1, 416);
                    }
                }
                tilex = 1, tiley = 5;
                px = 40, py = 72;
                initSprite(2, 0x4000, 104);
                hrt_SetOBJXY(&sprites[2], 184, 56);
                dir = 0;
                memcpy(VRAM, l3Bitmap, 76800);
                hrt_DrawLine(120, 104, 135, 104, 0x0000, 3);
                sprites[0].attribute1 = 0x4000 | px;
                sprites[0].attribute2 = 512;
                hrt_SetOBJXY(&sprites[0], px, py);
                hrt_CopyOAM();
                for (Phase = 0; Phase < 17; Phase++) {
                    i = 2;
                    REG_BLDY = 16-Phase;
                    while (i--) {
                        hrt_VblankIntrWait();
                        tstsndcmp(1, 416);
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
        }
        else if (level == 3) {
            if ((tilex == 10)AND(tiley == 4)) {
                key = 1;
                hrt_SetOBJXY(&sprites[2], 240, 160);
            }
            if ((tilex == 1)AND(tiley == 7)) {
                if ((keyDown(KEY_A))AND(l3s == 0)) {
                    while (keyDown(KEY_A)) {
                        hrt_VblankIntrWait();
                        tstsndcmp(1, 416);
                    }
                    hrt_SetOBJXY(&sprites[0], 240, 160);
                    hrt_CopyOAM();
                    memcpy(VRAM, l3bBitmap, 76800);
                    while (!(keyDown(KEY_A))) {
                        hrt_VblankIntrWait();
                        tstsndcmp(1, 416);
                    }
                    memcpy(VRAM, l3cBitmap, 76800);
                    hrt_DrawLine(120, 104, 135, 104, 0x0000, 3);
                    l3s = 1;
                }
            }
            if ((key == 1)AND(keys==0)) {
                memcpy(VRAM, l3cBitmap, 76800);
				hrt_DrawLine(120, 104, 135, 104, 0x0000, 3);
                keys = 1;
            }
            if ((tilex == 9)AND(tiley == 8)) {
                die();
                return 0;
            }
			if ((px == 120)AND(py == 88))
			{
				if (keyDown(KEY_DOWN))
				{
					usekey = mmEffectEx(&keyuse);
					memcpy(VRAM, l3dBitmap, 76800);
				}
			}
            if ((tilex == 3)AND(tiley == 8)) {
				door = mmEffectEx(&enter);
                for (Phase = 0; Phase < 17; Phase++) {
                    i = 2;
                    REG_BLDY = Phase;
                    while (i--) {
                        hrt_VblankIntrWait();
                        tstsndcmp(1, 416);
                    }
                }
                tilex = 6, tiley = 5;
                px = 120, py = 72;
                dir = 3;
                hrt_SetOBJXY(&sprites[0], px, py);
                hrt_CopyOAM();
                level++;
                memcpy(VRAM, l4Bitmap, 76800);
                for (Phase = 0; Phase < 17; Phase++) {
                    i = 2;
                    REG_BLDY = 16 - Phase;
                    while (i--) {
                        hrt_VblankIntrWait();
                        tstsndcmp(1, 416);
                    }
                }
                i = 60;
                while (i--) {
                    hrt_VblankIntrWait();
                    tstsndcmp(1, 416);
                }
                glidetime(1, 128 + 16, -8, 63, 50, 2);
                i = 5;
                while (i--) {
                    hrt_VblankIntrWait();
                    tstsndcmp(1, 416);
                }
                sprites[1].attribute2 = 512+72;
                hrt_CopyOAM();
                i = 30;
                while (i--) {
                    hrt_VblankIntrWait();
                    tstsndcmp(1, 416);
                }
                memcpy(VRAM, l4bBitmap, 76800);
                i = 25;
                while (i--) {
                    hrt_VblankIntrWait();
                    tstsndcmp(1, 416);
                }
                sprites[2].attribute0 = COLOR_256 | SQUARE | 160;
                sprites[2].attribute1 = SIZE_8 | 240;
                sprites[2].attribute2 = 512 + 88;
                while (!(keyDown(KEY_A))) {
                    hrt_VblankIntrWait();
                    tstsndcmp(1, 416);
                    if (keyDown(KEY_LEFT)) {
                        arpos = 0;
                    }
                    if (keyDown(KEY_RIGHT)) {
                        arpos = 1;
                    }
                    if (arpos == 0) {
                        hrt_SetOBJXY(&sprites[2], 76, 136);
                    }
                    else {
                        hrt_SetOBJXY(&sprites[2], 128, 136);
                    }
                    hrt_CopyOAM();
                }
                if (arpos == 0) {
					sav = mmEffectEx(&save);
                    hrt_SaveByte(0, level*10);
                }
                memcpy(VRAM, l4Bitmap, 76800);
                initSprite(2, 0x4000, 64);
                hrt_SetOBJXY(&sprites[2], 152, 121);
                rot = 0;
                for (i = 256; i < 1764; i+=15) {
                    rot+=15;
                    hrt_VblankIntrWait();
                    tstsndcmp(1, 416);
                    hrt_AffineOBJ(1, rot, i, i);
                    hrt_CopyOAM();
                }
                hrt_SetOBJXY(&sprites[1], 240, 160);
            }
        }
        else if (level == 4) {
            if ((tilex == 7)AND(tiley == 8)AND(keyDown(KEY_A))AND(l4s == 0)) {
				door = mmEffectEx(&enter);
                glidetime(2, 152, 121, 169, 121, 2);
                hrt_DrawLine(169, 121, 169, 137, 0x0000,3);
                l4s = 1;
            }
            if ((tilex == 8)AND(tiley == 7)) {
				door = mmEffectEx(&enter);
                for (Phase = 0; Phase < 17; Phase++) {
                    REG_BLDY = Phase;
                    i = 2;
                    while (i--) {
                        hrt_VblankIntrWait();
                        tstsndcmp(1, 416);
                    }
                }
                hrt_SetOBJXY(&sprites[2], 240, 160);
                memcpy(VRAM, l5Bitmap, 76800);
                tilex = 1, tiley = 6;
                px = 40, py = 88;
                dir = 0;
                updateSprite(0, 0, 0, 0);
                level++;
                hrt_SetOBJXY(&sprites[0], px, py);
                hrt_CopyOAM();
                for (Phase = 0; Phase < 17; Phase++) {
                    i = 2;
                    REG_BLDY = 16-Phase;
                    while (i--) {
                        hrt_VblankIntrWait();
                        tstsndcmp(1, 416);
                    }
                }
            }
            if ((tilex == 6)AND(tiley == 1)) {
                die();
                return 0;
            }
        }
        else if (level == 5) {
            if ((tilex == 5)AND(tiley == 3)AND(keyDown(KEY_A))) {
                while (keyDown(KEY_A)) {
                    hrt_VblankIntrWait();
                    tstsndcmp(1, 416);
                }
                hrt_CopyOAM();
                memcpy(VRAM, l5bBitmap, 76800);
                while (!(keyDown(KEY_A))) {
                    hrt_VblankIntrWait();
                    tstsndcmp(1, 416);
                }
                memcpy(VRAM, l5Bitmap, 76800);
                while (keyDown(KEY_A)) {
                    hrt_VblankIntrWait();
                    tstsndcmp(1, 416);
                }
            }
            if ((tilex == 10)AND(tiley == 3)) {
				door = mmEffectEx(&enter);
                for (Phase = 0; Phase < 17; Phase++) {
                    i = 2;
                    REG_BLDY = Phase;
                    while (i--) {
                        hrt_VblankIntrWait();
                        tstsndcmp(1, 416);
                    }
                }
                memcpy(VRAM, l6Bitmap, 76800);
                initSprite(2, 0x4000, 96);
                hrt_SetOBJXY(&sprites[2], 168, 72);
                tilex = 1, tiley = 5;
                px = 40, py = 72;
                dir = 0;
                updateSprite(0, 0, 0, 0);
                level++;
                l4s = 0;
                hrt_DrawLine(168, 87, 184, 87, 0x0000,3);
                hrt_SetOBJXY(&sprites[0], px, py);
                hrt_CopyOAM();
                for (Phase = 0; Phase < 17; Phase++) {
                    i = 2;
                    REG_BLDY = 16 - Phase;
                    while (i--) {
                        hrt_VblankIntrWait();
                        tstsndcmp(1, 416);
                    }
                }
            }
        }
        else if (level == 6) {
            if ((tilex == 9)AND(tiley == 6)AND(keyDown(KEY_A))AND(l4s == 0)) {
                memcpy(VRAM, l6Bitmap, 76800);
				door = mmEffectEx(&enter);
                glidetime(2, 168, 72, 168, 55, 2);
                hrt_DrawLine(168, 71, 184, 71, 0x0000,3);
                l4s = 1;
            }
            if ((tilex == 10)AND(tiley == 5)) {
				door = mmEffectEx(&enter);
                for (Phase = 0; Phase < 17; Phase++) {
                    i = 2;
                    REG_BLDY = Phase;
                    while (i--) {
                        hrt_VblankIntrWait();
                        tstsndcmp(1, 416);
                    }
                }
                memcpy(VRAM, l7Bitmap, 76800);
                tilex = 6, tiley = 9;
                px = 120, py = 136;
                dir = 0;
                updateSprite(0, 0, 0, 0);
                level++;
                l4s = 0;
                hrt_SetOBJXY(&sprites[0], px, py);
                hrt_CopyOAM();
                for (Phase = 0; Phase < 17; Phase++) {
                    i = 2;
                    REG_BLDY = 16 - Phase;
                    while (i--) {
                        hrt_VblankIntrWait();
                        tstsndcmp(1, 416);
                    }
                }
            }
        }
        else if (level == 7) {
            if ((tilex == 5)AND(tiley == 3)) {
				door = mmEffectEx(&enter);
                for (Phase = 0; Phase < 17; Phase++) {
                    i = 2;
                    REG_BLDY = Phase;
                    while (i--) {
                        hrt_VblankIntrWait();
                        tstsndcmp(1, 416);
                    }
                }
                memcpy(VRAM, l8Bitmap, 76800);
                tilex = 5, tiley = 9;
                hrt_SetOBJXY(&sprites[2], 240, 160);
                px = 104, py = 136;
                dir = 0;
                sprites[0].attribute1 = 0x4000 | px;
                updateSprite(0, 16, 0, 0);
                level++;
                l4s = 0;
                hrt_SetOBJXY(&sprites[0], px, py);
                hrt_AffineOBJ(1, 0, 256, 256);
                hrt_CopyOAM();
                for (Phase = 0; Phase < 17; Phase++) {
                    i = 2;
                    REG_BLDY = 16 - Phase;
                    while (i--) {
                        hrt_VblankIntrWait();
                        tstsndcmp(1, 416);
                    }
                }
                sprites[1].attribute2 = 512 + 48; // NOTE: mode4 doesn't support the first tiles, so offset of 512 is requirerd
                glidetime(1, 128 + 16, -8, 96, 50, 2);
                i = 5;
                while (i--) {
                    hrt_VblankIntrWait();
                    tstsndcmp(1, 416);
                }
                memcpy(VRAM, l8bBitmap, 76800);
                sprites[2].attribute0 = COLOR_256 | SQUARE | 160;
                sprites[2].attribute1 = SIZE_8 | 240;
                sprites[2].attribute2 = 512 + 88;
                hrt_SetOBJXY(&sprites[0], 240, 160);
				arpos = 0;
                while (!(keyDown(KEY_A))) {
                    hrt_VblankIntrWait();
                    tstsndcmp(1, 416);
                    if (keyDown(KEY_LEFT)) {
                        arpos = 0;
                    }
                    if (keyDown(KEY_RIGHT)) {
                        arpos = 1;
                    }
                    if (arpos == 0) {
                        hrt_SetOBJXY(&sprites[2], 76, 136);
                    }
                    else {
                        hrt_SetOBJXY(&sprites[2], 128, 136);
                    }
                    hrt_CopyOAM();
                }
                if (arpos == 0) {
					sav = mmEffectEx(&save);
                    hrt_SaveByte(0, level*10);
                }
                memcpy(VRAM, l8Bitmap, 76800);
                hrt_SetOBJXY(&sprites[2], 240, 160);
                hrt_SetOBJXY(&sprites[0], px, py);
                rot = 0;
                for (i = 256; i < 1764; i += 15) {
                    rot += 15;
                    hrt_VblankIntrWait();
                    tstsndcmp(1, 416);
                    hrt_AffineOBJ(1, rot, i, i);
                    hrt_CopyOAM();
                }
                hrt_SetOBJXY(&sprites[1], 240, 160);
            }
        }
        else if (level == 8) {
            if (hrt_GetPixelInMode3(px, py) == 0x7ea0) {
                if ((tilex == 4)AND(tiley == 2)) {
					door = mmEffectEx(&enter);
                    for (Phase = 0; Phase < 17; Phase++) {
                        i = 2;
                        REG_BLDY = Phase;
                        while (i--) {
                            hrt_VblankIntrWait();
                            tstsndcmp(1, 416);
                        }
                    }
                    tilex = 5, tiley = 9;
                    px = 104, py = 136;
                    dir = 0;
                    memcpy(VRAM, l9Bitmap, 76800);
                    sprites[0].attribute1 = 0x4000 | px;
                    updateSprite(0, 0, 0, 0);
                    hrt_SetOBJXY(&sprites[0], px, py);
                    hrt_CopyOAM();
                    for (Phase = 0; Phase < 17; Phase++) {
                        i = 2;
                        REG_BLDY = 16 - Phase;
                        while (i--) {
                            hrt_VblankIntrWait();
                            tstsndcmp(1, 416);
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
        else if (level == 9) {
            if (hrt_GetPixelInMode3(px, py) == 0x7ea0) {
                if ((tilex == 1)AND(tiley == 3)) {
					door = mmEffectEx(&enter);
                    for (Phase = 0; Phase < 17; Phase++) {
                        i = 2;
                        REG_BLDY = Phase;
                        while (i--) {
                            hrt_VblankIntrWait();
                            tstsndcmp(1, 416);
                        }
                    }
                    tilex = 5, tiley = 9;
                    px = 112, py = 136;
                    dir = 0;
                    hrt_SetOBJXY(&sprites[0], px, py);
                    hrt_CopyOAM();
                    memcpy(VRAM, l10Bitmap, 76800);
                    sprites[0].attribute1 = 0x4000 | px;
                    updateSprite(0, 0, 0, 0);
                    for (Phase = 0; Phase < 17; Phase++) {
                        i = 2;
                        REG_BLDY = 16 - Phase;
                        while (i--) {
                            hrt_VblankIntrWait();
                            tstsndcmp(1, 416);
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
        else if (level == 10) {
            if ((tilex == 5)AND(tiley == 2)) {
                if (keyDown(KEY_A)) {
                    memcpy(VRAM, l10bBitmap, 76800);
					sprites[2].attribute0 = COLOR_256 | SQUARE | 160;
					sprites[2].attribute1 = SIZE_8 | 240;
					sprites[2].attribute2 = 512 + 88;
					arpos = 0;
					while (keyDown(KEY_A)) {
						hrt_VblankIntrWait();
						tstsndcmp(1, 416);
					}
					while (!(keyDown(KEY_A))) {
						hrt_VblankIntrWait();
						tstsndcmp(1, 416);
						if (keyDown(KEY_LEFT)) {
							arpos = 0;
						}
						if (keyDown(KEY_RIGHT)) {
							arpos = 1;
						}
						if (arpos == 0) {
							hrt_SetOBJXY(&sprites[2], 76, 136);
						}
						else {
							hrt_SetOBJXY(&sprites[2], 128, 136);
						}
						hrt_CopyOAM();
					}
					while (keyDown(KEY_A)) {
						hrt_VblankIntrWait();
						tstsndcmp(1, 416);
					}
					hrt_SetOBJXY(&sprites[2], 240, 160);
                    if (arpos == 0) {
                        memcpy(VRAM, l10cBitmap, 76800);
                        while (keyDown(KEY_A)) {
                            hrt_VblankIntrWait();
                            tstsndcmp(1, 416);
                        }
                        while (!(keyDown(KEY_A))) {
                            hrt_VblankIntrWait();
                            tstsndcmp(1, 416);
                        }
						memcpy(VRAM, l10eBitmap, 76800);
                        die();
                        return 0;
                    }
                    else {
                        memcpy(VRAM, l10dBitmap, 76800);
                        while (keyDown(KEY_A)) {
                            hrt_VblankIntrWait();
                            tstsndcmp(1, 416);
                        }
                        while (!(keyDown(KEY_A))) {
                            hrt_VblankIntrWait();
                            tstsndcmp(1, 416);
                        }
                        for (Phase = 0; Phase < 17; Phase++) {
                            i = 2;
                            REG_BLDY = Phase;
                            while (i--) {
                                hrt_VblankIntrWait();
                                tstsndcmp(1, 416);
                            }
                        }
                        tilex = 6, tiley = 9;
                        px = 120, py = 136;
                        dir = 1;
                        memcpy(VRAM, l11Bitmap, 76800);
                        sprites[0].attribute1 = 0x4000 | px;
                        updateSprite(0, 16, 0, 0);
                        hrt_SetOBJXY(&sprites[0], px, py);
                        hrt_CopyOAM();
                        for (Phase = 0; Phase < 17; Phase++) {
                            i = 2;
                            REG_BLDY = 16 - Phase;
                            while (i--) {
                                hrt_VblankIntrWait();
                                tstsndcmp(1, 416);
                            }
                        }
                        level++;
                    }
                }
            }
        }
        else if (level == 11) {
            if (hrt_GetPixelInMode3(px, py) == 0x7ea0) {
                if ((tilex == 6)AND(tiley == 2)) {
					door = mmEffectEx(&enter);
                    for (Phase = 0; Phase < 17; Phase++) {
                        i = 2;
                        REG_BLDY = Phase;
                        while (i--) {
                            hrt_VblankIntrWait();
                            tstsndcmp(1, 416);
                        }
                    }
                    tilex = 5, tiley = 4;
                    px = 104, py = 56;
                    dir = 0;
                    hrt_SetOBJXY(&sprites[0], px, py);
                    hrt_CopyOAM();
                    memcpy(VRAM, l12Bitmap, 76800);
                    sprites[0].attribute1 = 0x4000 | px;
                    updateSprite(0, 0, 0, 0);
                    hrt_SetOBJXY(&sprites[0], px, py);
                    hrt_CopyOAM();
                    for (Phase = 0; Phase < 17; Phase++) {
                        i = 2;
                        REG_BLDY = 16 - Phase;
                        while (i--) {
                            hrt_VblankIntrWait();
                            tstsndcmp(1, 416);
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
        else if (level == 12) {
            if (hrt_GetPixelInMode3(px, py) == 0x7ea0) {
                if ((tilex == 9)AND(tiley == 4)) {
					door = mmEffectEx(&enter);
                    for (Phase = 0; Phase < 17; Phase++) {
                        i = 2;
                        REG_BLDY = Phase;
                        while (i--) {
                            hrt_VblankIntrWait();
                            tstsndcmp(1, 416);
                        }
                    }
                    tilex = 6, tiley = 5;
                    px = 120, py = 72;
                    dir = 0;
                    memcpy(VRAM, l13Bitmap, 76800);
                    sprites[0].attribute1 = 0x4000 | px;
                    updateSprite(0, 0, 0, 0);
                    hrt_SetOBJXY(&sprites[0], px, py);
                    hrt_CopyOAM();
                    for (Phase = 0; Phase < 17; Phase++) {
                        i = 2;
                        REG_BLDY = 16 - Phase;
                        while (i--) {
                            hrt_VblankIntrWait();
                            tstsndcmp(1, 416);
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
        else if (level == 13) {
            if (hrt_GetPixelInMode3(px, py) == 0x7ea0) {
                if ((tilex == 10)AND(tiley == 7)) {
					door = mmEffectEx(&enter);
                    for (Phase = 0; Phase < 17; Phase++) {
                        i = 2;
                        REG_BLDY = Phase;
                        while (i--) {
                            hrt_VblankIntrWait();
                            tstsndcmp(1, 416);
                        }
                    }
                    tilex = 1, tiley = 5;
                    px = 40, py = 72;
                    dir = 0;
                    memcpy(VRAM, l14Bitmap, 76800);
                    sprites[0].attribute1 = 0x4000 | px;
                    updateSprite(0, 0, 0, 0);
                    hrt_SetOBJXY(&sprites[0], px, py);
                    hrt_CopyOAM();
                    for (Phase = 0; Phase < 17; Phase++) {
                        i = 2;
                        REG_BLDY = 16 - Phase;
                        while (i--) {
                            hrt_VblankIntrWait();
                            tstsndcmp(1, 416);
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
        else if (level == 14) {
            if (hrt_GetPixelInMode3(px, py) == 0x7ea0) {
                if ((tilex == 2)AND(tiley == 9)) {
					door = mmEffectEx(&enter);
                    for (Phase = 0; Phase < 17; Phase++) {
                        i = 2;
                        REG_BLDY = Phase;
                        while (i--) {
                            hrt_VblankIntrWait();
                            tstsndcmp(1, 416);
                        }
                    }
                    tilex = 10, tiley = 6;
                    px = 184, py = 88;
                    dir = 3;
                    memcpy(VRAM, l15Bitmap, 76800);
                    sprites[0].attribute1 = 0x4000 | 0x1000 | px;
                    updateSprite(0, 0, 0, 0);
                    hrt_SetOBJXY(&sprites[0], px, py);
                    hrt_CopyOAM();
                    for (Phase = 0; Phase < 17; Phase++) {
                        i = 2;
                        REG_BLDY = 16 - Phase;
                        while (i--) {
                            hrt_VblankIntrWait();
                            tstsndcmp(1, 416);
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
        else if (level == 15) {
            if (hrt_GetPixelInMode3(px, py) == 0x7ea0) {
                if ((tilex == 1)AND(tiley == 6)) {
					door = mmEffectEx(&enter);
                    for (Phase = 0; Phase < 17; Phase++) {
                        i = 2;
                        REG_BLDY = Phase;
                        while (i--) {
                            hrt_VblankIntrWait();
                            tstsndcmp(1, 416);
                        }
                    }
                    tilex = 7, tiley = 1;
                    px = 136, py = 8;
                    dir = 2;
                    memcpy(VRAM, l16Bitmap, 76800);
                    sprites[0].attribute1 = 0x4000 | px;
                    updateSprite(0, 32, 0, 0);
                    hrt_SetOBJXY(&sprites[0], px, py);
                    hrt_CopyOAM();
                    for (Phase = 0; Phase < 17; Phase++) {
                        i = 2;
                        REG_BLDY = 16 - Phase;
                        while (i--) {
                            hrt_VblankIntrWait();
                            tstsndcmp(1, 416);
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
        else if (level == 16) {
            if (hrt_GetPixelInMode3(px, py) == 0x7ea0) {
                if ((tilex == 5)AND(tiley == 1)) {
					door = mmEffectEx(&enter);
                    for (Phase = 0; Phase < 17; Phase++) {
                        i = 2;
                        REG_BLDY = Phase;
                        while (i--) {
                            hrt_VblankIntrWait();
                            tstsndcmp(1, 416);
                        }
                    }
                    tilex = 6, tiley = 7;
                    px = 120, py = 104;
                    dir = 0;
                    memcpy(VRAM, l17Bitmap, 76800);
                    sprites[0].attribute1 = 0x4000 | px;
                    updateSprite(0, 16, 0, 0);
                    hrt_SetOBJXY(&sprites[0], px, py);
                    hrt_CopyOAM();
                    for (Phase = 0; Phase < 17; Phase++) {
                        i = 2;
                        REG_BLDY = 16 - Phase;
                        while (i--) {
                            hrt_VblankIntrWait();
                            tstsndcmp(1, 416);
                        }
                    }
                    level++;
                    i = 60;
                    while (i--) {
                        hrt_VblankIntrWait();
                        tstsndcmp(1, 416);
                    }
                    hrt_AffineOBJ(1, 0, 256, 256);
                    glidetime(1, 240, 160, 112, 50, 2);
                    i = 5;
                    while (i--) {
                        hrt_VblankIntrWait();
                        tstsndcmp(1, 416);
                    }
                    memcpy(VRAM, l17bBitmap, 76800);
                    sprites[2].attribute0 = COLOR_256 | SQUARE | 160;
                    sprites[2].attribute1 = SIZE_8 | 240;
                    sprites[2].attribute2 = 512 + 88;
                    hrt_SetOBJXY(&sprites[0], 240, 160);
                    while (!(keyDown(KEY_A))) {
                        hrt_VblankIntrWait();
                        tstsndcmp(1, 416);
                        if (keyDown(KEY_LEFT)) {
                            arpos = 0;
                        }
                        if (keyDown(KEY_RIGHT)) {
                            arpos = 1;
                        }
                        if (arpos == 0) {
                            hrt_SetOBJXY(&sprites[2], 76, 136);
                        }
                        else {
                            hrt_SetOBJXY(&sprites[2], 128, 136);
                        }
                        hrt_CopyOAM();
                    }
                    if (arpos == 0) {
						sav = mmEffectEx(&save);
                        hrt_SaveByte(0, level);
                    }
                    memcpy(VRAM, l17Bitmap, 76800);
                    hrt_SetOBJXY(&sprites[2], 240, 160);
                    hrt_SetOBJXY(&sprites[0], px, py);
                    rot = 0;
                    for (i = 256; i < 1764; i += 15) {
                        rot += 15;
                        hrt_VblankIntrWait();
                        tstsndcmp(1, 416);
                        hrt_AffineOBJ(1, rot, i, i);
                        hrt_CopyOAM();
                    }
                    hrt_SetOBJXY(&sprites[1], 240, 160);
                }
                else {
                    die();
                    return 0;
                }
            }
        }
        else if (level == 17) {
            if (hrt_GetPixelInMode3(px, py) == 0x7ea0) {
                if ((tilex == 3)AND(tiley == 3)) {
					door = mmEffectEx(&enter);
                    for (Phase = 0; Phase < 17; Phase++) {
                        i = 2;
                        REG_BLDY = Phase;
                        while (i--) {
                            hrt_VblankIntrWait();
                            tstsndcmp(1, 416);
                        }
                    }
                    tilex = 5, tiley = 5;
                    px = 104, py = 72;
                    dir = 2;
                    memcpy(VRAM, l18Bitmap, 76800);
                    sprites[0].attribute1 = 0x4000 | px;
                    updateSprite(0, 0, 0, 0);
                    hrt_SetOBJXY(&sprites[0], px, py);
                    hrt_CopyOAM();
                    for (Phase = 0; Phase < 17; Phase++) {
                        i = 2;
                        REG_BLDY = 16 - Phase;
                        while (i--) {
                            hrt_VblankIntrWait();
                            tstsndcmp(1, 416);
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
        else if (level == 18) {
            if (hrt_GetPixelInMode3(px, py) == 0x7ea0) {
                if ((tilex == 7)AND(tiley == 8)) {
					door = mmEffectEx(&enter);
                    for (Phase = 0; Phase < 17; Phase++) {
                        i = 2;
                        REG_BLDY = Phase;
                        while (i--) {
                            hrt_VblankIntrWait();
                            tstsndcmp(1, 416);
                        }
                    }
                    tilex = 6, tiley = 1;
                    px = 120, py = 8;
                    dir = 2;
                    memcpy(VRAM, l19Bitmap, 76800);
                    sprites[0].attribute1 = 0x4000 | px;
                    updateSprite(0, 32, 0, 0);
                    hrt_SetOBJXY(&sprites[0], px, py);
                    hrt_CopyOAM();
                    for (Phase = 0; Phase < 17; Phase++) {
                        i = 2;
                        REG_BLDY = 16 - Phase;
                        while (i--) {
                            hrt_VblankIntrWait();
                            tstsndcmp(1, 416);
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
        else if (level == 19) {
            if (hrt_GetPixelInMode3(px, py) == 0x7ea0) {
                if ((tilex == 1)AND(tiley == 7)) {
					door = mmEffectEx(&enter);
                    for (Phase = 0; Phase < 17; Phase++) {
                        i = 2;
                        REG_BLDY = Phase;
                        while (i--) {
                            hrt_VblankIntrWait();
                            tstsndcmp(1, 416);
                        }
                    }
                    tilex = 4, tiley = 6;
                    px = 88, py = 88;
                    dir = 0;
                    memcpy(VRAM, l20Bitmap, 76800);
                    sprites[0].attribute1 = 0x4000 | px;
                    updateSprite(0, 0, 0, 0);
                    hrt_SetOBJXY(&sprites[0], px, py);
                    hrt_CopyOAM();
                    for (Phase = 0; Phase < 17; Phase++) {
                        i = 2;
                        REG_BLDY = 16 - Phase;
                        while (i--) {
                            hrt_VblankIntrWait();
                            tstsndcmp(1, 416);
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
        else if (level == 20) {
            if (hrt_GetPixelInMode3(px, py) == 0x7ea0) {
                if ((tilex == 10)AND(tiley == 6)) {
					door = mmEffectEx(&enter);
                    for (Phase = 0; Phase < 17; Phase++) {
                        i = 2;
                        REG_BLDY = Phase;
                        while (i--) {
                            hrt_VblankIntrWait();
                            tstsndcmp(1, 416);
                        }
                    }
                    tilex = 2, tiley = 1;
                    px = 56, py = 8;
                    dir = 0;
                    memcpy(VRAM, l21Bitmap, 76800);
                    sprites[0].attribute1 = 0x4000 | px;
                    updateSprite(0, 0, 0, 0);
                    hrt_SetOBJXY(&sprites[0], px, py);
                    hrt_CopyOAM();
                    for (Phase = 0; Phase < 17; Phase++) {
                        i = 2;
                        REG_BLDY = 16 - Phase;
                        while (i--) {
                            hrt_VblankIntrWait();
                            tstsndcmp(1, 416);
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
        else if (level == 21) {
            if (hrt_GetPixelInMode3(px, py) == 0x7ea0) {
                if ((tilex == 8)AND(tiley == 4)) {
					door = mmEffectEx(&enter);
                    for (Phase = 0; Phase < 17; Phase++) {
                        i = 2;
                        REG_BLDY = Phase;
                        while (i--) {
                            hrt_VblankIntrWait();
                            tstsndcmp(1, 416);
                        }
                    }
                    tilex = 1, tiley = 1;
                    px =40, py = 8;
                    dir = 0;
                    memcpy(VRAM, l22Bitmap, 76800);
                    sprites[0].attribute1 = 0x4000 | px;
                    updateSprite(0, 0, 0, 0);
                    hrt_SetOBJXY(&sprites[0], px, py);
					hrt_offsetOAMData = 0;
					hrt_offsetOAMPal = 0;
					hrt_LoadOBJPal((void*)sprsdkPal, 256);
					hrt_LoadOBJGFX((void*)sprsdkTiles, 2048);
                    hrt_CopyOAM();
                    for (Phase = 0; Phase < 17; Phase++) {
                        i = 2;
                        REG_BLDY = 16 - Phase;
                        while (i--) {
                            hrt_VblankIntrWait();
                            tstsndcmp(1, 416);
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
        else if (level == 22) {
            if ((tilex == 4)AND(tiley = 1)) {
                if (keyDown(KEY_A)) {
                    while (keyDown(KEY_A)) {
                        hrt_VblankIntrWait();
                        tstsndcmp(1, 416);
                    }
                    hrt_CopyOAM();
                    memcpy(VRAM, l22bBitmap, 76800);
                    while (!(keyDown(KEY_A))) {
                        hrt_VblankIntrWait();
                        tstsndcmp(1, 416);
                    }
                    memcpy(VRAM, l22Bitmap, 76800);
                    while (keyDown(KEY_A)) {
                        hrt_VblankIntrWait();
                        tstsndcmp(1, 416);
                    }
                }
            }
            if (hrt_GetPixelInMode3(px, py) == 0x7ea0) {
                if ((tilex == 3)AND(tiley == 1)) {
					door = mmEffectEx(&enter);
                    for (Phase = 0; Phase < 17; Phase++) {
                        i = 2;
                        REG_BLDY = Phase;
                        while (i--) {
                            hrt_VblankIntrWait();
                            tstsndcmp(1, 416);
                        }
                    }
                    tilex = 4, tiley = 9;
                    px = 88, py = 136;
                    dir = 0;
                    memcpy(VRAM, l23Bitmap, 76800);
                    sprites[0].attribute1 = 0x4000 | px;
                    updateSprite(0, 0, 0, 0);
                    hrt_SetOBJXY(&sprites[0], px, py);
                    hrt_CopyOAM();
                    for (Phase = 0; Phase < 17; Phase++) {
                        i = 2;
                        REG_BLDY = 16 - Phase;
                        while (i--) {
                            hrt_VblankIntrWait();
                            tstsndcmp(1, 416);
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
        else if (level == 23) {
            if (hrt_GetPixelInMode3(px, py) == 0x7ea0) {
                if ((tilex == 10)AND(tiley == 7)) {
					door = mmEffectEx(&enter);
                    for (Phase = 0; Phase < 17; Phase++) {
                        i = 2;
                        REG_BLDY = Phase;
                        while (i--) {
                            hrt_VblankIntrWait();
                            tstsndcmp(1, 416);
                        }
                    }
                    tilex = 1, tiley = 1;
                    px = 40, py = 8;
                    dir = 0;
                    memcpy(VRAM, l24Bitmap, 76800);
                    sprites[0].attribute1 = 0x4000 | px;
                    updateSprite(0, 0, 0, 0);
                    hrt_SetOBJXY(&sprites[0], px, py);
                    hrt_CopyOAM();
                    for (Phase = 0; Phase < 17; Phase++) {
                        i = 2;
                        REG_BLDY = 16 - Phase;
                        while (i--) {
                            hrt_VblankIntrWait();
                            tstsndcmp(1, 416);
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
        else if (level == 24) {
            if (hrt_GetPixelInMode3(px, py) == 0x7ea0) {
                if ((tilex == 8)AND(tiley == 6)) {
					door = mmEffectEx(&enter);
                    for (Phase = 0; Phase < 17; Phase++) {
                        i = 2;
                        REG_BLDY = Phase;
                        while (i--) {
                            hrt_VblankIntrWait();
                            tstsndcmp(1, 416);
                        }
                    }
                    tilex = 1, tiley = 1;
                    px = 40, py = 8;
                    dir = 0;
                    memcpy(VRAM, l25Bitmap, 76800);
                    sprites[0].attribute1 = 0x4000 | px;
                    updateSprite(0, 0, 0, 0);
                    hrt_SetOBJXY(&sprites[0], px, py);
                    hrt_CopyOAM();
                    for (Phase = 0; Phase < 17; Phase++) {
                        i = 2;
                        REG_BLDY = 16 - Phase;
                        while (i--) {
                            hrt_VblankIntrWait();
                            tstsndcmp(1, 416);
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
        else if (level == 25) {
            if (hrt_GetPixelInMode3(px, py) == 0x7ea0) {
                if ((tilex == 7)AND(tiley == 7)) {
					door = mmEffectEx(&enter);
                    for (Phase = 0; Phase < 17; Phase++) {
                        i = 2;
                        REG_BLDY = Phase;
                        while (i--) {
                            hrt_VblankIntrWait();
                            tstsndcmp(1, 416);
                        }
                    }
                    tilex = 3, tiley = 9;
                    px = 72, py = 136;
                    dir = 0;
                    memcpy(VRAM, l26Bitmap, 76800);
                    sprites[0].attribute1 = 0x4000 | px;
                    updateSprite(0, 0, 0, 0);
                    hrt_SetOBJXY(&sprites[0], px, py);
                    hrt_CopyOAM();
                    for (Phase = 0; Phase < 17; Phase++) {
                        i = 2;
                        REG_BLDY = 16 - Phase;
                        while (i--) {
                            hrt_VblankIntrWait();
                            tstsndcmp(1, 416);
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
        else if (level == 26) {
            if (hrt_GetPixelInMode3(px, py) == 0x7ea0) {
                if ((tilex == 1)AND(tiley == 9)) {
					door = mmEffectEx(&enter);
                    for (Phase = 0; Phase < 17; Phase++) {
                        i = 2;
                        REG_BLDY = Phase;
                        while (i--) {
                            hrt_VblankIntrWait();
                            tstsndcmp(1, 416);
                        }
                    }
                    tilex = 5, tiley = 9;
                    px = 104, py = 136;
                    dir = 0;
                    memcpy(VRAM, l27Bitmap, 76800);
					hrt_offsetOAMData = 0;
					hrt_offsetOAMPal = 0;
                    hrt_LoadOBJPal((void*)sprsPal, 256);
                    hrt_LoadOBJGFX((void*)sprsTiles, 2048);
                    sprites[0].attribute1 = 0x4000 | px;
                    updateSprite(0, 16, 0, 0);
                    hrt_SetOBJXY(&sprites[0], px, py);
                    hrt_CopyOAM();
                    for (Phase = 0; Phase < 17; Phase++) {
                        i = 2;
                        REG_BLDY = 16 - Phase;
                        while (i--) {
                            hrt_VblankIntrWait();
                            tstsndcmp(1, 416);
                        }
                    }
                    level++;
                    i = 60;
                    while (i--) {
                        hrt_VblankIntrWait();
                        tstsndcmp(1, 416);
                    }
                    hrt_AffineOBJ(1, 0, 256, 256);
                    glidetime(1, 240, 160, 96, 50, 2);
                    i = 5;
                    while (i--) {
                        hrt_VblankIntrWait();
                        tstsndcmp(1, 416);
                    }
                    memcpy(VRAM, l27bBitmap, 76800);
                    sprites[2].attribute0 = COLOR_256 | SQUARE | 160;
                    sprites[2].attribute1 = SIZE_8 | 240;
                    sprites[2].attribute2 = 512 + 88;
                    hrt_SetOBJXY(&sprites[0], 240, 160);
                    while (!(keyDown(KEY_A))) {
                        hrt_VblankIntrWait();
                        tstsndcmp(1, 416);
                        if (keyDown(KEY_LEFT)) {
                            arpos = 0;
                        }
                        if (keyDown(KEY_RIGHT)) {
                            arpos = 1;
                        }
                        if (arpos == 0) {
                            hrt_SetOBJXY(&sprites[2], 76, 136);
                        }
                        else {
                            hrt_SetOBJXY(&sprites[2], 128, 136);
                        }
                        hrt_CopyOAM();
                    }
                    if (arpos == 0) {
						sav = mmEffectEx(&save);
                        hrt_SaveByte(0, level);
                    }
                    memcpy(VRAM, l27Bitmap, 76800);
                    hrt_SetOBJXY(&sprites[2], 240, 160);
                    hrt_SetOBJXY(&sprites[0], px, py);
                    rot = 0;
                    for (i = 256; i < 1764; i += 15) {
                        rot += 15;
                        hrt_VblankIntrWait();
                        tstsndcmp(1, 416);
                        hrt_AffineOBJ(1, rot, i, i);
                        hrt_CopyOAM();
                    }
                    hrt_SetOBJXY(&sprites[1], 240, 160);
                }
                else {
                    die();
                    return 0;
                }
            }
        }
        else if (level == 27) {
            if (hrt_GetPixelInMode3(px, py) == 0x7ea0) {
                if ((tilex == 1)AND(tiley == 1)) {
					door = mmEffectEx(&enter);
                    for (Phase = 0; Phase < 17; Phase++) {
                        i = 2;
                        REG_BLDY = Phase;
                        while (i--) {
                            hrt_VblankIntrWait();
                            tstsndcmp(1, 416);
                        }
                    }
                    tilex = 3, tiley = 9;
                    px = 72, py = 136;
                    dir = 0;
                    memcpy(VRAM, l28Bitmap, 76800);
                    sprites[0].attribute1 = 0x4000 | px;
                    updateSprite(0, 0, 0, 0);
                    hrt_SetOBJXY(&sprites[0], px, py);
                    hrt_CopyOAM();
                    for (Phase = 0; Phase < 17; Phase++) {
                        i = 2;
                        REG_BLDY = 16 - Phase;
                        while (i--) {
                            hrt_VblankIntrWait();
                            tstsndcmp(1, 416);
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
            if (hrt_GetPixelInMode3(px, py) == 0x7c14) {
                tilex = 6, tiley = 2;
                px = 120, py = 24;
            }
            if (hrt_GetPixelInMode3(px, py) == 0x7ea0) {
                if ((tilex == 3)AND(tiley == 1)) {
					door = mmEffectEx(&enter);
                    for (Phase = 0; Phase < 17; Phase++) {
                        i = 2;
                        REG_BLDY = Phase;
                        while (i--) {
                            hrt_VblankIntrWait();
                            tstsndcmp(1, 416);
                        }
                    }
                    tilex = 3, tiley = 9;
                    px = 72, py = 136;
                    dir = 0;
                    memcpy(VRAM, l29Bitmap, 76800);
                    hrt_DrawLine(120, 135, 136, 135, 0x0000,3);
                    sprites[0].attribute1 = 0x4000 | px;
                    updateSprite(0, 0, 0, 0);
                    hrt_SetOBJXY(&sprites[0], px, py);
                    hrt_CopyOAM();
                    for (Phase = 0; Phase < 17; Phase++) {
                        i = 2;
                        REG_BLDY = 16 - Phase;
                        while (i--) {
                            hrt_VblankIntrWait();
                            tstsndcmp(1, 416);
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
            if ((tilex == 3)AND(tiley == 9)) {
                if (keyDown(KEY_A)) {
					mmEffectCancelAll();
                    hrt_AffineOBJ(1, 0, 256, 256);
                    hrt_SleepF(60);
                    hrt_GlideSpritetoPos(1, 240, 0, px-16, py-16, 6);
                    hrt_SetDSPMode(3, //Mode
                                   0,								  //CGB Mode
                                   0,								  //Frame Select
                                   0,                               //Unlocked HBlank
                                   0,                               //Linear OBJ Tile Mapping
                                   0,                               //Force Blank
                                   0,                               //BG 0
                                   0,                               //BG 1
                                   1,                               //BG 2
                                   0,                               //BG 3
                                   0,                               //OBJ
                                   0,                               //Win 0
                                   0,                               //Win 1
                                   0);							  //OBJWin
                    FadeOut(0);
                    hrt_FillScreen(0x0000);
                    die();
                }
            }
            if ((tilex == 4)AND(tiley == 9)) {
                if (keyDown(KEY_A)) {
					if (l29k == 0)
					{
						usekey = mmEffectEx(&keyuse);
						memcpy(VRAM, l29bBitmap, 76800);
						l29k = 1;
					}
                }
            }
            if (hrt_GetPixelInMode3(px, py) == 0x7ea0) {
                if ((tilex == 10)AND(tiley == 4)) {
					door = mmEffectEx(&enter);
                    for (Phase = 0; Phase < 17; Phase++) {
                        i = 2;
                        REG_BLDY = Phase;
                        while (i--) {
                            hrt_VblankIntrWait();
                            tstsndcmp(1, 416);
                        }
                    }
                    tilex = 5, tiley = 9;
                    px = 104, py = 136;
                    dir = 0;
                    memcpy(VRAM, l30Bitmap, 76800);
                    sprites[0].attribute1 = 0x4000 | px;
                    updateSprite(0, 16, 0, 0);
                    hrt_SetOBJXY(&sprites[0], px, py);
                    hrt_CopyOAM();
                    for (Phase = 0; Phase < 17; Phase++) {
                        i = 2;
                        REG_BLDY = 16 - Phase;
                        while (i--) {
                            hrt_VblankIntrWait();
                            tstsndcmp(1, 416);
                        }
                    }
                    level++;
                    i = 60;
                    while (i--) {
                        hrt_VblankIntrWait();
                        tstsndcmp(1, 416);
                    }
                    hrt_AffineOBJ(1, 0, 256, 256);
                    glidetime(1, 240, 160, 96, 50, 2);
                    i = 5;
                    while (i--) {
                        hrt_VblankIntrWait();
                        tstsndcmp(1, 416);
                    }
                    memcpy(VRAM, l30cBitmap, 76800);
                    sprites[2].attribute0 = COLOR_256 | SQUARE | 160;
                    sprites[2].attribute1 = SIZE_8 | 240;
                    sprites[2].attribute2 = 512 + 88;
                    hrt_SetOBJXY(&sprites[0], 240, 160);
                    hrt_CopyOAM();
                    while (!(keyDown(KEY_A))) {
                        hrt_VblankIntrWait();
                        tstsndcmp(1, 416);
                    }
                    while (keyDown(KEY_A)) {
                        hrt_VblankIntrWait();
                        tstsndcmp(1, 416);
                    }
                    memcpy(VRAM, l30bBitmap, 76800);
                    while (!(keyDown(KEY_A))) {
                        hrt_VblankIntrWait();
                        tstsndcmp(1, 416);
                    }
                    while (keyDown(KEY_A)) {
                        hrt_VblankIntrWait();
                        tstsndcmp(1, 416);
                    }
                    memcpy(VRAM, l30dBitmap, 76800);
                    while (!(keyDown(KEY_A))) {
                        hrt_VblankIntrWait();
                        tstsndcmp(1, 416);
                        if (keyDown(KEY_LEFT)) {
                            arpos = 0;
                        }
                        if (keyDown(KEY_RIGHT)) {
                            arpos = 1;
                        }
                        if (arpos == 0) {
                            hrt_SetOBJXY(&sprites[2], 76, 136);
                        }
                        else {
                            hrt_SetOBJXY(&sprites[2], 128, 136);
                        }
                        hrt_CopyOAM();
                    }
                    if (arpos == 0) {
						sav = mmEffectEx(&save);
                        hrt_SaveByte(0, level);
                    }
                    memcpy(VRAM, l30Bitmap, 76800);
                    hrt_SetOBJXY(&sprites[2], 240, 160);
                    hrt_SetOBJXY(&sprites[0], px, py);
                    rot = 0;
                    for (i = 256; i < 1764; i += 15) {
                        rot += 15;
                        hrt_VblankIntrWait();
                        tstsndcmp(1, 416);
                        hrt_AffineOBJ(1, rot, i, i);
                        hrt_CopyOAM();
                    }
                    hrt_SetOBJXY(&sprites[1], 240, 160);
                }
                else {
                    die();
                    return 0;
                }
            }
        }
        else if (level == 30) {
            if (hrt_GetPixelInMode3(px, py) == 0x7ea0) {
                if ((tilex == 1)AND(tiley == 1)) {
					door = mmEffectEx(&enter);
                    for (Phase = 0; Phase < 17; Phase++) {
                        i = 2;
                        REG_BLDY = Phase;
                        while (i--) {
                            hrt_VblankIntrWait();
                            tstsndcmp(1, 416);
                        }
                    }
                    tilex = 1, tiley = 9;
                    px = 40, py = 136;
                    dir = 0;
                    memcpy(VRAM, l31Bitmap, 76800);
                    hrt_offsetOAMData = 0;
                    sprites[0].attribute1 = 0x4000 | px;
                    updateSprite(0, 16, 0, 0);
                    hrt_SetOBJXY(&sprites[0], px, py);
                    hrt_CopyOAM();
                    for (Phase = 0; Phase < 17; Phase++) {
                        i = 2;
                        REG_BLDY = 16 - Phase;
                        while (i--) {
                            hrt_VblankIntrWait();
                            tstsndcmp(1, 416);
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
                if (keyDown(KEY_A)) {
                    while (keyDown(KEY_A)) {
                        hrt_VblankIntrWait();
                        tstsndcmp(1, 416);
                    }
                    hrt_CopyOAM();
                    memcpy(VRAM, l31bBitmap, 76800);
                    while (!(keyDown(KEY_A))) {
                        hrt_VblankIntrWait();
                        tstsndcmp(1, 416);
                    }
                    memcpy(VRAM, l31Bitmap, 76800);
                    while (keyDown(KEY_A)) {
                        hrt_VblankIntrWait();
                        tstsndcmp(1, 416);
                    }
                }
            }
            if (hrt_GetPixelInMode3(px, py) == 0x7ea0) {
                if ((tilex == 10)AND(tiley == 1)) {
					door = mmEffectEx(&enter);
                    for (Phase = 0; Phase < 17; Phase++) {
                        i = 2;
                        REG_BLDY = Phase;
                        while (i--) {
                            hrt_VblankIntrWait();
                            tstsndcmp(1, 416);
                        }
                    }
                    tilex = 1, tiley = 1;
                    px = 40, py = 8;
                    dir = 0;
                    memcpy(VRAM, l32Bitmap, 76800);
                    hrt_offsetOAMData = 0;
                    sprites[0].attribute1 = 0x4000 | px;
                    updateSprite(0, 16, 0, 0);
                    hrt_SetOBJXY(&sprites[0], px, py);
                    hrt_CopyOAM();
                    for (Phase = 0; Phase < 17; Phase++) {
                        i = 2;
                        REG_BLDY = 16 - Phase;
                        while (i--) {
                            hrt_VblankIntrWait();
                            tstsndcmp(1, 416);
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
            if (hrt_GetPixelInMode3(px, py) == 0x7ea0) {
                if ((tilex == 9)AND(tiley == 4)) {
					door = mmEffectEx(&enter);
                    for (Phase = 0; Phase < 17; Phase++) {
                        i = 2;
                        REG_BLDY = Phase;
                        while (i--) {
                            hrt_VblankIntrWait();
                            tstsndcmp(1, 416);
                        }
                    }
                    tilex =5, tiley = 6;
                    px = 104, py = 88;
                    dir = 0;
                    memcpy(VRAM, l33Bitmap, 76800);
                    hrt_offsetOAMData = 0;
                    sprites[0].attribute1 = 0x4000 | px;
                    updateSprite(0, 0, 0, 0);
                    hrt_SetOBJXY(&sprites[0], px, py);
                    hrt_CopyOAM();
                    for (Phase = 0; Phase < 17; Phase++) {
                        i = 2;
                        REG_BLDY = 16 - Phase;
                        while (i--) {
                            hrt_VblankIntrWait();
                            tstsndcmp(1, 416);
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
            if (hrt_GetPixelInMode3(px, py) == 0x7ea0) {
                if ((tilex == 2)AND(tiley == 1)) {
					door = mmEffectEx(&enter);
                    for (Phase = 0; Phase < 17; Phase++) {
                        i = 2;
                        REG_BLDY = Phase;
                        while (i--) {
                            hrt_VblankIntrWait();
                            tstsndcmp(1, 416);
                        }
                    }
                    tilex = 1, tiley = 1;
                    px = 40, py = 8;
                    dir = 0;
                    memcpy(VRAM, l34Bitmap, 76800);
                    hrt_offsetOAMData = 0;
                    sprites[0].attribute1 = 0x4000 | px;
                    updateSprite(0, 0, 0, 0);
                    hrt_SetOBJXY(&sprites[0], px, py);
                    hrt_CopyOAM();
                    for (Phase = 0; Phase < 17; Phase++) {
                        i = 2;
                        REG_BLDY = 16 - Phase;
                        while (i--) {
                            hrt_VblankIntrWait();
                            tstsndcmp(1, 416);
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
            if (hrt_GetPixelInMode3(px, py) == 0x7ea0) {
                if ((tilex == 7)AND(tiley == 5)) {
					door = mmEffectEx(&enter);
                    for (Phase = 0; Phase < 17; Phase++) {
                        i = 2;
                        REG_BLDY = Phase;
                        while (i--) {
                            hrt_VblankIntrWait();
                            tstsndcmp(1, 416);
                        }
                    }
                    tilex = 1, tiley = 1;
                    px = 40, py = 8;
                    dir = 0;
                    memcpy(VRAM, l35Bitmap, 76800);
                    hrt_offsetOAMData = 0;
                    sprites[0].attribute1 = 0x4000 | px;
                    updateSprite(0, 0, 0, 0);
                    hrt_SetOBJXY(&sprites[0], px, py);
                    hrt_CopyOAM();
                    for (Phase = 0; Phase < 17; Phase++) {
                        i = 2;
                        REG_BLDY = 16 - Phase;
                        while (i--) {
                            hrt_VblankIntrWait();
                            tstsndcmp(1, 416);
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
            if (hrt_GetPixelInMode3(px, py) == 0x7ea0) {
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
            sprites[0].attribute1 = 0x4000 | px;
            updateSprite(0, 0, 0, 0);
            frames = 0;
            tilex++;
            dir = 0;
            for (i = 0; i < 16; i++) {
                if ((px == 184)OR(hrt_GetPixelInMode3(px + 16, py) == 0x0000)OR((level == 4)AND(tilex == 8)AND(tiley == 8)AND(l4s == 0))) {
                    tilex--;
                    break;
                }
                hrt_VblankIntrWait();
                tstsndcmp(1, 416);
                frames++;
                if (!(frames % 8)) {
                    anim++;
                    if (anim >= 4) {
                        anim = 0;
                    }
                }
                if (anim == 0) {
                    updateSprite(0, 0, 0, 0);
                }
                else if (anim == 1) {
                    updateSprite(0, 8, 0, 0);
                }
                else if (anim == 2) {
                    updateSprite(0, 0, 0, 0);
                }
                else {
                    updateSprite(0, 8, 0, 0);
                }
                px++;
                hrt_SetOBJXY(&sprites[0], px, py);
                hrt_CopyOAM();
                dir = 0;
            }
            i = 0;
        }
        if (!((dir == 2)OR(dir == 1))) {
            anim = 0;
        }
        if (keyDown(KEY_UP)) {
            tiley--;
            sprites[0].attribute1 = 0x4000 | px;
            updateSprite(0, 16, 0, 0);
            frames = 0;
            for (i = 0; i < 16; i++) {
                dir = 1;
                if ((py == 8)OR(hrt_GetPixelInMode3(px, py - 1) == 0x0000)) {
                    tiley++;
                    break;
                }
                if ((level == 6)AND(tilex == 9)AND(tiley == 6)AND(l4s == 0)) {
                    tiley++;
                    break;
                }
                hrt_VblankIntrWait();
                tstsndcmp(1, 416);
                udframe++;
                if (!(udframe % 8)) {
                    anim++;
                    if (anim >= 4) {
                        anim = 0;
                    }
                }
                if (anim == 0) {
                    sprites[0].attribute1 = 0x4000 | px;
                    updateSprite(0, 16, 0, 0);
                }
                else if(anim==1) {
                    sprites[0].attribute1 = 0x4000 | px;
                    updateSprite(0, 24, 0, 0);
                }
                else if (anim == 2) {
                    sprites[0].attribute1 = 0x4000 | px;
                    updateSprite(0, 16, 0, 0);
                }
                else {
                    sprites[0].attribute1 = 0x4000 | 0x1000 | px;
                    updateSprite(0, 24, 0, 0);
                }
                py--;
                hrt_SetOBJXY(&sprites[0], px, py);
                hrt_CopyOAM();
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
            sprites[0].attribute1 = 0x4000 | 0x1000 | px;
            updateSprite(0, 0, 0, 0);
            frames = 0;
            for (i = 0; i < 16; i++) {
                dir = 3;
                if ((px == 40)OR(hrt_GetPixelInMode3(px - 1, py) == 0x0000)) {
                    tilex++;
                    break;
                }
                hrt_VblankIntrWait();
                tstsndcmp(1, 416);
                frames++;
                if (!(frames % 8)) {
                    anim++;
                    if (anim >= 4) {
                        anim = 0;
                    }
                }
                if (anim == 0) {
                    updateSprite(0, 0, 0, 0);
                }
                else if(anim == 1) {
                    updateSprite(0, 8, 0, 0);
                }
                else if (anim == 2) {
                    updateSprite(0, 0, 0, 0);
                }
                else {
                    updateSprite(0, 8, 0, 0);
                }
                px--;
                hrt_SetOBJXY(&sprites[0], px, py);
                hrt_CopyOAM();
            }
            i = 0;
        }
        if (!((dir == 2)OR(dir == 1))) {
            anim = 0;
        }
        if (keyDown(KEY_DOWN)) {
            dir = 2;
            tiley++;
            sprites[0].attribute1 = 0x4000 | px;
            updateSprite(0, 32, 0, 0);
            frames = 0;
            for (i = 0; i < 16; i++) {
                if ((py == 136)OR(hrt_GetPixelInMode3(px, py + 16) == 0x0000)OR((tilex == 6)AND(tiley == 6)AND(level == 3)AND(key == 0))) {
                    tiley--;
                    break;
                }
                hrt_VblankIntrWait();
                tstsndcmp(1, 416);
                udframe++;
                if (!(udframe % 8)) {
                    anim++;
                    if (anim >= 4) {
                        anim = 0;
                    }
                }
                if ((level > 21)AND(level<27)) {
                    if (anim == 0) {
                        sprites[0].attribute1 = 0x4000 | px;
                        updateSprite(0, 16, 0, 0);
                    }
                    else if (anim == 1) {
                        sprites[0].attribute1 = 0x4000 | px;
                        updateSprite(0, 24, 0, 0);
                    }
                    else if (anim == 2) {
                        sprites[0].attribute1 = 0x4000 | px;
                        updateSprite(0, 16, 0, 0);
                    }
                    else {
                        sprites[0].attribute1 = 0x4000 | 0x1000 | px;
                        updateSprite(0, 24, 0, 0);
                    }
                }
                else {
                    if (anim == 0) {
                        sprites[0].attribute1 = 0x4000 | px;
                        updateSprite(0, 32, 0, 0);
                    }
                    else if (anim == 1) {
                        sprites[0].attribute1 = 0x4000 | px;
                        updateSprite(0, 40, 0, 0);
                    }
                    else if (anim == 2) {
                        sprites[0].attribute1 = 0x4000 | px;
                        updateSprite(0, 32, 0, 0);
                    }
                    else {
                        sprites[0].attribute1 = 0x4000 | 0x1000 | px;
                        updateSprite(0, 40, 0, 0);
                    }
                }
                py++;
                hrt_SetOBJXY(&sprites[0], px, py);
                hrt_CopyOAM();
                dir = 2;
            }
            i = 0;
        }
        hrt_SetOBJXY(&sprites[0], px, py);
        hrt_CopyOAM();
    }
    if (!((dir == 2)OR(dir == 1))) {
        anim = 0;
    }
    return 0;
}
void die()
{
	mmEffectCancelAll();
    mm_sound_effect rip = {
        { SFX_RIP },			// id
        (int)(1.0f * (1 << 10)),	// rate
        0,		// handle
        255,	// volume
        128,	// panning
    };
    FadeOut(8);
    hrt_SetDSPMode(4, //Mode
                   0,								  //CGB Mode
                   0,								  //Frame Select
                   0,                               //Unlocked HBlank
                   1,                               //Linear OBJ Tile Mapping
                   0,                               //Force Blank
                   0,                               //BG 0
                   0,                               //BG 1
                   1,                               //BG 2
                   0,                               //BG 3
                   0,                               //OBJ
                   0,                               //Win 0
                   0,                               //Win 1
                   0);							  //OBJWin
    hrt_offsetBGPal = 0;
    hrt_LoadBGPal((void*)iamgodPal, 256);
    memcpy(VRAM, iamgodBitmap, 38400);
    FadeIn(8);
    while (!(keyDown(KEY_A))) {
        hrt_VblankIntrWait();
        tstsndcmp(2, 208);
    }
	mmEffectCancelAll();
    FadeOutWhite(8);
	hrt_FillScreen(0xFFFF);
	asm volatile("swi 0x00"::); //resets console
}
