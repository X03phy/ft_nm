/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nm.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: x03phy <x03phy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 23:32:08 by x03phy            #+#    #+#             */
/*   Updated: 2025/10/26 19:18:11 by x03phy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"
#include "ft_printf.h" /* For ft_dprintf() */
#include <fcntl.h> /* For open() */
#include <unistd.h> /* For close() */
#include <stdio.h> /* For perror() */
#include <errno.h> /* For errno */
#include <sys/mman.h> /* For mmap(), munmap() */

static int init_map( const char *filename, int *fd, struct stat *st, void **map )
{
	/* Open File */
	*fd = open( filename, O_RDONLY );
	if ( *fd == -1 )
	{
		if ( errno == ENOENT )
			ft_dprintf( 2, "ft_nm: « %s »: no such file\n", filename );
		else
		{
			ft_dprintf( 2, "ft_nm: %s: ", filename );
			perror( NULL );
		}
		return ( 0 );
	}

	/* Initialize stat */
	if ( fstat( *fd, st ) < 0 )
	{
		perror( "fstat()" );
		close( *fd );
		return ( 0 );
	}

	/* Check if it's a directory */
	if ( S_ISDIR( ( *st ).st_mode ) )
	{
		ft_dprintf( 2, "ft_nm: Warning : « %s » is a directory\n", filename );
		close( *fd );
		return ( 0 );
	}

	/* Check file size */
	if ( st->st_size == 0 )
	{
		ft_dprintf( 2, "ft_nm: « %s »: empty file\n", filename );
		close( *fd );
		return ( 0 );
	}

	/* Map File */
	*map = mmap( NULL, ( *st ).st_size, PROT_READ, MAP_PRIVATE, *fd, 0 );
	if ( *map == MAP_FAILED )
	{
		perror( "mmap()" );
		close( *fd );
		return ( 0 );
	}

	return ( 1 );
}

static void cleanup_map( int fd, void *map, size_t size )
{
	if ( map )
		munmap( map, size );
	if ( fd >= 0 )
		close( fd );
}

static int ft_nm( t_opts *opts, const char *filename )
{
	int fd;
	struct stat st;
	void *map;
	t_list *symbols;

	fd = -1;
	map = NULL;
	if ( !init_map( filename, &fd, &st, &map ) )
		return ( 0 );
	symbols = NULL;
	if ( !process_file( &symbols, filename, map ) )
	{
		cleanup_map( fd, map, st.st_size );
		ft_lstfree( &symbols );
		return ( 0 );
	}
	print_symbols( opts, symbols, ( ( ( unsigned char * ) map )[EI_CLASS] == ELFCLASS64 ) );

	cleanup_map( fd, map, st.st_size );
	ft_lstclear( &symbols, free );
	return ( 1 );
}

int ft_nm_wrapper( t_opts *opts )
{
	int error_code;
	t_list *node;
	const char *filename;

	error_code = 0;
	node = opts->files;

	while ( node )
	{
		filename = ( const char * ) node->content;
		if ( !ft_nm( opts, filename ) )
			error_code = 1;
		node = node->next;
	}

	return ( error_code );
}
