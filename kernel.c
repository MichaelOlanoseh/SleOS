#include "kernel.h"
#include "../sched/scheduler.h"
#include "../mm/memory.h"
#include "../fs/filesystem.h"
#include "../drivers/vga.h"
#include "../drivers/keyboard.h"

void kernel_main(void){
    vga_init();
    vga_clear();
    keyboard_init();

    /* ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
       LINE 1  - top border
    ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━ */
    vga_set_color(VGA_COLOR_LIGHT_BROWN, VGA_COLOR_BLACK);
    vga_print("*========================================================*\n");

    /* LINE 2  - title on green background */
    vga_set_color(VGA_COLOR_WHITE, VGA_COLOR_GREEN);
    vga_print("*        SIERRA LEONE OS  (SLeOS)  v1.0                 *\n");

    /* LINE 3-4 - sub-lines */
    vga_set_color(VGA_COLOR_LIGHT_GREEN, VGA_COLOR_BLACK);
    vga_print("*   Built by Limkokwing University Students              *\n");
    vga_print("*   Addressing Local Computing Challenges  2026          *\n");

    /* LINE 5  - bottom border */
    vga_set_color(VGA_COLOR_LIGHT_BROWN, VGA_COLOR_BLACK);
    vga_print("*========================================================*\n");

    /* LINE 6  - SDG */
    vga_set_color(VGA_COLOR_LIGHT_CYAN, VGA_COLOR_BLACK);
    vga_print("  SDG4:Education  SDG9:Innovation  SDG10:Equality  SDG17:Partnership\n");

    /* LINE 7  - license */
    vga_set_color(VGA_COLOR_WHITE, VGA_COLOR_BLACK);
    vga_print("  License: MIT Open Source   Tools: NASM + GCC + GNU LD + QEMU\n");

    /* LINE 8  - divider */
    vga_set_color(VGA_COLOR_DARK_GREY, VGA_COLOR_BLACK);
    vga_print("  --------------------------------------------------------\n");

    /* LINE 9  - boot messages all on ONE line */
    vga_set_color(VGA_COLOR_WHITE, VGA_COLOR_BLACK);
    vga_print("  [BOOT] Memory...");
    mm_init();
    vga_set_color(VGA_COLOR_LIGHT_GREEN, VGA_COLOR_BLACK);
    vga_print("OK  ");
    vga_set_color(VGA_COLOR_WHITE, VGA_COLOR_BLACK);
    vga_print("Scheduler...");
    sched_init();
    vga_set_color(VGA_COLOR_LIGHT_GREEN, VGA_COLOR_BLACK);
    vga_print("OK  ");
    vga_set_color(VGA_COLOR_WHITE, VGA_COLOR_BLACK);
    vga_print("FileSystem...");
    fs_init();
    vga_set_color(VGA_COLOR_LIGHT_GREEN, VGA_COLOR_BLACK);
    vga_print("OK  ");
    vga_set_color(VGA_COLOR_WHITE, VGA_COLOR_BLACK);
    vga_print("Keyboard...");
    vga_set_color(VGA_COLOR_LIGHT_GREEN, VGA_COLOR_BLACK);
    vga_print("OK\n");

    /* LINE 10 - divider */
    vga_set_color(VGA_COLOR_DARK_GREY, VGA_COLOR_BLACK);
    vga_print("  --------------------------------------------------------\n");

    /* LINES 11-25 — command list */
    vga_set_color(VGA_COLOR_LIGHT_CYAN, VGA_COLOR_BLACK);
    vga_print("  COMMANDS\n");
    vga_set_color(VGA_COLOR_WHITE, VGA_COLOR_BLACK);
    vga_print("  help     - Show all commands    ");
    vga_set_color(VGA_COLOR_LIGHT_GREEN, VGA_COLOR_BLACK);
    vga_print("ps       ");
    vga_set_color(VGA_COLOR_WHITE, VGA_COLOR_BLACK);
    vga_print("- Show process table\n");

    vga_print("  fcfs     - FCFS scheduler demo  ");
    vga_set_color(VGA_COLOR_LIGHT_GREEN, VGA_COLOR_BLACK);
    vga_print("rr       ");
    vga_set_color(VGA_COLOR_WHITE, VGA_COLOR_BLACK);
    vga_print("- Round-Robin demo\n");

    vga_print("  mem      - Show memory map      ");
    vga_set_color(VGA_COLOR_LIGHT_GREEN, VGA_COLOR_BLACK);
    vga_print("memtest  ");
    vga_set_color(VGA_COLOR_WHITE, VGA_COLOR_BLACK);
    vga_print("- Memory alloc demo\n");

    vga_print("  ls       - List files            ");
    vga_set_color(VGA_COLOR_LIGHT_GREEN, VGA_COLOR_BLACK);
    vga_print("cat      ");
    vga_set_color(VGA_COLOR_WHITE, VGA_COLOR_BLACK);
    vga_print("- Read a file\n");

    vga_print("  touch    - Create a file         ");
    vga_set_color(VGA_COLOR_LIGHT_GREEN, VGA_COLOR_BLACK);
    vga_print("write    ");
    vga_set_color(VGA_COLOR_WHITE, VGA_COLOR_BLACK);
    vga_print("- Write to file\n");

    vga_print("  rm       - Delete a file         ");
    vga_set_color(VGA_COLOR_LIGHT_GREEN, VGA_COLOR_BLACK);
    vga_print("sdg      ");
    vga_set_color(VGA_COLOR_WHITE, VGA_COLOR_BLACK);
    vga_print("- SDG relevance\n");

    vga_print("  about    - About SLeOS           ");
    vga_set_color(VGA_COLOR_LIGHT_GREEN, VGA_COLOR_BLACK);
    vga_print("clear    ");
    vga_set_color(VGA_COLOR_WHITE, VGA_COLOR_BLACK);
    vga_print("- Clear screen\n");

    vga_print("  halt     - Halt the system\n");

    vga_set_color(VGA_COLOR_DARK_GREY, VGA_COLOR_BLACK);
    vga_print("  --------------------------------------------------------\n");

    /* ── SHELL starts here — sleos> appears right below ── */
    shell_run();
    while(1){ __asm__ volatile("hlt"); }
}
