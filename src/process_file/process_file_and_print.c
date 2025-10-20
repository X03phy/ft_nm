/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_file_and_print.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: x03phy <x03phy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 23:32:39 by x03phy            #+#    #+#             */
/*   Updated: 2025/10/20 09:53:49 by x03phy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"
#include "ft_printf.h" /* For ft_dprintf() */
#include "string.h"
#include <ar.h>
#include <stdio.h>

int process_file_and_print( t_opts *opts, const char *filename, size_t size, void *map )
{
	t_list *symbols;
	unsigned char *e_ident;
	int exit_code;
	
	symbols = NULL;
	e_ident = ( unsigned char * ) map;

	/* Process archive */
	if ( ft_strncmp( ARMAG, ( const char * ) e_ident, SARMAG ) == 0 )
	{
		if ( opts->nb_files > 1 )
			ft_dprintf( 1, "\n%s:\n", filename );
		return ( process_archive_and_print( opts, map, size ) );
	}

	/* Process elf */
	if ( e_ident[0] != 0x7F || e_ident[1] != 'E' || e_ident[2] != 'L' || e_ident[3] != 'F' )
	{
		ft_dprintf( 2, "ft_nm: « %s »: not an ELF or archive file\n", filename );
		return ( 0 );
	}

	if ( e_ident[EI_CLASS] == ELFCLASS64 ) /* Process elf 64 */
		exit_code = process_elf64( map, &symbols );
	else if ( e_ident[EI_CLASS] == ELFCLASS32 ) /* Process elf 32 */
	 	exit_code = process_elf32( map, &symbols );
	else
	{
		ft_dprintf( 2, "ft_nm: « %s » invalid ELF class\n", filename );
		return ( 0 );
	}

	if ( exit_code == 0 )
		return ( 0 );

	if ( symbols )
	{
			if ( opts->nb_files > 1 )
		ft_dprintf( 1, "\n%s:\n", filename );
		print_symbols( opts, symbols );
	}
	else
		ft_dprintf( 2, "ft_nm: %s: no symbol\n", filename );

	return ( 1 );
}
