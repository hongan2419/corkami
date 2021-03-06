%define PREFIX_OPERANDSIZE db 66h

IMAGE_RESOURCE_DATA_IS_DIRECTORY equ 80000000h
PAGE_READWRITE equ 4
ExceptionContinueExecution equ 0

DLL_PROCESS_ATTACH equ 1
DLL_PROCESS_DETACH equ 0

IMAGE_SCN_MEM_EXECUTE            equ 020000000h
IMAGE_SCN_MEM_READ               equ 040000000h
IMAGE_SCN_MEM_WRITE              equ 080000000h

MEM_COMMIT equ 1000h

BREAKPOINT equ 080000003h
SINGLE_STEP equ 80000004h
ACCESS_VIOLATION equ 0c0000005h
INVALID_HANDLE equ 0C0000008h
INVALID_LOCK_SEQUENCE equ 0C000001eh
INTEGER_DIVIDE_BY_ZERO equ 0C0000094h
INTEGER_OVERFLOW equ 0C0000095h
PRIVILEGED_INSTRUCTION equ 0C0000096h

struc exceptionHandler
    .pException resd 1          ; EXCEPTION_RECORD
    .pRegistrationRecord resd 1 ; EXCEPTION_REGISTRATION_RECORD
    .pContext resd 1            ; CONTEXT
endstruc

SIZE_OF_80387_REGISTERS equ 80
MAXIMUM_SUPPORTED_EXTENSION equ 512

struc CONTEXT
.ContextFlags  resd 1
;CONTEXT_DEBUG_REGISTERS
.iDr0          resd 1
.iDr1          resd 1
.iDr2          resd 1
.iDr3          resd 1
.iDr6          resd 1
.iDr7          resd 1
;CONTEXT_FLOATING_POINT
.ControlWord   resd 1
.StatusWord    resd 1
.TagWord       resd 1
.ErrorOffset   resd 1
.ErrorSelector resd 1
.DataOffset    resd 1
.DataSelector  resd 1
.RegisterArea  resb SIZE_OF_80387_REGISTERS
.Cr0NpxState   resd 1
;CONTEXT_SEGMENTS
.regGs   resd 1
.regFs   resd 1
.regEs   resd 1
.regDs   resd 1
;CONTEXT_INTEGER
.regEdi  resd 1
.regEsi  resd 1
.regEbx  resd 1
.regEdx  resd 1
.regEcx  resd 1
.regEax  resd 1
;CONTEXT_CONTROL
.regEbp  resd 1
.regEip  resd 1
.regCs   resd 1
.regFlag resd 1
.regEsp  resd 1
.regSs   resd 1
;CONTEXT_EXTENDED_REGISTERS
.ExtendedRegisters resb MAXIMUM_SUPPORTED_EXTENSION
endstruc

IMAGE_SIZEOF_SHORT_NAME equ 8

struc IMAGE_DOS_HEADER
  .e_magic      resw 1
  .e_cblp       resw 1
  .e_cp         resw 1
  .e_crlc       resw 1
  .e_cparhdr    resw 1
  .e_minalloc   resw 1
  .e_maxalloc   resw 1
  .e_ss         resw 1
  .e_sp         resw 1
  .e_csum       resw 1
  .e_ip         resw 1
  .e_cs         resw 1
  .e_lfarlc     resw 1
  .e_ovno       resw 1
  .e_res        resw 4
  .e_oemid      resw 1
  .e_oeminfo    resw 1
  .e_res2       resw 10
  .e_lfanew     resd 1
endstruc

struc IMAGE_NT_HEADERS
  .Signature         resd 1
;  .FileHeader        resb IMAGE_FILE_HEADER_size
;  .OptionalHeader    resb IMAGE_OPTIONAL_HEADER32_size
endstruc

struc IMAGE_FILE_HEADER
  .Machine              resw 1
  .NumberOfSections     resw 1
  .TimeDateStamp        resd 1
  .PointerToSymbolTable resd 1
  .NumberOfSymbols      resd 1
  .SizeOfOptionalHeader resw 1
  .Characteristics      resw 1
endstruc

IMAGE_FILE_MACHINE_I386         equ 014ch
IMAGE_FILE_DLL equ 02000h
IMAGE_NT_OPTIONAL_HDR32_MAGIC equ 010bh

struc IMAGE_OPTIONAL_HEADER32
  .Magic                        resw 1
  .MajorLinkerVersion           resb 1
  .MinorLinkerVersion           resb 1
  .SizeOfCode                   resd 1
  .SizeOfInitializedData        resd 1
  .SizeOfUninitializedData      resd 1
  .AddressOfEntryPoint          resd 1
  .BaseOfCode                   resd 1
  .BaseOfData                   resd 1
  .ImageBase                    resd 1
  .SectionAlignment             resd 1
  .FileAlignment                resd 1
  .MajorOperatingSystemVersion  resw 1
  .MinorOperatingSystemVersion  resw 1
  .MajorImageVersion            resw 1
  .MinorImageVersion            resw 1
  .MajorSubsystemVersion        resw 1
  .MinorSubsystemVersion        resw 1
  .Win32VersionValue            resd 1
  .SizeOfImage                  resd 1
  .SizeOfHeaders                resd 1
  .CheckSum                     resd 1
  .Subsystem                    resw 1
  .DllCharacteristics           resw 1
  .SizeOfStackReserve           resd 1
  .SizeOfStackCommit            resd 1
  .SizeOfHeapReserve            resd 1
  .SizeOfHeapCommit             resd 1
  .LoaderFlags                  resd 1
  .NumberOfRvaAndSizes          resd 1
  .DataDirectory                resb 0
endstruc

struc IMAGE_DATA_DIRECTORY
  VirtualAddress    resd 1
  isize             resd 1
endstruc

struc IMAGE_DATA_DIRECTORY_16
    .ExportsVA        resd 1
    .ExportsSize      resd 1
    .ImportsVA        resd 1
    .ImportsSize      resd 1
    .ResourceVA       resd 1
    .ResourceSize     resd 1
    .Exception        resd 2
    .Security         resd 2
    .FixupsVA         resd 1
    .FixupsSize       resd 1
    .DebugVA          resd 1
    .DebugSize        resd 1
    .Description      resd 2
    .MIPS             resd 2
    .TLSVA            resd 1
    .TLSSize          resd 1
    .Load             resd 2
    .BoundImportsVA   resd 1
    .BoundImportsSize resd 1
    .IATVA            resd 1
    .IATSize          resd 1
    .DelayImportsVA   resd 1
    .DelayImportsSize resd 1
    .COM              resd 2
    .reserved         resd 2
endstruc

struc IMAGE_SECTION_HEADER
    .Name                    resb IMAGE_SIZEOF_SHORT_NAME
    .VirtualSize             resd 1
    .VirtualAddress          resd 1
    .SizeOfRawData           resd 1
    .PointerToRawData        resd 1
    .PointerToRelocations    resd 1
    .PointerToLinenumbers    resd 1
    .NumberOfRelocations     resw 1
    .NumberOfLinenumbers     resw 1
    .Characteristics         resd 1
endstruc


IMAGE_SUBSYSTEM_WINDOWS_CUI    equ 3
IMAGE_SUBSYSTEM_WINDOWS_GUI    equ 2
IMAGE_FILE_RELOCS_STRIPPED         equ 00001h
IMAGE_FILE_EXECUTABLE_IMAGE        equ 00002h
IMAGE_FILE_LINE_NUMS_STRIPPED      equ 00004h
IMAGE_FILE_LOCAL_SYMS_STRIPPED     equ 00008h
IMAGE_FILE_32BIT_MACHINE           equ 00100h

%macro _ 0
    nop
%endmacro

%macro _c 0
    int3
    align 4, int3
%endmacro

%macro _d 0
    db 0
    align 16, db 0
%endmacro


%macro setSEH 1
    push  %1
    push dword [fs:0]
    mov [fs:0], esp
%endmacro

%macro clearSEH 0
    pop dword [fs:0]
    add esp, 4
%endmacro

struc IMAGE_OPTIONAL_HEADER64
  .Magic                        resw 1
  .MajorLinkerVersion           resb 1
  .MinorLinkerVersion           resb 1
  .SizeOfCode                   resd 1
  .SizeOfInitializedData        resd 1
  .SizeOfUninitializedData      resd 1
  .AddressOfEntryPoint          resd 1
  .BaseOfCode                   resd 1
  .ImageBase                    resq 1
  .SectionAlignment             resd 1
  .FileAlignment                resd 1
  .MajorOperatingSystemVersion  resw 1
  .MinorOperatingSystemVersion  resw 1
  .MajorImageVersion            resw 1
  .MinorImageVersion            resw 1
  .MajorSubsystemVersion        resw 1
  .MinorSubsystemVersion        resw 1
  .Win32VersionValue            resd 1
  .SizeOfImage                  resd 1
  .SizeOfHeaders                resd 1
  .CheckSum                     resd 1
  .Subsystem                    resw 1
  .DllCharacteristics           resw 1
  .SizeOfStackReserve           resq 1
  .SizeOfStackCommit            resq 1
  .SizeOfHeapReserve            resq 1
  .SizeOfHeapCommit             resq 1
  .LoaderFlags                  resd 1
  .NumberOfRvaAndSizes          resd 1
  .DataDirectory                resb 0
endstruc

IMAGE_FILE_MACHINE_AMD64        equ 8664h
IMAGE_NT_OPTIONAL_HDR64_MAGIC   equ 020bh

IMAGE_REL_BASED_HIGHLOW equ 3
CR equ 0dh
EOF equ 1ah
LF equ 0ah

struc IMAGE_RESOURCE_DIRECTORY
 .Characteristics         resd 1
 .TimeDateStamp           resd 1
 .MajorVersion            resw 1
 .MinorVersion            resw 1
 .NumberOfNamedEntries    resw 1
 .NumberOfIdEntries       resw 1
endstruc

struc IMAGE_RESOURCE_DIRECTORY_ENTRY
    .NameID resd 1
    .OffsetToData resd 1
endstruc

struc IMAGE_RESOURCE_DATA_ENTRY
    .OffsetToData resd 1
    .Size1        resd 1
    .CodePage     resd 1
    .Reserved     resd 1
endstruc

struc _IMAGE_DELAY_IMPORT_DESCRIPTOR
    .grAttrs       resd 1  ; attributes
    .rvaDLLName    resd 1  ; RVA to dll name
    .rvaHmod       resd 1  ; RVA of module handle
    .rvaIAT        resd 1  ; RVA of the IAT
    .rvaINT        resd 1  ; RVA of the INT
    .rvaBoundIAT   resd 1  ; RVA of the optional bound IAT
    .rvaUnloadIAT  resd 1  ; RVA of optional copy of original IAT
    .dwTimeStamp   resd 1  ; 0 if not bound
endstruc

struc TRUNC_OPTIONAL_HEADER32
  .Magic                        resw 1
  .MajorLinkerVersion           resb 1
  .MinorLinkerVersion           resb 1
  .SizeOfCode                   resd 1
  .SizeOfInitializedData        resd 1
  .SizeOfUninitializedData      resd 1
  .AddressOfEntryPoint          resd 1
  .BaseOfCode                   resd 1
  .BaseOfData                   resd 1
  .ImageBase                    resd 1
  .SectionAlignment             resd 1
  .FileAlignment                resd 1
  .MajorOperatingSystemVersion  resw 1
  .MinorOperatingSystemVersion  resw 1
  .MajorImageVersion            resw 1
  .MinorImageVersion            resw 1
  .MajorSubsystemVersion        resw 1
  .MinorSubsystemVersion        resw 1
  .Win32VersionValue            resd 1
  .SizeOfImage                  resd 1
  .SizeOfHeaders                resd 1
  .CheckSum                     resd 1
  .Subsystem                    resb 1  ; truncated as a byte
  ; no more data
endstruc

struc VS_FIXEDFILEINFO
  .dwSignature           resd 1
  .dwStrucVersion        resd 1
  .dwFileVersionMS       resd 1
  .dwFileVersionLS       resd 1
  .dwProductVersionMS    resd 1
  .dwProductVersionLS    resd 1
  .dwFileFlagsMask       resd 1
  .dwFileFlags           resd 1
  .dwFileOS              resd 1
  .dwFileType            resd 1
  .dwFileSubtype         resd 1
  .dwFileDateMS          resd 1
  .dwFileDateLS          resd 1
endstruc

RT_VERSION 		equ 16
RT_MANIFEST equ 24
CREATEPROCESS_MANIFEST_RESOURCE_ID EQU 1
ISOLATIONAWARE_MANIFEST_RESOURCE_ID EQU 2
ISOLATIONAWARE_NOSTATICIMPORT_MANIFEST_RESOURCE_ID EQU 3


struc ACTCTX                       ; typedef struct tagACTCTX {
.cbSize resd 1                     ;   ULONG   cbSize;
.dwFlags resd 1                    ;   DWORD   dwFlags;
.lpSource resd 1                   ;   LPCWSTR lpSource;
.wProcessorArchitecture resw 1     ;   USHORT  wProcessorArchitecture;
.wLangId resw 1                    ;   LANGID  wLangId;
.lpAssemblyDirectory resd 1        ;   LPCTSTR lpAssemblyDirectory;
.lpResourceName resd 1             ;   LPCTSTR lpResourceName;
.lpApplicationName resd 1          ;   LPCTSTR lpApplicationName;
.hModule resd 1                    ;   HMODULE hModule;
endstruc                           ; } ACTCTX, *PACTCTX;

ACTCTX_FLAG_PROCESSOR_ARCHITECTURE_VALID equ 1
ACTCTX_FLAG_LANGID_VALID equ 2
ACTCTX_FLAG_ASSEMBLY_DIRECTORY_VALID equ 4
ACTCTX_FLAG_RESOURCE_NAME_VALID equ 8
ACTCTX_FLAG_SET_PROCESS_DEFAULT equ 16
ACTCTX_FLAG_APPLICATION_NAME_VALID equ 32
ACTCTX_FLAG_HMODULE_VALID equ 128

; widechar string macro
%macro WIDE 1
%assign %%__i 1
%strlen %%__len %1
%rep %%__len
	%substr %%__c %1 %%__i
		db %%__c
		db 0
	%assign %%__i %%__i + 1
%endrep
	db 0, 0
%endmacro


%macro __string 2
%%string:
dw %%SLEN
dw %%VALLEN / 2 ; dammit !
dw 1 ; text type
WIDE %1
	align 4, db 0
%%val:
	WIDE %2
	%%VALLEN equ $ - %%val
	align 4, db 0
%%SLEN equ $ - %%string
%endmacro
