/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbearded <sbearded@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/20 17:55:23 by mgorczan          #+#    #+#             */
/*   Updated: 2019/10/26 13:22:43 by sbearded         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static int	envin_quote(char **chang_line, int i, char **env)
{
	int		lenght;
	char	*env_verb;

	lenght = i;
	env = NULL;
	env_verb = replace_param(*chang_line, i, &lenght);
	if (!ft_strcmp(env_verb, " "))
		cut_str(chang_line, i, lenght);
	else if (ft_strcmp(env_verb, "$"))
	{
		replace_str(chang_line, i, lenght, env_verb);
		i += ft_strlen(env_verb);
	}
	else
		++i;
	free(env_verb);
	return (i);
}

static int	miss_quote(char **chang_line, int i, char **env)
{
	if ((*chang_line)[i] == '\'')
	{
		++i;
		while ((*chang_line)[i] && (*chang_line)[i] != '\'')
			++i;
		i += (*chang_line)[i] ? 1 : 0;
	}
	else if ((*chang_line)[i] == '\"')
	{
		++i;
		while ((*chang_line)[i] && (*chang_line)[i] != '\"')
		{
			if ((*chang_line)[i] == '$')
				i = envin_quote(chang_line, i, env);
			else
				++i;
		}
		i += (*chang_line)[i] ? 1 : 0;
	}
	return (i);
}

void		replace_env_else(char **chang_line, int *i, int *lenght)
{
	char	*env_verb;

	env_verb = replace_param(*chang_line, *i, lenght);
	if (!ft_strcmp(env_verb, " "))
		cut_str(chang_line, *i, *lenght);
	else
	{
		if (ft_strcmp(env_verb, "$"))
			replace_str(chang_line, *i, *lenght, env_verb);
		i += ft_strcmp(env_verb, "$") ? ft_strlen(env_verb) : 1;
	}
	free(env_verb);
}

char		*replace_env(char *chang_line, char **env)
{
	int		i;
	int		lenght;

	i = 0;
	while (chang_line && chang_line[i])
	{
		if (chang_line[i] == '\'' || chang_line[i] == '\"')
			i = miss_quote(&chang_line, i, env);
		else if (chang_line[i] == '$')
			replace_env_else(&chang_line, &i, &lenght);
		else
			++i;
	}
	return (chang_line);
}
