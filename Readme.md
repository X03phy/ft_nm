## Doc

https://can-ozkan.medium.com/exploring-the-nm-tool-understanding-symbols-in-binaries-1ae03193212a


## Commands to Generate ELF

### Generating an executable

```
gcc hello.c
```

For Mips :

```
powerpc-linux-gnu-gcc
```

### Generating a .o

```
gcc -c hello.c -o hello.o
```

For x32 :

```
gcc -m32 hello.c -o hello.o
```

### Generating a .so

```
gcc -c -fPIC hello.c -o hello.o
gcc hello.o -shared -o libhello.so
```

## ELF Structures

### Header

```
typedef struct {
	unsigned char e_ident[16];  // ELF magic bytes + file/class/data ABI info
	uint16_t e_type;            // File type (REL, EXEC, DYN...)
	uint16_t e_machine;         // Target architecture (x86_64 = 62)
	uint32_t e_version;         // ELF version (always 1)
	uint64_t e_entry;           // Entry point virtual address
	uint64_t e_phoff;           // Offset to Program Header Table
	uint64_t e_shoff;           // Offset to Section Header Table
	uint32_t e_flags;           // Processor-specific flags
	uint16_t e_ehsize;          // ELF header size
	uint16_t e_phentsize;       // Size of one program header entry
	uint16_t e_phnum;           // Number of program header entries
	uint16_t e_shentsize;       // Size of one section header entry
	uint16_t e_shnum;           // Number of section header entries
	uint16_t e_shstrndx;        // Index of section-name string table
} Elf64_Ehdr;
```

#### Example

```
7f 45 4c 46 02 01 01 ...   → "\x7fELF", 64-bit, little-endian
e_type    = 0x02           → Executable
e_machine = 0x3e           → x86_64
e_entry   = 0x401000       → Entry address
```

### Section Header

```
typedef struct {
	uint32_t sh_name;       // Offset in section string table (.shstrtab)
	uint32_t sh_type;       // Section type (SHT_PROGBITS, SHT_SYMTAB...)
	uint64_t sh_flags;      // Flags (ALLOC, WRITE, EXEC)
	uint64_t sh_addr;       // Virtual address (if loaded)
	uint64_t sh_offset;     // File offset to the section's data
	uint64_t sh_size;       // Section size in bytes
	uint32_t sh_link;       // Link to another section
	uint32_t sh_info;       // Extra info (meaning depends on type)
	uint64_t sh_addralign;  // Alignment constraint
	uint64_t sh_entsize;    // Entry size (for tables)
} Elf64_Shdr;

```

#### Example

```
Section: .text
sh_type   = SHT_PROGBITS
sh_flags  = SHF_ALLOC | SHF_EXECINSTR
sh_offset = 0x1000
sh_size   = 0x2a3
```

### String and symbol tables

```
typedef struct {
	uint32_t st_name;       // Offset in .strtab (symbol name)
	unsigned char st_info;  // Binding + type
	unsigned char st_other; // Visibility
	uint16_t st_shndx;      // Section index
	uint64_t st_value;      // Address/offset of symbol
	uint64_t st_size;       // Symbol size (if known)
} Elf64_Sym;
```

st_info :

bind = ELF64_ST_BIND(st_info) → GLOBAL / LOCAL / WEAK…

type = ELF64_ST_TYPE(st_info) → FUNC / OBJECT / SECTION / FILE / IFUNC…

#### Example

```
Symbol: main
Binding = GLOBAL
Type    = FUNC
Section = .text
Value   = 0x4011e0
```

## nm Symbol Letter

```
u – Unique global symbol (GNU)
A global symbol declared as unique: only one definition is allowed in the entire program. GNU extension.

i – GNU IFUNC (indirect function)
A function whose final address is resolved at runtime by a resolver function. Used to select optimized implementations depending on the CPU.

U – Undefined symbol
A symbol that is referenced but not defined in the current file (resolved by the linker or dynamically at runtime).

A – Absolute symbol
A symbol with an absolute, non-relocatable address.

C – Common symbol
Uninitialized global data. Merged by the linker. Typically corresponds to non-static global variables without an initial value.

V/v – Weak object
Weak object symbol. Can be overridden by a strong definition.

W/w – Weak symbol
Weak symbol (function or variable). Can be replaced by a strong symbol.

B/b – BSS (uninitialized data)
Global variables located in the .bss section (uninitialized data).

T/t – Text section (code)
Functions or code located in the .text section.

R/r – Read-only data
Symbols in the .rodata section (read-only data).

D/d – Initialized data
Global variables with an initial value (stored in the .data section).

? – Unknown symbol
Symbol type not recognized by nm (rare).
```
