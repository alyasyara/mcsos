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
kernel/arch/x86_64/serial.o

.PHONY: all clean

all: build/kernel.elf

build/kernel.elf: $(KERNEL_OBJS)
	mkdir -p build
	$(LD) -T linker.ld -nostdlib -o $@ $(KERNEL_OBJS) -Map=build/kernel.map

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf build
	find . -name '*.o' -delete
m8-kmem-host-test:
	gcc -Iinclude tests/test_kmem.c kernel/mm/kmem.c -o build/m8/test_kmem
	build/m8/test_kmem

m8-audit:
	./scripts/check_m8_kmem.sh
m9-scheduler-host-test:
	gcc -Iinclude tests/test_scheduler.c kernel/sched/mcsos_thread.c -o build/m9/test_scheduler
	build/m9/test_scheduler

m9-audit:
	./scripts/check_m9_scheduler.sh
m10-host-test:
	gcc -Iinclude tests/test_syscall_host.c kernel/syscall/syscall.c -o build/m10/test_syscall
	build/m10/test_syscall

m10-preflight:
	./scripts/m10_preflight.sh

m10-qemu-smoke:
	./scripts/m10_qemu_smoke.sh
