/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nm.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: x03phy <x03phy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 23:32:19 by x03phy            #+#    #+#             */
/*   Updated: 2025/10/16 23:47:17 by x03phy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_NM_H
#define FT_NM_H

/* Headers */
/* For struct stat, fstat() */
#include <sys/stat.h>

/* For t_list */
#include "linked_list.h"

#include <endian.h>

#include <elf.h>

/* Macros */
#define NEED_SWAP( file_is_little_endian )                                     \
	( file_is_little_endian != ( __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__ ) )

#define FLAG_A 0
#define FLAG_G 1
#define FLAG_U 2
#define FLAG_R 3
#define FLAG_P 4

/* Structures */
typedef struct s_symbol
{
	uint64_t address;
	char		type;
	char	  *name;
} t_symbol;

typedef struct s_opts
{
	int	  flags;
	t_list *files;
	int	  nb_files;
} t_opts;

/* Prototypes */
/* Parsing */
int parse_input( t_opts *opts, int argc, char **argv );
static inline int flag_active( int n, int f )
{
	return ( ( n >> f ) & 1 );
}

/* print_symbols */
void print_nm_symbols( t_opts *opts, t_list *symbols );

/* endian */
/* 64 archi */
void convert_elf_header64_endian( Elf64_Ehdr *elf_header, int little );
void convert_elf_sections64_endian( Elf64_Shdr *sections, uint16_t count,
												int little );
void convert_elf_symbol64_endian( Elf64_Sym *sym, int little );

/* 32 archi */
void convert_elf_header32_endian( Elf32_Ehdr *elf_header, int little );
void convert_elf_sections32_endian( Elf32_Shdr *sections, uint16_t count,
												int little );
void convert_elf_symbol32_endian( Elf32_Sym *sym, int little );

/* ft_nm */
// int process_elf32( void *map );
int process_elf64( void *map, t_list **symbols );
int process_file( const char *filename, int fd, struct stat *st, void *map,
						t_list **symbols );
int ft_nm_wrapper( t_opts *opts );

#endif
