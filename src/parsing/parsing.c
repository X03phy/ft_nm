/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: x03phy <x03phy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 23:32:32 by x03phy            #+#    #+#             */
/*   Updated: 2025/10/16 23:49:02 by x03phy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

/* For ft_bzero() */
#include "memory.h"

/* For perror() */
#include <stdio.h>

int parse_input( t_opts *opts, int argc, char **argv )
{
	t_list *new;

	ft_bzero( opts, sizeof( t_opts ) );

	for ( int i = 1; i < argc; i += 1 )
	{
		if ( argv[i][0] == '-' && argv[i][1] && !argv[i][2] )
		{
			if ( argv[i][1] == 'a' )
				opts->flags |= 1 << FLAG_A;
			if ( argv[i][1] == 'g' )
				opts->flags |= 1 << FLAG_G;
			if ( argv[i][1] == 'u' )
				opts->flags |= 1 << FLAG_U;
			if ( argv[i][1] == 'r' )
				opts->flags |= 1 << FLAG_R;
			if ( argv[i][1] == 'p' )
				opts->flags |= 1 << FLAG_P;
			continue;
		}
		
		new = ft_lstnew( argv[i] );
		if ( !new )
		{
			perror( "ft_lstnew()" );
			ft_lstfree( &opts->files );
			return ( 0 );
		}
		ft_lstadd_back( &( opts->files ), new );
		opts->nb_files += 1;
	}

	if ( opts->files == NULL )
	{
		new = ft_lstnew( "a.out" );
		if ( !new )
		{
			perror( "ft_lstnew()" );
			ft_lstfree( &opts->files );
			return ( 0 );
		}
		ft_lstadd_back( &( opts->files ), new );
		opts->nb_files += 1;
	}

	return ( 1 );
}
