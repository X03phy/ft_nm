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

