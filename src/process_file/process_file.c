/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_file.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: x03phy <x03phy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 23:32:39 by x03phy            #+#    #+#             */
/*   Updated: 2025/11/26 01:31:04 by x03phy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"
#include "ft_printf.h" /* For ft_dprintf() */
#include "string.h" /* For ft_strncmp() */

int process_file( t_list **symbols, const char *filename, void *map )
{
	unsigned char *e_ident;
	int exit_code;

	e_ident = ( unsigned char * ) map;

	/* Process elf */
	if ( e_ident[0] != 0x7F || e_ident[1] != 'E' || e_ident[2] != 'L' || e_ident[3] != 'F' )
	{
		ft_dprintf( 2, "ft_nm: « %s »: not an ELF\n", filename );
		return ( 0 );
	}

	if ( e_ident[EI_CLASS] == ELFCLASS64 ) /* Process elf 64 */
	{
		if ( ( ( Elf64_Ehdr * ) map )->e_machine == EM_X86_64 ) /* Is x64 */
			exit_code = process_elf64( symbols, map );
		else
		{
			ft_dprintf( 2, "ft_nm: « %s »: invalid architecture\n", filename );
			return ( 0 );
		}
	}
	else if ( e_ident[EI_CLASS] == ELFCLASS32 ) /* Process elf 32 */
	{
		if ( ( ( Elf64_Ehdr * ) map )->e_machine == EM_386 ) /* Is x86 */
			exit_code = process_elf32( symbols, map );
		else
		{
			ft_dprintf( 2, "ft_nm: « %s »: invalid architecture\n", filename );
			return ( 0 );
		}
	}
	else
	{
		ft_dprintf( 2, "ft_nm: « %s » invalid ELF class\n", filename );
		return ( 0 );
	}

	return ( exit_code );
}
