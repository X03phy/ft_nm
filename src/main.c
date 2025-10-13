/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: x03phy <x03phy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 23:32:28 by x03phy            #+#    #+#             */
/*   Updated: 2025/10/13 23:32:28 by x03phy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

int main( int argc, char **argv )
{
	t_opts opts;
	int	 error_code;

	if ( !parse_input( &opts, argc, argv ) )
		return ( 1 );

	error_code = ft_nm_wrapper( &opts );

	ft_lstfree( &opts.files );
	return ( error_code );
}
