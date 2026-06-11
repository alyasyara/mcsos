CC=clang
CFLAGS=-target x86_64-unknown-none-elf -ffreestanding -fno-stack-protector -mno-red-zone -mcmodel=kernel -Wall -Wextra -O2 -Iinclude

OBJS=\
kernel/core/kmain.o \
kernel/core/log.o \
kernel/arch/x86_64/serial.o \
kernel/arch/x86_64/interrupt/idt.o \
kernel/arch/x86_64/interrupt/isr.o \
src/pmm.o \
src/vmm.o

all: build/kernel.elf

build/kernel.elf: $(OBJS)
	mkdir -p build
	ld.lld -T linker.ld -nostdlib -o build/kernel.elf $(OBJS) -Map=build/kernel.map

kernel/core/kmain.o:
	$(CC) $(CFLAGS) -c kernel/core/kmain.c -o kernel/core/kmain.o

kernel/core/log.o:
	$(CC) $(CFLAGS) -c kernel/core/log.c -o kernel/core/log.o

kernel/arch/x86_64/serial.o:
	$(CC) $(CFLAGS) -c kernel/arch/x86_64/serial.c -o kernel/arch/x86_64/serial.o

kernel/arch/x86_64/interrupt/idt.o:
	$(CC) $(CFLAGS) -c kernel/arch/x86_64/interrupt/idt.c -o kernel/arch/x86_64/interrupt/idt.o

kernel/arch/x86_64/interrupt/isr.o:
	nasm -f elf64 kernel/arch/x86_64/interrupt/isr.asm -o kernel/arch/x86_64/interrupt/isr.o

src/pmm.o:
	$(CC) $(CFLAGS) -c src/pmm.c -o src/pmm.o

src/vmm.o:
	$(CC) $(CFLAGS) -c src/vmm.c -o src/vmm.o

clean:
	rm -rf build
	find . -name '*.o' -delete
