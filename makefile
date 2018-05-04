HEADERS = inc/defs.h
OBJECTS = build/main.o build/levels.o build/obj_bg.o build/soundbank.o
SOURCES = src/main.c src/levels.o src/obj_bg.o src/soundbank.s
ELFS = build/main.elf
CFLAGS = -Wall -Wextra -O3 -ffast-math -mlong-calls -mcpu=arm7tdmi -mtune=arm7tdmi -marm -faggressive-loop-optimizations -fverbose-asm 
ARCH = -mthumb -mthumb-interwork
SPECS = -specs=gba.specs
PREFIX = C:\devkitPro\devkitARM\bin\arm-none-eabi-

default: misfortune.gba

build/%.o: src/%.s $(HEADERS)
	$(PREFIX)gcc $(CFLAGS) $(ARCH) -c $< -o $@
build/%.o: src/%.c $(HEADERS)
	$(PREFIX)gcc $(CFLAGS) $(ARCH) -c $< -o $@
build/%.o: data/%.c $(HEADERS)
	$(PREFIX)gcc $(CFLAGS) $(ARCH) -c $< -o $@
build/main.elf: $(OBJECTS) 
	$(PREFIX)gcc $(SPECS) $(ARCH) -LC:\devkitPro\devkitARM\lib $(OBJECTS) -lheart -lm -o build/main.elf
misfortune.gba: $(ELFS)
	$(PREFIX)objcopy -O binary $(ELFS) misfortune.gba
	C:\devkitPro\devkitARM\bin\gbafix misfortune.gba
clean:
	-rm -f build/*.o
	-rm -f build/main.elf
	-rm -f mayhem.gba