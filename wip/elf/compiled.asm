; a compiled ELF

; Ange Albertini, BSD Licence 2013

%include 'consts.inc'

ELFBASE equ 08048000h
BITS 32

ehdr:
istruc Elf32_Ehdr
    at Elf32_Ehdr.e_ident
        EI_MAG     db 07Fh, "ELF" 
        EI_CLASS   db ELFCLASS32
        EI_DATA    db ELFDATA2LSB
        EI_VERSION db EV_CURRENT
    at Elf32_Ehdr.e_type,      db ET_EXEC
    at Elf32_Ehdr.e_machine,   db EM_386
    at Elf32_Ehdr.e_version,   db EV_CURRENT
    at Elf32_Ehdr.e_entry,     dd main - ehdr + ELFBASE
    at Elf32_Ehdr.e_phoff,     dd phdr - ehdr
    at Elf32_Ehdr.e_shoff,     dd shdr - ehdr
    at Elf32_Ehdr.e_ehsize,    dw Elf32_Ehdr_size
    at Elf32_Ehdr.e_phentsize, dw Elf32_Phdr_size
    at Elf32_Ehdr.e_phnum,     dw PHNUM
    at Elf32_Ehdr.e_shentsize, dw Elf32_Shdr_size
    at Elf32_Ehdr.e_shnum,     dw SHNUM
    at Elf32_Ehdr.e_shstrndx,  dw SHSTRNDX
iend

phdr:
istruc Elf32_Phdr
    at Elf32_Phdr.p_type,   dd PT_LOAD
    at Elf32_Phdr.p_vaddr,  dd ELFBASE
    at Elf32_Phdr.p_paddr,  dd ELFBASE
    at Elf32_Phdr.p_filesz, dd names
    at Elf32_Phdr.p_memsz,  dd names
    at Elf32_Phdr.p_flags,  dd PF_R + PF_X
    at Elf32_Phdr.p_align,  dd 1000h
iend
PHNUM equ ($ - phdr) / Elf32_Phdr_size

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

align 10h, db 0

main:
    mov eax, SC_EXIT
    mov ebx, 42
    int 080h
MAIN_SIZE equ $ - main

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

names:
    db 0
ashstrtab:
    db ".shstrtab", 0
atext:
    db ".text", 0
NAMES_SIZE equ $ - names

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

align 10h, db 0

shdr:
istruc Elf32_Shdr
    at Elf32_Shdr.sh_type, dw SHT_NULL
iend

istruc Elf32_Shdr
    at Elf32_Shdr.sh_name,      db atext - names
    at Elf32_Shdr.sh_type,      dw SHT_PROGBITS
    at Elf32_Shdr.sh_flags,     dd SHF_ALLOC + SHF_EXECINSTR
    at Elf32_Shdr.sh_addr,      dd ELFBASE + main
    at Elf32_Shdr.sh_offset,    dd main
    at Elf32_Shdr.sh_size,      dd MAIN_SIZE
    at Elf32_Shdr.sh_addralign, dd 16
iend

SHSTRNDX equ ($ - shdr) / Elf32_Shdr_size
istruc Elf32_Shdr
    at Elf32_Shdr.sh_name,      db ashstrtab - names
    at Elf32_Shdr.sh_type,      dw SHT_STRTAB
    at Elf32_Shdr.sh_offset,    dd names
    at Elf32_Shdr.sh_size,      dd NAMES_SIZE
    at Elf32_Shdr.sh_addralign, dd 1
iend

SHNUM equ ($ - shdr) / Elf32_Shdr_size

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
