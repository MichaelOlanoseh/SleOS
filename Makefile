ASM    = nasm
CC     = gcc
LD     = ld
GCCINC = /usr/lib/gcc/x86_64-linux-gnu/13/include

CFLAGS = -ffreestanding -O2 -m32 -fno-stack-protector -fno-builtin \
         -fno-pic -nostdlib -isystem $(GCCINC) \
         -I kernel -I drivers -I sched -I mm -I fs -Wall

LDFLAGS = -m elf_i386 -T link.ld --oformat binary

IMG = sleos.img

all: $(IMG)

$(IMG): build/boot.bin build/kernel.bin
	dd if=/dev/zero        of=$(IMG) bs=512 count=2880 2>/dev/null
	dd if=build/boot.bin   of=$(IMG) bs=512 count=1   conv=notrunc 2>/dev/null
	dd if=build/kernel.bin of=$(IMG) bs=512 seek=1    conv=notrunc 2>/dev/null
	@echo "=== sleos.img built successfully! ==="

build/boot.bin: boot/boot.asm
	@mkdir -p build
	$(ASM) -f bin $< -o $@

build/kernel.bin: build/kernel/kernel.o build/kernel/utils.o build/kernel/shell.o \
                  build/drivers/vga.o build/drivers/keyboard.o \
                  build/sched/scheduler.o build/mm/memory.o build/fs/filesystem.o
	$(LD) $(LDFLAGS) -o $@ $^

build/kernel/%.o: kernel/%.c
	@mkdir -p build/kernel
	$(CC) $(CFLAGS) -c $< -o $@

build/drivers/%.o: drivers/%.c
	@mkdir -p build/drivers
	$(CC) $(CFLAGS) -c $< -o $@

build/sched/%.o: sched/%.c
	@mkdir -p build/sched
	$(CC) $(CFLAGS) -c $< -o $@

build/mm/%.o: mm/%.c
	@mkdir -p build/mm
	$(CC) $(CFLAGS) -c $< -o $@

build/fs/%.o: fs/%.c
	@mkdir -p build/fs
	$(CC) $(CFLAGS) -c $< -o $@

run: $(IMG)
	qemu-system-x86_64 -drive file=$(IMG),format=raw -m 32M

run-gui: $(IMG)
	qemu-system-x86_64 -drive file=$(IMG),format=raw -m 32M

clean:
	rm -rf build $(IMG)
	@echo "Cleaned."

.PHONY: all run run-gui clean
