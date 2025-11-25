## ELF Header
typedef struct {
    unsigned char e_ident[16];  // Signature ELF + infos système
    uint16_t e_type;            // Type du fichier (relocatable, executable, shared)
    uint16_t e_machine;         // Architecture (x86_64, ARM...)
    uint32_t e_version;         // Version ELF
    uint64_t e_entry;           // Adresse du point d'entrée (main)
    uint64_t e_phoff;           // Offset vers la table des Program Headers
    uint64_t e_shoff;           // Offset vers la table des Section Headers
    uint32_t e_flags;           // Flags
    uint16_t e_ehsize;          // Taille de ce header
    uint16_t e_phentsize;       // Taille d’une entrée Program Header
    uint16_t e_phnum;           // Nombre d’entrées Program Header
    uint16_t e_shentsize;       // Taille d’une entrée Section Header
    uint16_t e_shnum;           // Nombre d’entrées Section Header
    uint16_t e_shstrndx;        // Index de la section contenant les noms des sections
} Elf64_Ehdr;


typedef struct {
    uint32_t sh_name;       // Offset dans la table des noms de sections
    uint32_t sh_type;       // Type de la section (code, data, symboles…)
    uint64_t sh_flags;      // Attributs (alloc, exec, write...)
    uint64_t sh_addr;       // Adresse virtuelle (si applicable)
    uint64_t sh_offset;     // Offset dans le fichier où commence la section
    uint64_t sh_size;       // Taille de la section
    uint32_t sh_link;       // Lien vers une autre section (ex: pour les symboles → strtab)
    uint32_t sh_info;       // Infos supplémentaires
    uint64_t sh_addralign;  // Alignement
    uint64_t sh_entsize;    // Taille d’un élément (utile pour .symtab)
} Elf64_Shdr;


typedef struct {
   uint32_t st_name;       // Index du nom dans la table de chaînes
   unsigned char st_info;  // Type et liaison (func, object, global/local)
   unsigned char st_other; // Visibilité
   uint16_t st_shndx;      // Index de la section associée
   uint64_t st_value;      // Adresse ou offset du symbole
   uint64_t st_size;       // Taille (si connue)
} Elf64_Sym;

"A" The symbol's value is absolute, and will not be changed by
	further linking.

"B"
"b" The symbol is in the BSS data section.  This section
	typically contains zero-initialized or uninitialized data,
	although the exact behavior is system dependent.

"C"
"c" The symbol is common.  Common symbols are uninitialized
	data.  When linking, multiple common symbols may appear
	with the same name.  If the symbol is defined anywhere,
	the common symbols are treated as undefined references.
	The lower case c character is used when the symbol is in a
	special section for small commons.

"D"
"d" The symbol is in the initialized data section.

"G"
"g" The symbol is in an initialized data section for small
	objects.  Some object file formats permit more efficient
	access to small data objects, such as a global int
	variable as opposed to a large global array.

"i" For PE format files this indicates that the symbol is in a
	section specific to the implementation of DLLs.

	For ELF format files this indicates that the symbol is an
	indirect function.  This is a GNU extension to the
	standard set of ELF symbol types.  It indicates a symbol
	which if referenced by a relocation does not evaluate to
	its address, but instead must be invoked at runtime.  The
	runtime execution will then return the value to be used in
	the relocation.

	Note - the actual symbols display for GNU indirect symbols
	is controlled by the --ifunc-chars command line option.
	If this option has been provided then the first character
	in the string will be used for global indirect function
	symbols.  If the string contains a second character then
	that will be used for local indirect function symbols.

"I" The symbol is an indirect reference to another symbol.

"N" The symbol is a debugging symbol.

"n" The symbol is in a non-data, non-code, non-debug read-only
	section.

"p" The symbol is in a stack unwind section.

"R"
"r" The symbol is in a read only data section.

"S"
"s" The symbol is in an uninitialized or zero-initialized data
	section for small objects.

"T"
"t" The symbol is in the text (code) section.

"U" The symbol is undefined.

"u" The symbol is a unique global symbol.  This is a GNU
	extension to the standard set of ELF symbol bindings.  For
	such a symbol the dynamic linker will make sure that in
	the entire process there is just one symbol with this name
	and type in use.

"V"
"v" The symbol is a weak object.  When a weak defined symbol
	is linked with a normal defined symbol, the normal defined
	symbol is used with no error.  When a weak undefined
	symbol is linked and the symbol is not defined, the value
	of the weak symbol becomes zero with no error.  On some
	systems, uppercase indicates that a default value has been
	specified.

"W"
"w" The symbol is a weak symbol that has not been specifically
	tagged as a weak object symbol.  When a weak defined
	symbol is linked with a normal defined symbol, the normal
	defined symbol is used with no error.  When a weak
	undefined symbol is linked and the symbol is not defined,
	the value of the symbol is determined in a system-specific
	manner without error.  On some systems, uppercase
	indicates that a default value has been specified.

"-" The symbol is a stabs symbol in an a.out object file.  In
	this case, the next values printed are the stabs other
	field, the stabs desc field, and the stab type.  Stabs
	symbols are used to hold debugging information.

"?" The symbol type is unknown, or object file format
	specific.

