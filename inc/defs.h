#define ROTATION_FLAG         0x100
#define SIZE_DOUBLE           0x200
#define MODE_NORMAL           0x0
#define MODE_ALPHA            0x400
#define MODE_WINDOWED         0x800
#define MOSAIC                0x1000
#define COLOR_16              0x0000
#define COLOR_256             0x2000
#define SQUARE                0x0
#define WIDE                  0x4000
#define TALL                  0x8000
#define ROTDATA(n)			((n)<<9)
#define HORIZONTAL_FLIP		0x1000
#define VERTICAL_FLIP		0x2000
#define SIZE_8				0x0
#define SIZE_16				0x4000
#define SIZE_32				0x8000
#define SIZE_64				0xC000               
#define OBJ_MODE_NORMAL2             0x00
#define OBJ_MODE_SEMITRANSPARENT    0x01
#define OBJ_MODE_OBJWINDOW          0x02
#define PRIORITY(n)	        ((n)<<10)
#define PALETTE(n)			((n)<<12)
const unsigned short sprsTiles[4096];
const unsigned short sprsPal[64];
const unsigned short sprsdkTiles[4096];
const unsigned short sprsdkPal[64];
const unsigned short finalBitmap[19200];
const unsigned short finalPal[16];
const unsigned short iamgodBitmap[19200];
const unsigned short iamgodPal[16];
const unsigned short titlescreenBitmap[19200];
const unsigned short titlescreenPal[16];
const unsigned short wrongBitmap[19200];
const unsigned short wrongPal[256];
const unsigned short endBitmap[38400];
const unsigned short l0Bitmap[38400];
const unsigned short l0bBitmap[38400];
const unsigned short l1Bitmap[38400];
const unsigned short l1bBitmap[38400];
const unsigned short l1cBitmap[38400];
const unsigned short l2Bitmap[38400];
const unsigned short l2bBitmap[38400];
const unsigned short l3Bitmap[38400];
const unsigned short l3bBitmap[38400];
const unsigned short l3cBitmap[38400];
const unsigned short l3dBitmap[38400];
const unsigned short l4Bitmap[38400];
const unsigned short l4bBitmap[38400];
const unsigned short l5Bitmap[38400];
const unsigned short l5bBitmap[38400];
const unsigned short l6Bitmap[38400];
const unsigned short l7Bitmap[38400];
const unsigned short l8Bitmap[38400];
const unsigned short l8bBitmap[38400];
const unsigned short l9Bitmap[38400];
const unsigned short l10Bitmap[38400];
const unsigned short l10bBitmap[38400];
const unsigned short l10cBitmap[38400];
const unsigned short l10dBitmap[38400];
const unsigned short l10eBitmap[38400];
const unsigned short l11Bitmap[38400];
const unsigned short l12Bitmap[38400];
const unsigned short l13Bitmap[38400];
const unsigned short l14Bitmap[38400];
const unsigned short l15Bitmap[38400];
const unsigned short l16Bitmap[38400];
const unsigned short l17Bitmap[38400];
const unsigned short l17bBitmap[38400];
const unsigned short l18Bitmap[38400];
const unsigned short l19Bitmap[38400];
const unsigned short l20Bitmap[38400];
const unsigned short l21Bitmap[38400];
const unsigned short l22Bitmap[38400];
const unsigned short l22bBitmap[38400];
const unsigned short l23Bitmap[38400];
const unsigned short l24Bitmap[38400];
const unsigned short l25Bitmap[38400];
const unsigned short l26Bitmap[38400];
const unsigned short l27Bitmap[38400];
const unsigned short l27bBitmap[38400];
const unsigned short l28Bitmap[38400];
const unsigned short l29Bitmap[38400];
const unsigned short l29bBitmap[38400];
const unsigned short l30Bitmap[38400];
const unsigned short l30bBitmap[38400];
const unsigned short l30cBitmap[38400];
const unsigned short l30dBitmap[38400];
const unsigned short l31Bitmap[38400];
const unsigned short l31bBitmap[38400];
const unsigned short l32Bitmap[38400];
const unsigned short l33Bitmap[38400];
const unsigned short l34Bitmap[38400];
const unsigned short l35Bitmap[38400];
void FadeOutWhite(u32 frames)
{
	u32 temp = frames;
	s8 Phase;
	REG_BLDCNT = 0x00BF;
	for (Phase = 0; Phase < 17; Phase++)
	{
		frames = temp;
		REG_BLDY = Phase;
		while (frames--)
			hrt_VblankIntrWait();
	}
}

//****************************************************************************** 
void FadeInWhite(u32 frames)
{
	u32 temp = frames;
	s8 Phase;
	REG_BLDCNT = 0x00BF;
	for (Phase = 0; Phase < 17; Phase++)
	{
		frames = temp;
		REG_BLDY = 16 - Phase;
		while (frames--)
			hrt_VblankIntrWait();
	}
}
void FadeOut(u32 frames)
{
	u32 temp = frames;
	s8 Phase;
	REG_BLDCNT = 0x00F7;
	for (Phase = 0; Phase < 17; Phase++)
	{
		frames = temp;
		REG_BLDY = Phase;
		while (frames--)
			hrt_VblankIntrWait();
	}
}

//****************************************************************************** 
void FadeIn(u32 frames)
{
	u32 temp = frames;
	s8 Phase;
	REG_BLDCNT = 0x00F7;
	for (Phase = 0; Phase < 17; Phase++)
	{
		frames = temp;
		REG_BLDY = 16 - Phase;
		while (frames--)
			hrt_VblankIntrWait();
	}
}