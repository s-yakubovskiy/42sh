/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colon.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbearded <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/27 21:40:43 by sbearded          #+#    #+#             */
/*   Updated: 2019/10/27 21:40:43 by sbearded         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*param_exp_colon(t_exp *exp)
{
	return (ft_strdup(exp->env));
}
