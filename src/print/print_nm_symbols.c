/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_nm_symbols.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebonutto <ebonutto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 12:38:44 by ebonutto          #+#    #+#             */
/*   Updated: 2025/10/17 13:05:57 by ebonutto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"
#include <stdio.h>

#include "char.h"

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

void print_nm_symbols( t_opts *opts, t_list *symbols )
{
	char t;

	if ( !flag_active( opts->flags, FLAG_P ) )
	{	
		ft_list_sort( &symbols, symbol_name_cmp );

		if ( flag_active( opts->flags, FLAG_R ) )
			ft_lstrev( &symbols );
	}

	while ( symbols )
	{
		t = ( (t_symbol *) ( symbols->content ) )->type;
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
			printf( "%16c %c %s\n", ' ', t, ( (t_symbol *) ( symbols->content ) )->name );
		else
			printf( "%016lx %c %s\n", ( (t_symbol *) ( symbols->content ) )->address, t, ( (t_symbol *) ( symbols->content ) )->name );
		symbols = symbols->next;
	}
}
