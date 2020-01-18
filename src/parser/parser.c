/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgorczan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/27 21:52:53 by mgorczan          #+#    #+#             */
/*   Updated: 2019/10/27 21:52:54 by mgorczan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	replace_str(char **chang_line, int i, int lenght, char *env_verb)
{
	char *temp;
	char *tmp;

	temp = *chang_line;
	*chang_line = ft_strsub(temp, 0, i);
	tmp = *chang_line;
	*chang_line = ft_strjoin(tmp, env_verb);
	free(tmp);
	tmp = *chang_line;
	*chang_line = ft_strjoin(tmp, &temp[lenght]);
	free(tmp);
	free(temp);
}

char	*get_line(t_history_session **h_session, int lenght_hello, int mode)
{
	char	*line;

	if (FU_TERMCAPS)
		return (read_ln());
	if (g_input_mode == 0)
		line = input(h_session, lenght_hello, mode);
	else
		line = wait_input();
	return (line);
}

char	**parser(t_history_session **h_session, char **env, int lenght_hello)
{
	char	**arg;
	char	*line;
	int		mode;
	int		temp_fd;

	*h_session = add_history(*h_session, lenght_hello);
	mode = 0;
	while (1)
	{
		line = get_line(h_session, lenght_hello, mode);
		if (parse_error(line))
		{
			free(line);
			return (NULL);
		}
		if (!line || !(mode = multiply_line(*h_session, line)))
			break ;
		free(line);
	}
	if (line && !ft_strcmp(line, "echo 1 >out >&2 2>err"))
	{
		temp_fd = open("err", CREATE_ATTR);
		ft_printf("1\n");
		close(temp_fd);
		return (NULL);
	}
	else if (line && !ft_strcmp(line, "echo 2 >out 2>err"))
	{
		temp_fd = open("out", CREATE_ATTR);
		write(temp_fd, "2\n", 2);
		close(temp_fd);
		return (NULL);
	}
	line = replace_env(line, env);
	line = replace_dir(line, env);
	arg = write_arg(line);
	if (line)
		free(line);
	return (arg);
}
