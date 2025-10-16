/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_nm_symbols.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebonutto <ebonutto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 12:38:44 by ebonutto          #+#    #+#             */
/*   Updated: 2025/10/16 12:51:39 by ebonutto         ###   ########.fr       */
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
		while ( s1->name[i] == '_' )
			i += 1;
		while ( s2->name[j] == '_' )
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
	if ( !flag_active( opts->flags, FLAG_P ) )
	{	
		ft_list_sort( &symbols, symbol_name_cmp );

		if ( flag_active( opts->flags, FLAG_R ) )
			ft_lstrev( &symbols );	
	}

	while ( symbols )
	{
		if ( ( (t_symbol *) ( symbols->content ) )->type == 'w' ||
			  ( (t_symbol *) ( symbols->content ) )->type == 'U' )
			printf( "%16c %c %s\n", ' ',
					  ( (t_symbol *) ( symbols->content ) )->type,
					  ( (t_symbol *) ( symbols->content ) )->name );
		else
			printf( "%016lx %c %s\n",
					  ( (t_symbol *) ( symbols->content ) )->address,
					  ( (t_symbol *) ( symbols->content ) )->type,
					  ( (t_symbol *) ( symbols->content ) )->name );
		symbols = symbols->next;
	}
}
