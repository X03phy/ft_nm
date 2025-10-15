/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_endian64.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebonutto <ebonutto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 23:32:43 by x03phy            #+#    #+#             */
/*   Updated: 2025/10/14 12:18:16 by ebonutto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

#include "ft_bswap.h"

void convert_elf_header64_endian( Elf64_Ehdr *elf_header, int little )
{
	if ( NEED_SWAP( little ) )
	{
		elf_header->e_type = ft_bswap16( elf_header->e_type );
		elf_header->e_machine = ft_bswap16( elf_header->e_machine );
		elf_header->e_version = ft_bswap32( elf_header->e_version );
		elf_header->e_entry = ft_bswap64( elf_header->e_entry );
		elf_header->e_phoff = ft_bswap64( elf_header->e_phoff );
		elf_header->e_shoff = ft_bswap64( elf_header->e_shoff );
		elf_header->e_flags = ft_bswap32( elf_header->e_flags );
		elf_header->e_ehsize = ft_bswap16( elf_header->e_ehsize );
		elf_header->e_phentsize = ft_bswap16( elf_header->e_phentsize );
		elf_header->e_phnum = ft_bswap16( elf_header->e_phnum );
		elf_header->e_shentsize = ft_bswap16( elf_header->e_shentsize );
		elf_header->e_shnum = ft_bswap16( elf_header->e_shnum );
		elf_header->e_shstrndx = ft_bswap16( elf_header->e_shstrndx );
	}
}

void convert_elf_sections64_endian( Elf64_Shdr *sections, uint16_t count,
												int little )
{
	if ( NEED_SWAP( little ) )
	{
		for ( uint16_t i = 0; i < count; i += 1 )
		{
			sections[i].sh_name = ft_bswap32( sections[i].sh_name );
			sections[i].sh_type = ft_bswap32( sections[i].sh_type );
			sections[i].sh_flags = ft_bswap64( sections[i].sh_flags );
			sections[i].sh_addr = ft_bswap64( sections[i].sh_addr );
			sections[i].sh_offset = ft_bswap64( sections[i].sh_offset );
			sections[i].sh_size = ft_bswap64( sections[i].sh_size );
			sections[i].sh_link = ft_bswap32( sections[i].sh_link );
			sections[i].sh_info = ft_bswap32( sections[i].sh_info );
			sections[i].sh_addralign = ft_bswap64( sections[i].sh_addralign );
			sections[i].sh_entsize = ft_bswap64( sections[i].sh_entsize );
		}
	}
}

void convert_elf_symbol64_endian( Elf64_Sym *sym, int little )
{
	if ( NEED_SWAP( little ) )
	{
		sym->st_name = ft_bswap32( sym->st_name );
		sym->st_value = ft_bswap64( sym->st_value );
		sym->st_size = ft_bswap64( sym->st_size );
		sym->st_shndx = ft_bswap16( sym->st_shndx );
	}
}
