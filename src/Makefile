OS=a
MAKE=make

XCOMPILER=~/opt/cross/bin
CC=$(XCOMPILER)/i686-elf-gcc
AS=$(XCOMPILER)/i686-elf-as
LD=$(XCOMPILER)/i686-elf-ld
BINOPT=-nostdlib -fno-builtin
INCLUDE=-I./asm/ -I./libc/ -I./graphics/ -I./desc/ -I./interrupt/ -I./memory/
CCOPT=$(BINOPT) $(INCLUDE) -Wall

OBJSRC=../obj
ASMOBJS=$(OBJSRC)/asm_func.o $(OBJSRC)/inthandler.o
VIDEOOBJS=$(OBJSRC)/video.o
DESCOBJS=$(OBJSRC)/gdt.o $(OBJSRC)/idt.o
INTOBJS=$(OBJSRC)/interrupt.o
MEMOBJS=$(OBJSRC)/memory.o
BOOTOBJS=$(OBJSRC)/boot.o $(OBJSRC)/kernel.o $(ASMOBJS) $(VIDEOOBJS) \
		$(DESCOBJS) $(INTOBJS) $(MEMOBJS)
IMG=$(OS).img

EMULATOR=qemu-system-i386

$(IMG): $(BOOTOBJS)
	cd libc; $(MAKE)
	cd $(OBJSRC);\
	$(LD) -o $(IMG) -nostdlib --script=../src/script/boot.ls *.o
	mv $(OBJSRC)/$(IMG) .

$(OBJSRC)/boot.o: boot.S
	$(CC) boot.S -c -g $(CCOPT) -o $(OBJSRC)/boot.o

# General Rules
$(OBJSRC)/%.o: %.c
	$(CC) -c $*.c $(CCOPT) -o $(OBJSRC)/$*.o

$(OBJSRC)/%.o: graphics/%.c
	$(CC) -c graphics/$*.c $(CCOPT) -o $(OBJSRC)/$*.o

$(OBJSRC)/%.o: desc/%.c
	$(CC) -c desc/$*.c $(CCOPT) -o $(OBJSRC)/$*.o

$(OBJSRC)/%.o: interrupt/%.c
	$(CC) -c interrupt/$*.c $(CCOPT) -o $(OBJSRC)/$*.o

$(OBJSRC)/%.o: memory/%.c
	$(CC) -c memory/$*.c $(CCOPT) -o $(OBJSRC)/$*.o

$(OBJSRC)/%.o: asm/%.S
	$(AS) asm/$*.S -o $(OBJSRC)/$*.o

# Commands
img: $(BOOTOBJS)
	$(MAKE)

install: $(IMG)
	mformat -f 1440 -C -i fd.img ::
	tar cvf fd.img $(IMG)

run: $(IMG)
	$(EMULATOR) -m 32 -localtime -vga std -fda $(IMG)
	$(MAKE) clean

debug: $(IMG)
	$(EMULATOR) -S -s -m 32 -localtime -vga std -fda $(IMG) 

clean:
	rm -f $(OBJSRC)/*.o
	rm -f $(IMG)
