/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_elf64.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebonutto <ebonutto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 23:32:37 by x03phy            #+#    #+#             */
/*   Updated: 2025/10/16 16:07:25 by ebonutto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

/* For ft_dprintf() */
#include "ft_printf.h"

#include <stdio.h>

static int is_file_little_endian( const Elf64_Ehdr *elf_header )
{
	if ( elf_header->e_ident[EI_DATA] == ELFDATA2LSB ) // little endian
		return ( 1 );

	else if ( elf_header->e_ident[EI_DATA] == ELFDATA2MSB ) // big endian
		return ( 0 );

	ft_dprintf( 2, "ft_nm: unknown ELF format\n" );

	return ( -1 );
}

static char get_symbol_type64( Elf64_Sym sym, Elf64_Ehdr *elf_header,
										 Elf64_Shdr *sections )
{
	uint32_t type, bind;
	char		c;
	uint16_t shnum, shndx;
	uint64_t flags;

	type = ELF64_ST_TYPE( sym.st_info );
	bind = ELF64_ST_BIND( sym.st_info );

	if ( bind == STB_GNU_UNIQUE ) // 
		return ( 'u' );
	if ( type == STT_GNU_IFUNC ) // 
		return ( 'i' );

	shndx = sym.st_shndx;

	if ( bind == STB_WEAK ) // 
	{
		if ( type == STT_OBJECT )
			return ( shndx == SHN_UNDEF ? 'v' : 'V' );
		return ( shndx == SHN_UNDEF ? 'w' : 'W' );
	}

	if ( shndx == SHN_UNDEF )
		return ( 'U' );
	if ( shndx == SHN_ABS )
		return ( 'A' );

	c = '?';
	shnum = elf_header->e_shnum;

	if ( shndx == SHN_COMMON )
		c = 'C';
	else if ( shndx < shnum )
	{
		type = sections[shndx].sh_type;
		flags = sections[shndx].sh_flags;

		if ( type == SHT_NOBITS )
			c = 'B';
		else if ( !( flags & SHF_WRITE ) )
		{
			if ( flags & SHF_ALLOC && flags & SHF_EXECINSTR )
				c = 'T';
			else
				c = 'R';
		}
		else if ( flags & SHF_EXECINSTR )
			c = 'T';
		else
			c = 'D';
	}

	if ( bind == STB_LOCAL && c != '?' )
		c += 32;

	return ( c );
}

int process_elf64( void *map, t_list **symbols )
{
	Elf64_Ehdr *elf_header;
	int			little;
	Elf64_Shdr *sections;
	Elf64_Sym	 *syms;
	char		  *strtab;
	size_t		sym_count;
	uint8_t		type;
	t_symbol	*symbol;
	t_list *new;

	elf_header = (Elf64_Ehdr *) map;

	little = is_file_little_endian( elf_header );
	if ( little == -1 )
		return ( 0 );

	convert_elf_header64_endian( elf_header, little );

	sections = (Elf64_Shdr *) ( map + elf_header->e_shoff );
	convert_elf_sections64_endian( sections, elf_header->e_shnum, little );

	for ( uint16_t i = 0; i < elf_header->e_shnum; i += 1 )
	{
		if ( sections[i].sh_type == SHT_SYMTAB )
		{
			syms = (Elf64_Sym *) ( map + sections[i].sh_offset );
			sym_count = sections[i].sh_size / sizeof( Elf64_Sym );
			strtab = (char *) ( map + sections[sections[i].sh_link].sh_offset );

			for ( size_t j = 1; j < sym_count; j += 1 )
			{
				convert_elf_symbol64_endian( &syms[j], little );

				type = ELF64_ST_TYPE( syms[j].st_info );
				if ( type == STT_FUNC || type == STT_OBJECT || type == STT_NOTYPE ||
					  type == STT_GNU_IFUNC || type == STT_TLS )
				{
					if ( !syms[j].st_name )
						continue;
					symbol = malloc( sizeof( t_symbol ) );
					if ( !symbol )
						continue;

					symbol->address = syms[j].st_value;
					symbol->type =
						 get_symbol_type64( syms[j], elf_header, sections );
					symbol->name = strtab + syms[j].st_name;

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
	}

	return ( 1 );
}
