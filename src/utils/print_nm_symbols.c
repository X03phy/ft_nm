/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_nm_symbols.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebonutto <ebonutto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 12:38:44 by ebonutto          #+#    #+#             */
/*   Updated: 2025/10/14 16:11:24 by ebonutto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"
#include <stdio.h>
#include "string.h"
static int symbol_content_cmp( t_symbol *s1, t_symbol *s2 )
{
	return ft_strcmp( s1->name, s2->name );
}

void print_nm_symbols( t_opts *opts, t_list *symbols )
{
	(void) opts;
	if ( 1 )
		ft_list_sort( &symbols, symbol_content_cmp );
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
