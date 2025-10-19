/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_symbols.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: x03phy <x03phy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 12:38:44 by ebonutto          #+#    #+#             */
/*   Updated: 2025/10/19 23:52:38 by x03phy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"
#include <stdio.h>
#include "ft_printf.h"
#include "char.h"
#include "string.h"
#include <unistd.h>

static int symbol_name_cmp( t_symbol *s1, t_symbol *s2 )
{
	size_t i = 0, j = 0;
	char   l1, l2;

	while ( s1->name[i] && s2->name[j] )
	{
		while ( !ft_isalnum( s1->name[i] ) )
			i += 1;
		while ( !ft_isalnum( s2->name[j] ) )
			j += 1;

		l1 = ft_tolower( s1->name[i] );
		l2 = ft_tolower( s2->name[j] );

		if ( l1 != l2 )
			return ( l1 - l2 );

		i += 1;
		j += 1;
	}

	if ( s1->name[i] == '\0' && s2->name[j] == '\0' && i < j )
		return ( 1 );

	return ( s1->name[i] - s2->name[j] );
}

static void	write_hex64(uint64_t n)
{
	char	hex[16];
	int		i;

	for (i = 0; i < 16; i++)
		hex[i] = '0';
	i = 15;
	while (n)
	{
		uint8_t d = n % 16;
		hex[i--] = (d < 10) ? d + '0' : d - 10 + 'a';
		n /= 16;
	}
	write(1, hex, 16);
}

void	print_symbol(uint64_t addr, char type, const char *name)
{
	write_hex64(addr);
	write(1, " ", 1);
	write(1, &type, 1);
	write(1, " ", 1);
	while (*name)
		write(1, name++, 1);
	write(1, "\n", 1);
}

void print_symbols( t_opts *opts, t_list *symbols )
{
	t_symbol *symbol;

	/* Sort if needed */
	if ( !flag_active( opts->flags, FLAG_P ) )
	{	
		ft_list_sort( &symbols, symbol_name_cmp );
		if ( flag_active( opts->flags, FLAG_R ) )
			ft_lstrev( &symbols );
	}

	/* Print all symbols */
	while ( symbols )
	{
		symbol = ( t_symbol * ) ( symbols->content );

		if ( symbol->name && symbol->name[0] )
		{
			char t = symbol->type;
			if ( flag_active( opts->flags, FLAG_U ) )
			{
				if ( t != 'w' && t != 'U' )
				{
					symbols = symbols->next;
					continue;
				}
			}
			else if ( flag_active( opts->flags, FLAG_G ) )
			{
				if ( t != 'w' && ft_islower( t ) )
				{
					symbols = symbols->next;
					continue;
				}
			}
			else if ( !flag_active( opts->flags, FLAG_A ) )
			{
				if ( t == 'a' || t == 'A' )
				{
					symbols = symbols->next;
					continue;
				}
			}
			if ( t == 'w' || t == 'U' )
				ft_dprintf( 1, "                 %c %s\n", t, symbol->name );
			else
				print_symbol( symbol->address, t, symbol->name );
		}
		symbols = symbols->next;
	}
}
