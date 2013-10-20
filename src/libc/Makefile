LIBC=libc.a
MAKE=make

XCOMPILER=~/opt/cross/bin
CC=$(XCOMPILER)/i686-elf-gcc
AS=$(XCOMPILER)/i686-elf-as
LD=$(XCOMPILER)/i686-elf-ld
AR=$(XCOMPILER)/i686-elf-ar
BINOPT=-nostdlib -fno-builtin
INCLUDE=-I../graphics/
CCOPT=$(BINOPT) $(INCLUDE)

OBJSRC=../../obj
OBJS=$(OBJSRC)/stdio.o $(OBJSRC)/stdlib.o $(OBJSRC)/string.o

default: $(OBJS)

# General Rules
$(OBJSRC)/%.o: %.c
	$(CC) -c $*.c $(CCOPT) -o $(OBJSRC)/$*.o

$(OBJSRC)/%.o: %.S
	$(AS) $*.S -o $(OBJSRC)/$*.o

# Commands
clean:
	rm -f $(OBJSRC)/*.o
