/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_archive_and_print.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: x03phy <x03phy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/19 01:18:22 by x03phy            #+#    #+#             */
/*   Updated: 2025/10/26 18:13:51 by x03phy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"
#include "string.h" /* For ft_strlen() */
#include "memory.h" /* For ft_bzero(), ft_memcpy() */
#include "ft_printf.h" /* ft_dprintf() */
#include <ar.h>

/*

#define  ARMAG   "!<arch>\n"    // magic string 
#define  SARMAG   8             // length of magic string
#define  ARFMAG   "`\n"         // header trailer string

struct  ar_hdr                  // file member header
{
    char    ar_name[16];        // '/' terminated file member name
    char    ar_date[12];        // file member date
    char    ar_uid[6]           // file member user identification
    char    ar_gid[6]           // file member group identification
    char    ar_mode[8]          // file member mode (octal)
    char    ar_size[10];        // file member size
    char    ar_fmag[2];         // header trailer string
};

*/

static uint32_t ft_atoi_ar( const char *str )
{
	uint32_t result;
	int i;

	result = 0;
	i = 0;

	while ( i < 10 && str[i] >= '0' && str[i] <= '9' )
	{
		result = result * 10 + ( str[i] - '0' );
		i += 1;	
	}

	return ( result );
}

static char *get_ar_string_table( void *map, size_t size )
{
	struct ar_hdr *header;
	uint32_t offset, member_size;

	offset = SARMAG;

	while ( offset < size )
	{
		if ( offset + sizeof(struct ar_hdr) > size )
			break;

		header = ( struct ar_hdr * )( map + offset );

		member_size = ft_atoi_ar( header->ar_size );
		if ( offset + member_size > size )
			break;

		if ( ft_strncmp( header->ar_name, "//", 2 ) == 0 )
			return ( ( char * ) ( map + offset + sizeof(struct ar_hdr) ) );
		
		offset += sizeof(struct ar_hdr);

		offset += member_size;
		if ( member_size & 1 )
			offset += 1;
	}

	return ( NULL );
}

static void trim_ar_name( char *filename )
{
	int i;
	i = ft_strlen( filename ) - 1;
	while ( i >= 0 && ( filename[i] == '/' || filename[i] == ' ' ) )
	{
		filename[i] = '\0';
		i -= 1;
	}
}

static void get_ar_member_name( char *member_filename, const char *name, const char *string_table )
{
	uint32_t nb;
	int i;

	ft_bzero( member_filename, 256 );

	if ( name[0] == '/' && string_table )
	{
		nb = ft_atoi_ar( name + 1 );
		i = 0;
		while ( string_table[nb + i] && string_table[nb + i] != '\n' )
		{
			member_filename[i] = string_table[nb + i];
			i += 1;
		}
		trim_ar_name( member_filename );
	}
	else
	{	
		ft_memcpy( member_filename, name, 16 );
		trim_ar_name( member_filename );
	}
}

int process_archive_and_print( t_opts *opts, void *map, size_t size )
{
	struct ar_hdr *header;
	const char *string_table;
	uint32_t offset;
	uint32_t member_size;
	void *member_map;
	t_list *symbols;
	char member_filename[256];
	unsigned char *e_ident;
	int exit_code;

	offset = SARMAG; /* Skip ar magic (8 bytes) */
	string_table = get_ar_string_table( map, size );

	while ( offset < size )
	{
		if ( offset + sizeof(struct ar_hdr) > size )
			break;

		header = ( struct ar_hdr * )( map + offset );
		offset += sizeof(struct ar_hdr);

		/* Parse the member size from header */
		member_size = ft_atoi_ar( header->ar_size );
		if ( offset + member_size > size )
			break;

		member_map = map + offset;

		/* Check if member is an ELF file */
		if ( * ( unsigned char * ) member_map == 0x7f &&
			  * ( unsigned char * ) ( member_map + 1 ) == 'E' &&
			  * ( unsigned char * ) ( member_map + 2 ) == 'L' &&
			  * ( unsigned char * ) ( member_map + 3 ) == 'F' )
		{
			symbols = NULL;

			/* Extract member filename */
			get_ar_member_name( member_filename, header->ar_name, string_table );

			/* Process the ELF member */
			e_ident = ( unsigned char * ) member_map;
			if ( e_ident[EI_CLASS] == ELFCLASS64 )
				exit_code = process_elf64( member_map, &symbols );
			else if ( e_ident[EI_CLASS] == ELFCLASS32 )
				exit_code = process_elf32( member_map, &symbols );
			else
			{
				ft_dprintf( 2, "ft_nm: « %s » invalid ELF class\n", member_filename );
				return ( 0 );
			}

			if ( !exit_code )
				return ( 0 );

			if ( symbols )
			{
				ft_dprintf( 1, "\n%s:\n", member_filename );
				if ( e_ident[EI_CLASS] == ELFCLASS64 )
					print_symbols( opts, symbols, 1 );
				else
					print_symbols( opts, symbols, 0 );
			}
			else
				ft_dprintf( 2, "ft_nm: %s: no symbol\n", member_filename );
			ft_lstfree( &symbols );
		}

		/* Move to next member (ar members are 2-byte aligned) */
		offset += member_size;
		if ( member_size & 1 )
			offset += 1;
	}

	return ( 1 );
}
