/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nm.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebonutto <ebonutto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 23:32:19 by x03phy            #+#    #+#             */
/*   Updated: 2025/10/14 12:15:54 by ebonutto         ###   ########.fr       */
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

/* Structures */
typedef struct s_opts
{
	int	  flags;
	t_list *files;
	int	  nb_files;
} t_opts;

/* Prototypes */
/* Parsing */
int parse_input( t_opts *opts, int argc, char **argv );

/* endian */
void convert_elf_header64_endian( Elf64_Ehdr *elf_header, int little );
void convert_elf_sections64_endian( Elf64_Shdr *sections, uint16_t count,
											 int little );
void convert_elf_symbol64_endian( Elf64_Sym *sym, int little );

/* ft_nm */
int process_elf32( void *map );
int process_elf64( void *map );
int process_file( const char *filename, int fd, struct stat *st, void *map );
int ft_nm_wrapper( t_opts *opts );

#endif
