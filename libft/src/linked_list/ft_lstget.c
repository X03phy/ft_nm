/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstget.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebonutto <ebonutto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 12:14:04 by ebonutto          #+#    #+#             */
/*   Updated: 2025/10/16 12:17:13 by ebonutto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "linked_list.h"

t_list *ft_lstget( t_list *lst, size_t i )
{
	size_t j = 0;

	while ( lst && j < i )
	{
		lst = lst->next;
		j += 1;
	}

	return ( lst );
}
