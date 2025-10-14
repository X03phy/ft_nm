/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebonutto <ebonutto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 23:32:32 by x03phy            #+#    #+#             */
/*   Updated: 2025/10/14 12:18:27 by ebonutto         ###   ########.fr       */
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
