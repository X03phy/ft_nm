/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   endian64.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: x03phy <x03phy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 23:32:14 by x03phy            #+#    #+#             */
/*   Updated: 2025/10/13 23:32:15 by x03phy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENDIAN64_H
#define ENDIAN64_H

/* Headers */
/* For uintX_t */
#include <stdint.h>

/* For ft_bwapX() */
#include "ft_bswap.h"

#include <elf.h>

/* Macros */
#define NEED_SWAP( file_is_little_endian )                                     \
	( file_is_little_endian != ( __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__ ) )

/* Prototypes */
void convert_elf_header_endian( Elf64_Ehdr *elf_header, int little );
void convert_elf_sections_endian( Elf64_Shdr *sections, uint16_t count,
											 int little );
void convert_elf_symbol_endian( Elf64_Sym *sym, int little );

#endif
