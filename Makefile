CC=clang
LD=ld.lld

CFLAGS=-target x86_64-unknown-none-elf \
-ffreestanding \
-fno-stack-protector \
-mno-red-zone \
-mcmodel=kernel \
-Wall -Wextra -O2

KERNEL_OBJS=\
kernel/core/kmain.o \
kernel/core/log.o \
kernel/arch/x86_64/serial.o \
kernel/arch/x86_64/interrupt/idt.o \
kernel/arch/x86_64/interrupt/isr.o

.PHONY: all clean

all: build/kernel.elf

build/kernel.elf: $(KERNEL_OBJS)
	mkdir -p build
	$(LD) -T linker.ld -nostdlib -o $@ $(KERNEL_OBJS) -Map=build/kernel.map

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

%.o: %.asm
	nasm -f elf64 $< -o $@

clean:
	rm -rf build
	find . -name '*.o' -delete
