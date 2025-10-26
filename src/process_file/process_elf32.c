/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_elf32.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: x03phy <x03phy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/26 19:14:22 by x03phy            #+#    #+#             */
/*   Updated: 2025/10/26 19:27:13 by x03phy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"
#include "ft_printf.h" /* For ft_dprintf() */
#include "string.h" /* For ft_strncmp() */
#include <stdio.h>

static int is_file_little_endian( const Elf32_Ehdr *elf_header )
{
	if ( elf_header->e_ident[EI_DATA] == ELFDATA2LSB ) // little endian
		return ( 1 );
	else if ( elf_header->e_ident[EI_DATA] == ELFDATA2MSB ) // big endian
		return ( 0 );
	ft_dprintf( 2, "ft_nm: unknown ELF format\n" );

	return ( -1 );
}

static char get_symbol_type32( Elf32_Sym sym, Elf32_Ehdr *elf_header, Elf32_Shdr *sections )
{
	char c;
	uint32_t st_type, st_bind, sh_type;
	uint16_t st_shndx;
	uint32_t sh_flags;

	st_type = ELF32_ST_TYPE(sym.st_info);
	st_bind = ELF32_ST_BIND(sym.st_info);
	st_shndx = sym.st_shndx;

	// Special cases GNU
	if ( st_bind == STB_GNU_UNIQUE )
		return ( 'u' );
	if ( st_type == STT_GNU_IFUNC )
		return ( 'i' );

	c = '?';

	// Undefine, absolute or common
	if ( st_shndx == SHN_UNDEF )
		c = 'U';
	else if ( st_shndx == SHN_ABS )
		c = 'A';
	else if ( st_shndx == SHN_COMMON )
		c = 'C';

	// Weak symbol
	if ( st_bind == STB_WEAK )
	{
		if ( st_type == STT_OBJECT )
			return ( st_shndx == SHN_UNDEF ? 'v' : 'V' );
		return ( st_shndx == SHN_UNDEF ? 'w' : 'W' );
	}

	// Analyse the section if the index is valid
	else if ( st_shndx < elf_header->e_shnum && c == '?' )
	{
		sh_type = sections[st_shndx].sh_type;
		sh_flags = sections[st_shndx].sh_flags;

		if ( sh_type == SHT_NOBITS )
			c = 'B';
		// Read-only section
		else if ( !( sh_flags & SHF_WRITE ) )
		{
			if ( ( sh_flags & SHF_ALLOC ) && ( sh_flags & SHF_EXECINSTR ) )
				c = 'T';  // Executable code
			else
				c = 'R';  // Read-only data
		}
		// Executable section
		else if ( sh_flags & SHF_EXECINSTR )
			c = 'T';
		// Modif data section
		else
			c = 'D';
	}

	// Convert to lower cases for local symbols
	if ( st_bind == STB_LOCAL && c != '?' )
		c += 32;
	
	return ( c );
}

int process_elf32( t_list **symbols, void *map )
{
	Elf32_Ehdr *elf_header;
	int little;
	Elf32_Shdr *sections;
	char *shstrtab;
	Elf32_Sym *syms;
	char *strtab;
	size_t sym_count;
	t_symbol *symbol;
	t_list *new;

	elf_header = ( Elf32_Ehdr * ) map;

	little = is_file_little_endian( elf_header );
	if ( little == -1 )
		return ( 0 );

	convert_elf_header32_endian( elf_header, little );

	sections = ( Elf32_Shdr * ) ( map + elf_header->e_shoff );
	convert_elf_sections32_endian( sections, elf_header->e_shnum, little );
	shstrtab = ( char * ) ( map + sections[elf_header->e_shstrndx].sh_offset );

	for ( uint16_t i = 0; i < elf_header->e_shnum; i += 1 )
	{
		if ( sections[i].sh_type == SHT_SYMTAB )
		{
			syms = ( Elf32_Sym * ) ( map + sections[i].sh_offset );
			sym_count = sections[i].sh_size / sizeof( Elf32_Sym );
			strtab = ( char * ) ( map + sections[sections[i].sh_link].sh_offset );

			for ( size_t j = 1; j < sym_count; j += 1 )
			{
				convert_elf_symbol32_endian( &syms[j], little );

				symbol = malloc( sizeof( t_symbol ) );
				if ( !symbol )
					continue;

				symbol->address = syms[j].st_value; /* Get the address */
								if ( ELF64_ST_TYPE(syms[j].st_info) == STT_SECTION &&
					syms[j].st_shndx < elf_header->e_shnum )
				{
					symbol->name = shstrtab + sections[syms[j].st_shndx].sh_name;
				}
				else
					symbol->name = strtab + syms[j].st_name;
				symbol->type = get_symbol_type32( syms[j], elf_header, sections );

				new = ft_lstnew( symbol );
				if ( !new )
				{
					free( symbol );
					continue;
				}

				ft_lstadd_back( symbols, new );
			}
		}
	}

	return ( 1 );
}
