/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgorczan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/18 16:53:05 by mgorczan          #+#    #+#             */
/*   Updated: 2019/07/18 16:53:06 by mgorczan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static struct termios	stored_settings;


void					replace_str(char **chang_line, int i, int lenght, char *env_verb)
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

void					check_quote(t_control_multiply_line *control, char ch)
{

	if ((ch == '\"' || ch == '\'') && (control->quote % 2) == 0)
	{
		control->ch_quote = ch;
		control->quote++;
	}
	else if (ch == control->ch_quote)
	{
		control->quote--;
	}
}

t_control_multiply_line	init_control(void)
{
	t_control_multiply_line control;

	control.quote = 0;
	control.ch_quote ='\0';
	control.pipe = 0;
	control.els = 0;
	control.ch = 0;
	return (control);
}

int						multiply_line(char *line)
{
	int i;
	t_control_multiply_line control;

	i = 0;
	control = init_control();
	while (line && line[i])
	{
		if ((line[i] == '\"' || line[i] == '\'') && !(i > 0 && line[i - 1] == '\\'))
			check_quote(&control, line[i++]);
		// else if (!control.quote && spec_token(line, i))
		// {
		// 	if (!control.ch && line[i] != '<' && !(line[i] == '&' && line[i + 1] == '>'))
		// 	{
		// 		write(2, "21sh: parse error near `", ft_strlen("21sh: parse error near `"));
		// 		write(2, &line[i], spec_token(line, i));
		// 		write(2, "\'\n", 2);
		// 		return (-1);
		// 	}
		// 	i += spec_token(line, i);
		// 	// if ()
		// }
		else
		{
			++i;
			control.ch++;
		}
	}
	if (control.quote)
		return (COMMANDID_QUOTE);
	else
		return (0);
}

void	set_keypress(void)
{
	struct termios	new_settings;

	tcgetattr(0, &stored_settings);
	new_settings = stored_settings;
	new_settings.c_lflag &= (~ICANON & ~ECHO);
	new_settings.c_cc[VTIME] = 0;
	new_settings.c_cc[VMIN] = 1;
	tcsetattr(0, TCSANOW, &new_settings);
	return ;
}

void	reset_keypress(void)
{
	tcsetattr(0, TCSANOW, &stored_settings);
	return;
}

char		*get_termcap(char **environ)
{
	char	*term;
	char	*term_edit;
	
	if ((term = ft_strnew(2048)))
	{
		if ((term_edit = ft_strdup(getenv("TERM"))))
		{
			tgetent(term, term_edit);
			if (tgetent(term, term_edit) == 1)
			{
				free(term_edit);
				return (term);
			}
			free(term_edit);
		}
		free(term);
	}
	return (NULL);
}

void	set_termenv(char *termcap)
{
	term = (t_term *)malloc(sizeof(t_term));
	term->le = tgetstr("le", &termcap);
	term->nd = tgetstr("nd", &termcap);
	term->cd = tgetstr("cd", &termcap);
	term->dc = tgetstr("dc", &termcap);
	term->im = tgetstr("im", &termcap);
	term->ei = tgetstr("ei", &termcap);
	term->so = tgetstr("so", &termcap);
	term->se = tgetstr("se", &termcap);
	term->up = tgetstr("up", &termcap);
	term->do_ = tgetstr("do", &termcap);


}

char					**parser(t_history_session **h_session, char **env, int lenght_hello)
{
	char	**arg;
	char	*line;
	int		mode;
	int		count_arg;
	char	*termcap;

	if ((termcap = get_termcap(env)))
		set_termenv(termcap);
	set_keypress();
	*h_session = add_history(*h_session, lenght_hello);
	mode = 0;
	while (1)
	{
		line = input(h_session, lenght_hello, mode);
		mode = multiply_line(line);
		if (mode == -1)
		{
			free(line);
			return (NULL);
		}
		if (!mode)
			break ;
		free(line);
	}
	line = replace_env(line, env);
	line = replace_dir(line, env);
	arg = write_arg(line);
	free(line);

	reset_keypress();
	free(termcap);
	free(term);

	return (arg);
}
