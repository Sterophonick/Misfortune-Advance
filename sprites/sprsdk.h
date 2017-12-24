/**********************************************\
*       prsdk.h                                   *
*          by dovotos pcx->gba program         *
/**********************************************/
#define  prsdk_WIDTH   16
#define  prsdk_HEIGHT  256


const u16 prsdkData[] = {
                    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
                    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
                    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0E00, 0x000E, 0x0000, 0x0000,
                    0x0E00, 0x100E, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
                    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0E00, 0x000E,
                    0x0000, 0x0000, 0x0E0E, 0x0E0E, 0x0000, 0x0000, 0x0E0E, 0x0E0E, 0x0000, 0x0000,
                    0x0E0E, 0x0E00, 0x0000, 0x0000, 0x0000, 0x0000, 0x0E00, 0x0E0E, 0x0000, 0x0000,
                    0x0000, 0x0E0E, 0x0000, 0x0000, 0x0F00, 0x0000, 0x0000, 0x0000, 0x0F00, 0x0E00,
                    0x0000, 0x0000, 0x0000, 0x0E00, 0x0000, 0x0000, 0x0000, 0x0E00, 0x0000, 0x0000,
                    0x0000, 0x000D, 0x0000, 0x0000, 0x0000, 0x0000, 0x0E0E, 0x0E0E, 0x0000, 0x0000,
                    0x0E0E, 0x0009, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x000E, 0x000F,
                    0x0000, 0x0000, 0x000E, 0x0000, 0x0000, 0x0000, 0x000E, 0x0000, 0x0000, 0x0000,
                    0x0D00, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
                    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
                    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
                    0x0000, 0x0000, 0x0000, 0x0000, 0x0E00, 0x000E, 0x0000, 0x0000, 0x0E00, 0x100E,
                    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
                    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0E00, 0x000E, 0x0000, 0x0000,
                    0x0E0E, 0x0E0E, 0x0000, 0x0000, 0x0E0E, 0x0E0E, 0x0000, 0x0000, 0x0E0E, 0x0E00,
                    0x0000, 0x0000, 0x0000, 0x0000, 0x0E00, 0x0E0E, 0x0000, 0x0000, 0x0000, 0x0E0E,
                    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0E00, 0x000E, 0x0000, 0x0000,
                    0x0E00, 0x000E, 0x0000, 0x0D00, 0x0E00, 0x000E, 0x0000, 0x0D00, 0x000D, 0x0000,
                    0x0000, 0x0000, 0x0000, 0x0000, 0x0E0E, 0x0E0E, 0x0000, 0x0000, 0x0E0E, 0x0009,
                    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0F00, 0x0000, 0x0000, 0x0000,
                    0x0F00, 0x0000, 0x0000, 0x0000, 0x0000, 0x0D00, 0x000D, 0x0000, 0x0000, 0x0D0D,
                    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
                    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
                    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x000E, 0x0000, 0x0000,
                    0x0000, 0x0E0E, 0x0000, 0x0000, 0x0000, 0x100E, 0x0000, 0x0000, 0x0000, 0x0000,
                    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
                    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
                    0x0E00, 0x0000, 0x0000, 0x0000, 0x0E0E, 0x0000, 0x0000, 0x0000, 0x0E10, 0x0000,
                    0x0000, 0x0000, 0x100E, 0x0000, 0x0000, 0x0E00, 0x0000, 0x1010, 0x0000, 0x0E0E,
                    0x0F00, 0x0000, 0x0000, 0x000E, 0x0F00, 0x0F0F, 0x0000, 0x0000, 0x0000, 0x0000,
                    0x0000, 0x0000, 0x000D, 0x0000, 0x0000, 0x0000, 0x0D0D, 0x000D, 0x0000, 0x0000,
                    0x0000, 0x0000, 0x0000, 0x0E10, 0x0000, 0x0000, 0x1010, 0x0000, 0x000E, 0x0000,
                    0x0000, 0x000F, 0x0E0E, 0x0000, 0x0F0F, 0x000F, 0x0E00, 0x0000, 0x0000, 0x0000,
                    0x0000, 0x0000, 0x0000, 0x0D00, 0x0000, 0x0000, 0x0D00, 0x0D0D, 0x0000, 0x0000,
                    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
                    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
                    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x000E,
                    0x0000, 0x0000, 0x0000, 0x0E0E, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
                    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
                    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
                    0x0000, 0x0000, 0x0E00, 0x0000, 0x0000, 0x0000, 0x0E0E, 0x0000, 0x0000, 0x100E,
                    0x0000, 0x0000, 0x0000, 0x0000, 0x100E, 0x0000, 0x0000, 0x0000, 0x0000, 0x1010,
                    0x0000, 0x0E0E, 0x0F00, 0x0000, 0x0000, 0x0E0E, 0x0F00, 0x0F0F, 0x0000, 0x0000,
                    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
                    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0E10, 0x0E00, 0x0000, 0x1010, 0x0000,
                    0x0000, 0x0000, 0x0000, 0x000F, 0x0000, 0x0000, 0x0F0F, 0x000F, 0x0000, 0x0000,
                    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0D00, 0x0000, 0x0000, 0x0000, 0x0000,
                    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
                    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
                    0x0E00, 0x000E, 0x0000, 0x000E, 0x0E0E, 0x000E, 0x0000, 0x0E0E, 0x0E0E, 0x0E0E,
                    0x0000, 0x100E, 0x0E0E, 0x0E00, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
                    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
                    0x0E00, 0x000E, 0x0000, 0x0000, 0x0E00, 0x0E0E, 0x0E00, 0x0000, 0x0E0E, 0x0E0E,
                    0x0E0E, 0x0000, 0x000E, 0x0E0E, 0x0E10, 0x0000, 0x0000, 0x0000, 0x0E0E, 0x0E00,
                    0x0000, 0x0000, 0x0E00, 0x090E, 0x0000, 0x0E0E, 0x0000, 0x0000, 0x0000, 0x0E0E,
                    0x0F00, 0x000F, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x000D, 0x0000,
                    0x0000, 0x0000, 0x0D0D, 0x000D, 0x0000, 0x0000, 0x0000, 0x0000, 0x000E, 0x0E0E,
                    0x0000, 0x0000, 0x0E09, 0x000E, 0x0000, 0x0000, 0x0000, 0x0000, 0x0E0E, 0x0000,
                    0x0F00, 0x000F, 0x0E0E, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0D00,
                    0x0000, 0x0000, 0x0D00, 0x0D0D, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
                    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
                    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0E00, 0x000E,
                    0x0000, 0x000E, 0x0E0E, 0x000E, 0x0000, 0x0E0E, 0x0E0E, 0x0E0E, 0x0000, 0x100E,
                    0x0E0E, 0x0E00, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
                    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0E00, 0x000E,
                    0x0000, 0x0000, 0x0E00, 0x0E0E, 0x0E00, 0x0000, 0x0E0E, 0x0E0E, 0x0E0E, 0x0000,
                    0x000E, 0x0E0E, 0x0E10, 0x0000, 0x0000, 0x0000, 0x0E0E, 0x0E00, 0x0000, 0x000E,
                    0x0E00, 0x090E, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0F00, 0x000F,
                    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
                    0x0D0D, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x000E, 0x0E0E, 0x0000, 0x0000,
                    0x0E09, 0x000E, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0F00, 0x000F,
                    0x0E0E, 0x0000, 0x0000, 0x0000, 0x0E0E, 0x0000, 0x0000, 0x000D, 0x0000, 0x0000,
                    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0800,
                    0x0808, 0x0000, 0x0000, 0x0008, 0x0000, 0x0008, 0x0800, 0x0000, 0x0000, 0x0800,
                    0x0008, 0x0800, 0x0008, 0x0800, 0x0008, 0x0808, 0x0000, 0x0000, 0x0000, 0x0008,
                    0x0000, 0x0000, 0x0800, 0x0000, 0x0000, 0x0000, 0x0800, 0x0000, 0x0303, 0x0000,
                    0x0000, 0x0808, 0x0008, 0x0000, 0x0800, 0x0000, 0x0800, 0x0000, 0x0008, 0x0000,
                    0x0000, 0x0008, 0x0008, 0x0800, 0x0008, 0x0800, 0x0000, 0x0000, 0x0808, 0x0800,
                    0x0000, 0x0000, 0x0800, 0x0000, 0x0000, 0x0000, 0x0000, 0x0008, 0x0000, 0x0303,
                    0x0000, 0x0008, 0x0008, 0x0300, 0x0300, 0x0003, 0x0008, 0x0300, 0x0003, 0x0003,
                    0x0008, 0x0000, 0x0303, 0x0000, 0x0008, 0x0000, 0x0000, 0x0000, 0x0800, 0x0000,
                    0x0000, 0x0003, 0x0000, 0x0008, 0x0000, 0x0300, 0x0800, 0x0000, 0x0000, 0x0000,
                    0x0008, 0x0000, 0x0000, 0x0000, 0x0300, 0x0003, 0x0003, 0x0800, 0x0300, 0x0300,
                    0x0003, 0x0800, 0x0000, 0x0303, 0x0000, 0x0800, 0x0000, 0x0000, 0x0000, 0x0800,
                    0x0300, 0x0000, 0x0000, 0x0008, 0x0003, 0x0000, 0x0800, 0x0008, 0x0000, 0x0000,
                    0x0008, 0x0800, 0x0000, 0x0800, 0x0000, 0x0800, 0x0800, 0x0800, 0x0000, 0x0000,
                    0x0000, 0x0808, 0x0000, 0x0000, 0x0000, 0x0800, 0x0000, 0x0000, 0x0000, 0x0800,
                    0x0000, 0x0000, 0x0000, 0x0000, 0x0008, 0x0000, 0x0000, 0x0000, 0x0008, 0x0000,
                    0x0000, 0x0000, 0x0800, 0x0000, 0x0000, 0x0000, 0x0000, 0x0808, 0x0000, 0x0800,
                    0x0000, 0x0800, 0x0000, 0x0000, 0x0808, 0x0008, 0x0000, 0x0000, 0x0800, 0x0000,
                    0x0000, 0x0000, 0x0008, 0x0000, 0x0008, 0x0000, 0x0008, 0x0000, 0x0808, 0x0800,
                    0x0000, 0x0000, 0x0008, 0x0008, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
                    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
                    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
                    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
                    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
                    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
                    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
                    0x0000, 0x0000, 0x0000, 0x0000, 0x0A0A, 0x0A0A, 0x0A0A, 0x0000, 0x0A0A, 0x0A0A,
                    0x0000, 0x0B0C, 0x0A0A, 0x000A, 0x0B0C, 0x0A0A, 0x0A0A, 0x0C00, 0x0A0A, 0x0A0A,
                    0x0A0A, 0x0B00, 0x0A0A, 0x0A0A, 0x0A0A, 0x0C00, 0x0B0B, 0x0A0A, 0x0A0A, 0x0C00,
                    0x0C0B, 0x0B0B, 0x0B0A, 0x0C00, 0x0C0B, 0x0A0C, 0x0000, 0x0A00, 0x0A0A, 0x0A0A,
                    0x0B0B, 0x000C, 0x0A00, 0x0A0A, 0x0A0A, 0x0B0A, 0x000C, 0x0A0A, 0x0A0A, 0x0A0A,
                    0x0C0A, 0x0A00, 0x0A0A, 0x0A0A, 0x0B0A, 0x0A00, 0x0A0A, 0x0B0A, 0x0C0B, 0x0A00,
                    0x0B0B, 0x0C0B, 0x0C0B, 0x0A00, 0x0A0A, 0x0C0C, 0x0C0B, 0x0A00, 0x0B0B, 0x0B00,
                    0x0C0B, 0x0A0C, 0x0C0B, 0x0B00, 0x0B0B, 0x0A0B, 0x0C0B, 0x0C00, 0x0B0B, 0x0A0B,
                    0x0C0B, 0x0C00, 0x0C0B, 0x0A0C, 0x0C0A, 0x000C, 0x0C0B, 0x0A0C, 0x0B0A, 0x0C0C,
                    0x0000, 0x0A0C, 0x0A0A, 0x0C0B, 0x0C0C, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
                    0x0A0A, 0x0C0C, 0x0B0B, 0x0A00, 0x0A0A, 0x0B0B, 0x0B0B, 0x0A00, 0x0A0A, 0x0B0B,
                    0x0C0B, 0x0A00, 0x0A0A, 0x0C0C, 0x0C0B, 0x0A00, 0x0A0A, 0x0C0C, 0x000B, 0x0A0C,
                    0x0A0A, 0x000C, 0x0C00, 0x0A0A, 0x0000, 0x0C00, 0x0A0C, 0x0A0A, 0x0000, 0x0000,
                    0x0000, 0x0000, 0x0000, 0x0800, 0x0808, 0x0808, 0x0000, 0x0008, 0x0000, 0x0000,
                    0x0800, 0x0000, 0x0000, 0x0000, 0x0800, 0x0800, 0x0808, 0x0008, 0x0000, 0x0008,
                    0x0008, 0x0000, 0x0000, 0x0800, 0x0000, 0x0000, 0x0000, 0x0800, 0x0000, 0x0000,
                    0x0000, 0x0008, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0008, 0x0000,
                    0x0000, 0x0000, 0x0800, 0x0008, 0x0000, 0x0000, 0x0000, 0x0800, 0x0008, 0x0000,
                    0x0000, 0x0000, 0x0800, 0x0000, 0x0000, 0x0000, 0x0000, 0x0008, 0x0000, 0x0303,
                    0x0000, 0x0008, 0x0300, 0x0300, 0x0003, 0x0800, 0x0000, 0x0008, 0x0000, 0x0000,
                    0x0000, 0x0008, 0x0000, 0x0000, 0x0000, 0x0008, 0x0000, 0x0000, 0x0800, 0x0800,
                    0x0000, 0x0000, 0x0008, 0x0009, 0x0000, 0x0000, 0x0900, 0x0909, 0x0000, 0x0000,
                    0x0900, 0x0909, 0x0009, 0x0000, 0x0900, 0x0009, 0x0000, 0x0008, 0x0300, 0x0003,
                    0x0003, 0x0800, 0x0000, 0x0303, 0x0000, 0x0800, 0x0000, 0x0000, 0x0000, 0x0800,
                    0x0000, 0x0000, 0x0003, 0x0800, 0x0000, 0x0000, 0x0300, 0x0008, 0x0000, 0x0000,
                    0x0000, 0x0008, 0x0000, 0x0000, 0x0808, 0x0000, 0x0800, 0x0000, 0x0008, 0x0000,
                    0x0900, 0x0800, 0x0000, 0x0008, 0x0000, 0x0808, 0x0000, 0x0008, 0x0808, 0x0800,
                    0x0000, 0x0800, 0x0000, 0x0000, 0x0008, 0x0000, 0x0000, 0x0000, 0x0800, 0x0000,
                    0x0000, 0x0000, 0x0000, 0x0008, 0x0000, 0x0000, 0x0000, 0x0800, 0x0000, 0x0000,
                    0x0000, 0x0000, 0x0800, 0x0000, 0x0008, 0x0000, 0x0800, 0x0000, 0x0008, 0x0000,
                    0x0008, 0x0000, 0x0008, 0x0000, 0x0000, 0x0800, 0x0000, 0x0000, 0x0000, 0x0800,
                    0x0000, 0x0000, 0x0000, 0x0008, 0x0000, 0x0000, 0x0808, 0x0000, 0x0000, 0x0000,
                    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
                    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
                    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
                    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
                    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
                    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
                    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0808, 0x0808,
                    0x0000, 0x0000, 0x0808, 0x0808, 0x0008, 0x0000, 0x0808, 0x0808, 0x0808, 0x0000,
                    0x0808, 0x0808, 0x0808, 0x0008, 0x0808, 0x0808, 0x0808, 0x0000, 0x0808, 0x0808,
                    0x0008, 0x0000, 0x0808, 0x0808, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
                    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
                    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
                    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
                    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
                    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
                    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
                    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
                    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
                    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
                    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0707, 0x0007, 0x0000, 0x0000,
                    0x0006, 0x0700, 0x0707, 0x0707, 0x0700, 0x0700, 0x0707, 0x0707, 0x0700, 0x0700,
                    0x0707, 0x0707, 0x0700, 0x0700, 0x0707, 0x0707, 0x0700, 0x0700, 0x0707, 0x0707,
                    0x0700, 0x0700, 0x0707, 0x0707, 0x0700, 0x0700, 0x0707, 0x0707, 0x0000, 0x0000,
                    0x0700, 0x0007, 0x0707, 0x0707, 0x0007, 0x0000, 0x0707, 0x0707, 0x0007, 0x0006,
                    0x0707, 0x0707, 0x0007, 0x0006, 0x0707, 0x0707, 0x0007, 0x0006, 0x0707, 0x0707,
                    0x0007, 0x0006, 0x0707, 0x0707, 0x0007, 0x0006, 0x0707, 0x0707, 0x0007, 0x0006,
                    0x0700, 0x0000, 0x0000, 0x0000, 0x0700, 0x0600, 0x0606, 0x0606, 0x0000, 0x0606,
                    0x0606, 0x0606, 0x0000, 0x0606, 0x0606, 0x0606, 0x0600, 0x0606, 0x0606, 0x0606,
                    0x0600, 0x0606, 0x0606, 0x0606, 0x0600, 0x0606, 0x0606, 0x0606, 0x0006, 0x0000,
                    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0006, 0x0606, 0x0606, 0x0006, 0x0006,
                    0x0606, 0x0606, 0x0606, 0x0000, 0x0606, 0x0606, 0x0606, 0x0000, 0x0606, 0x0606,
                    0x0606, 0x0006, 0x0606, 0x0606, 0x0606, 0x0006, 0x0606, 0x0606, 0x0606, 0x0006,
                    0x0000, 0x0000, 0x0000, 0x0000, 0x0303, 0x0303, 0x0303, 0x0303, 0x0303, 0x0303,
                    0x0303, 0x0303, 0x0303, 0x0303, 0x0303, 0x0303, 0x0303, 0x0303, 0x0303, 0x0303,
                    0x0303, 0x0303, 0x0303, 0x0303, 0x0303, 0x0303, 0x0303, 0x0003, 0x0303, 0x0303,
                    0x0303, 0x0003, 0x0303, 0x0303, 0x0303, 0x0003, 0x0303, 0x0303, 0x0303, 0x0303,
                    0x0303, 0x0303, 0x0303, 0x0303, 0x0303, 0x0303, 0x0303, 0x0303, 0x0303, 0x0303,
                    0x0303, 0x0303, 0x0000, 0x0303, 0x0303, 0x0303, 0x0404, 0x0300, 0x0303, 0x0303,
                    0x0004, 0x0005, 0x0303, 0x0303, 0x0504, 0x0005, 0x0303, 0x0303, 0x0303, 0x0303,
                    0x0303, 0x0400, 0x0303, 0x0303, 0x0003, 0x0004, 0x0303, 0x0303, 0x0400, 0x0500,
                    0x0303, 0x0303, 0x0000, 0x0003, 0x0303, 0x0303, 0x0303, 0x0303, 0x0303, 0x0303,
                    0x0303, 0x0303, 0x0303, 0x0303, 0x0303, 0x0303, 0x0303, 0x0303, 0x0303, 0x0303,
                    0x0000, 0x0300, 0x0303, 0x0303, 0x0303, 0x0303, 0x0303, 0x0303, 0x0300, 0x0303,
                    0x0303, 0x0303, 0x0300, 0x0303, 0x0303, 0x0303, 0x0303, 0x0303, 0x0303, 0x0303,
                    0x0303, 0x0303, 0x0303, 0x0303, 0x0303, 0x0303, 0x0303, 0x0303, 0x0303, 0x0303,
                    0x0303, 0x0303, 0x0101, 0x0001, 0x0100, 0x0101, 0x0201, 0x0102, 0x0201, 0x0102,
                    0x0201, 0x0102, 0x0201, 0x0102, 0x0201, 0x0102, 0x0201, 0x0102, 0x0100, 0x0102,
                    0x0201, 0x0001, 0x0100, 0x0202, 0x0202, 0x0001, 0x0000, 0x0201, 0x0102, 0x0000,
                    0x0000, 0x0100, 0x0001, 0x0000, 0x0000, 0x0101, 0x0101, 0x0000, 0x0100, 0x0202,
                    0x0202, 0x0001, 0x0201, 0x0102, 0x0201, 0x0102, 0x0201, 0x0102, 0x0202, 0x0102,
                    0x0201, 0x0202, 0x0201, 0x0102, 0x0201, 0x0102, 0x0201, 0x0102, 0x0100, 0x0202,
                    0x0202, 0x0001, 0x0000, 0x0101, 0x0101, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
                    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
                    0x0000, 0x0000, 0x0000, 0x0100, 0x0001, 0x0000, 0x0000, 0x0201, 0x0102, 0x0000,
                    0x0000, 0x0201, 0x0102, 0x0000, 0x0000, 0x0100, 0x0001, 0x0000, 0x0000, 0x0100,
                    0x0001, 0x0000, 0x0000, 0x0201, 0x0102, 0x0000, 0x0100, 0x0202, 0x0102, 0x0000,
                    0x0000, 0x0201, 0x0102, 0x0000, 0x0000, 0x0201, 0x0102, 0x0000, 0x0000, 0x0201,
                    0x0102, 0x0000, 0x0100, 0x0202, 0x0202, 0x0001, 0x0000, 0x0101, 0x0101, 0x0000,
                    0x0000, 0x0100, 0x0001, 0x0000, 0x0000, 0x0201, 0x0102, 0x0000, 0x0100, 0x0202,
                    0x0102, 0x0000, 0x0000, 0x0201, 0x0102, 0x0000, 0x0000, 0x0201, 0x0102, 0x0000,
                    0x0000, 0x0201, 0x0102, 0x0000, 0x0100, 0x0202, 0x0202, 0x0001, 0x0000, 0x0101,
                    0x0101, 0x0000, 0x0000, 0x0101, 0x0101, 0x0000, 0x0100, 0x0202, 0x0202, 0x0001,
                    0x0201, 0x0102, 0x0201, 0x0102, 0x0201, 0x0102, 0x0201, 0x0102, 0x0201, 0x0202,
                    0x0202, 0x0102, 0x0201, 0x0102, 0x0201, 0x0102, 0x0201, 0x0102, 0x0201, 0x0102,
                    0x0101, 0x0001, 0x0100, 0x0101, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
                    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
                    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
                    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
                    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
                    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
                    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,};

const u16 prsdkPalette[] = {
                    0x0000, 0x0C63, 0x7FFF, 0x4E73, 0x4D8C, 0x4C00, 0x4C0C, 0x4D91, 0x0013, 0x0003,
                    0x326C, 0x0260, 0x00E0, 0x2D6B, 0x2613, 0x0C60, 0x11D3, 0x0000, 0x0000, 0x0000,
                    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
                    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
                    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
                    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
                    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
                    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
                    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
                    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
                    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
                    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
                    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
                    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
                    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
                    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
                    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
                    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
                    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
                    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
                    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
                    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
                    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
                    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
                    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
                    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,};