#!/bin/bash

AUTHOR="ebonutto <ebonutto@student.42.fr>"

file="main.c"
	if ! grep -q "By: $AUTHOR" "$file"; then
		echo "Ajout du header 42 à $file"
		TMP=$(mktemp)
		cat << EOF > "$TMP"
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   $(printf "%-50s" "$(basename "$file")") :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: $AUTHOR$(printf "%*s" $((50-${#AUTHOR})) "")#+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: $(date +"%Y/%m/%d %H:%M:%S") by ebonutto          #+#    #+#             */
/*   Updated: $(date +"%Y/%m/%d %H:%M:%S") by ebonutto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

EOF
        cat "$file" >> "$TMP"
        mv "$TMP" "$file"
    fi
done
