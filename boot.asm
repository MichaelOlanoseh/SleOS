[BITS 16]
[ORG 0x7C00]

start:
    cli
    xor ax, ax
    mov ds, ax
    mov es, ax
    mov ss, ax
    mov sp, 0x7C00
    sti

    mov si, msg_welcome
    call print_str
    mov si, msg_loading
    call print_str

    mov ah, 0x02
    mov al, 30
    mov ch, 0
    mov cl, 2
    mov dh, 0
    mov dl, 0x80
    mov bx, 0x1000
    mov es, bx
    xor bx, bx
    int 0x13
    jc disk_err

    mov si, msg_ok
    call print_str

    cli
    lgdt [gdt_desc]
    mov eax, cr0
    or  eax, 1
    mov cr0, eax
    jmp 0x08:pmode

disk_err:
    mov si, msg_derr
    call print_str
    hlt

print_str:
    pusha
.L: lodsb
    or al,al
    jz .D
    mov ah,0x0E
    int 0x10
    jmp .L
.D: popa
    ret

gdt_null:   dq 0
gdt_code:   dw 0xFFFF,0x0000
            db 0x00,10011010b,11001111b,0x00
gdt_data:   dw 0xFFFF,0x0000
            db 0x00,10010010b,11001111b,0x00
gdt_end:
gdt_desc:   dw gdt_end-gdt_null-1
            dd gdt_null

msg_welcome db "SLeOS - Sierra Leone OS v1.0",13,10,"Built by Limkokwing Students",13,10,0
msg_loading db "Loading kernel...",0
msg_ok      db " OK",13,10,0
msg_derr    db " DISK ERROR",13,10,0

[BITS 32]
pmode:
    mov ax, 0x10
    mov ds, ax
    mov es, ax
    mov ss, ax
    mov esp, 0x90000
    call 0x10000
.hang: hlt
    jmp .hang

times 510-($-$$) db 0
dw 0xAA55
