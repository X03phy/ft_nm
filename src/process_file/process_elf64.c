/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_elf64.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: x03phy <x03phy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 23:32:37 by x03phy            #+#    #+#             */
/*   Updated: 2025/10/22 10:33:53 by x03phy           ###   ########.fr       */
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

#include <stdio.h>
static void print_type_debug( uint32_t st_type, uint32_t sh_type, uint32_t st_bind, uint64_t sh_flags, const char *name)
{
  dprintf(1, "section name: %s\n", name);
  dprintf(1, "st_type: %d\n", st_type);
  dprintf(1, "st_bind: %d\n", st_bind);
  dprintf(1, "sh_type: %d\n", sh_type);
  dprintf(1, "sh_flags: %lx\n", sh_flags);
}


static char get_symbol_type64( Elf64_Sym sym, Elf64_Ehdr *elf_header, Elf64_Shdr *sections, const char *name )
{
	char c;
	uint32_t st_type, st_bind, sh_type;
	uint16_t e_shnum, st_shndx;
	uint64_t sh_flags;

	st_type = ELF64_ST_TYPE( sym.st_info );
	st_bind = ELF64_ST_BIND( sym.st_info );
	e_shnum = elf_header->e_shnum;
	st_shndx = sym.st_shndx;

	if ( st_bind == STB_GNU_UNIQUE ) // 
		return ( 'u' );
	if ( st_type == STT_GNU_IFUNC ) // 
		return ( 'i' );

	c = '?';

	if ( st_shndx == SHN_UNDEF )
		c = 'U';
	else if ( st_shndx == SHN_ABS )
		c = 'A';
	else if ( st_shndx == SHN_COMMON )
		c = 'C';
	if ( st_bind == STB_WEAK ) // 
	{
		if ( st_type == STT_OBJECT )
			return ( st_shndx == SHN_UNDEF ? 'v' : 'V' );
		return ( st_shndx == SHN_UNDEF ? 'w' : 'W' );
	}

	// .debug_abbrev
	else if ( st_shndx < e_shnum )
	{
		sh_type = sections[st_shndx].sh_type;
		sh_flags = sections[st_shndx].sh_flags;

		(void)sh_type;
		(void)sh_flags;

		print_type_debug( st_type, sh_type, st_bind, sh_flags, name );
	}
	// 	type = sections[st_shndx].sh_type;
	// 	flags = sections[st_shndx].sh_flags;

	// 	if ( type == SHT_NOBITS )
	// 		c = 'B';
	// 	else if ( !( flags & SHF_WRITE ) )
	// 	{
	// 		if ( flags & SHF_ALLOC && flags & SHF_EXECINSTR )
	// 			c = 'T';
	// 		else
	// 			c = 'R';
	// 	}
	// 	else if ( flags & SHF_EXECINSTR )
	// 		c = 'T';
	// 	else
	// 		c = 'D';
	// }

	if ( st_bind == STB_LOCAL && c != '?' )
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

				symbol = malloc( sizeof( t_symbol ) );
				if ( !symbol )
					continue;

				symbol->address = syms[j].st_value;

				uint32_t st_type = ELF64_ST_TYPE(syms[j].st_info);
				if (st_type == STT_SECTION)
				{
					// le nom vient de la table des noms de sections (.shstrtab)
					uint16_t sh_index = syms[j].st_shndx;
					if (sh_index < elf_header->e_shnum)
					{
						Elf64_Shdr *shstrtab = &sections[elf_header->e_shstrndx];
						char *shstrtab_base = (char *)map + shstrtab->sh_offset;
						symbol->name = shstrtab_base + sections[sh_index].sh_name;
					}
					else
						symbol->name = "(invalid section)";
				}
				else
				{
					// nom normal venant de .strtab
					if (syms[j].st_name >= sections[sections[i].sh_link].sh_size)
						continue;
					symbol->name = (char *)(strtab + syms[j].st_name);
				}

				symbol->type = get_symbol_type64( syms[j], elf_header, sections, symbol->name );

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
