/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_param.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbearded <sbearded@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/24 12:01:12 by sbearded          #+#    #+#             */
/*   Updated: 2019/10/26 12:20:40 by sbearded         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		free_exp(t_exp *exp)
{
	free(exp->param);
	free(exp->word);
	free(exp->action);
}

char		*do_replace(t_exp *exp)
{
	char	*(*func)(t_exp *);
	char	*error;

	func = phash_search(exp->action, HASH_PARAM_EXP);
	if (func)
		return (func(exp));
	error = ft_strjoin("42sh: parameter expansion: illegal option ", exp->action);
	parser_error_set(error);
	free_exp(exp);
	return (" ");
}

char		*parse_action(char *line, int *length, t_exp *exp)
{
	int	counter;
	int	i;

	counter = 0;
	if (exp->flag_exp == 0 || line[*length] == '}')
	{
		free(exp->param);
		if (exp->env)
			return (exp->env);
		return (" ");
	}
	i = *length;
	while (line[*length] && !ft_isdigit(line[*length])
			&& !ft_isalpha(line[*length]) && line[*length] != '}')
		++(*length);
	exp->action = ft_strsub(line, i, (*length) - i);
	i = *length;
	while (line[*length] && line[*length] != '}')
		++(*length);
	exp->word = ft_strsub(line, i, (*length) - i);
	return (do_replace(exp));
}

char		*replace_param(char *line, int i, int *length)
{
	t_exp	exp;

	*length = ++i;
	if (line[i] == '{')
	{
		exp.flag_exp = 1;
		++(*length);
	}
	else if (ft_isalpha(line[i]) || ft_isdigit(line[i]))
		exp.flag_exp = 0;
	else
		return ("$");
	exp.flag_hash = 0;
	if (line[(*length)] == '#')
	{
		exp.flag_hash = 1;
		++(*length);
	}
	while (ft_isalpha(line[(*length)]) || ft_isdigit(line[(*length)]))
		++(*length);
	exp.param = ft_strsub(line, i + exp.flag_exp, (*length) - i - exp.flag_exp);
	exp.env = get_env(exp.param);
	return (parse_action(line, length, &exp));
}
