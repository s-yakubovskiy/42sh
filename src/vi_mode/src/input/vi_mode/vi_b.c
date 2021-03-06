/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vi_b.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgorczan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/27 21:25:54 by mgorczan          #+#    #+#             */
/*   Updated: 2019/10/27 21:25:56 by mgorczan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vi_input.h"

int	vi_b(t_line *line, int count)
{
	int		pos;

	pos = line->len - line->left;
	while (count-- && pos > 0)
	{
		ft_key_prev(line->str, line->len, &(line->left));
		pos = line->len - line->left;
	}
	return (0);
}
