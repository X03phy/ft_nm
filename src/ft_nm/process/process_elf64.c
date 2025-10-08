#include "ft_nm.h"

/* For ft_dprintf() */
#include "ft_printf.h"

#include <elf.h>
#include <stdio.h>
static char get_symbol_type64( Elf64_Sym sym, Elf64_Shdr *sections )
{
	if ( sym.st_shndx == SHN_UNDEF )
		return ( 'U' );
	if ( sym.st_shndx == SHN_ABS )
		return ( 'A' );
	if ( sym.st_shndx == SHN_COMMON )
		return ( 'C' );

	Elf64_Shdr shdr = sections[sym.st_shndx];

	if ( shdr.sh_type == SHT_NOBITS && ( shdr.sh_flags & ( SHF_ALLOC | SHF_WRITE ) ) )
		return ( 'b' );
	if ( ( shdr.sh_type == SHT_PROGBITS || shdr.sh_type == SHT_DYNAMIC ) && ( shdr.sh_flags & ( SHF_ALLOC | SHF_WRITE ) ) )
        return 'D';
	return ( '?' );
}


int process_elf64( void *map )
{
	Elf64_Ehdr *ehdr;
	Elf64_Shdr *sections;
	Elf64_Sym  *syms;
	size_t     sym_count;

	ehdr = ( Elf64_Ehdr * )map;
	sections = ( Elf64_Shdr * )( map + ehdr->e_shoff );

	for ( int i = 0; i < ehdr->e_shnum; i += 1 )
	{
		if ( sections[i].sh_type == SHT_SYMTAB || sections[i].sh_type == SHT_DYNSYM )
		{
			syms = ( Elf64_Sym * )( map + sections[i].sh_offset );
			sym_count = sections[i].sh_size / sizeof( Elf64_Sym );

			const char *strtab = ( const char * )( map + sections[sections[i].sh_link].sh_offset );

			for ( size_t j = 0; j < sym_count; j += 1 )
			{
				if (ELF64_ST_TYPE(syms[i].st_info) == STT_FILE)
					continue;
				if (ELF64_ST_BIND(syms[i].st_info) == STB_LOCAL)
					continue;
				if ( syms[j].st_name == 0 )
					continue;

				const char *sym_name = strtab + syms[j].st_name;

				char type = get_symbol_type64( syms[j], sections );
				// Affiche l’adresse, le type et le nom
				printf("%016lx %c %s\n", syms[j].st_value, type, sym_name);
			}
		}
	}

	return ( 1 );
}
