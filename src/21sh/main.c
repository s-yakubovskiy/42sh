/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yharwyn- <yharwyn-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/27 22:01:05 by mgorczan          #+#    #+#             */
/*   Updated: 2020/01/18 19:31:56 by yharwyn-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		sh_init(char **environ)
{
	struct sigaction	sigint_action;
	pid_t				pid;
	struct passwd		*pw;
	int					i;

	sigint_action.sa_flags = 0;
	i = -1;
	sigint_action.sa_handler = &sigint_handler;
	sigemptyset(&sigint_action.sa_mask);
	sigaction(SIGINT, &sigint_action, NULL);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGTTIN, SIG_IGN);
	pid = getpid();
	setpgid(pid, pid);
	tcsetpgrp(0, pid);
	g_sh = ft_memalloc(sizeof(t_shell_info));
	g_sh->env = init_environ(environ);
	getlogin_r(g_sh->cur_user, sizeof(g_sh->cur_user));
	pw = getpwuid(getuid());
	ft_strcpy(g_sh->pw_dir, pw->pw_dir);
	while (++i < NR_JOBS)
		g_sh->jobs[i] = NULL;
}

void		sh_print_promt(void)
{
	usleep(400);
	if (g_sh->signal == 0)
		ft_printf(COLOR_GREEN "⦿" COLOR_MAGENTA "  %s" COLOR_NONE " ",
				basename(g_sh->cur_dir));
	else
		ft_printf(COLOR_RED "⦿" COLOR_MAGENTA "  %s" COLOR_NONE " ",
				basename(g_sh->cur_dir));
}

void		free_hsess(t_history_session *h_session)
{
	t_history_session *temp;

	h_session = list_rewind_to_end(h_session);
	while (h_session)
	{
		h_session->victor->del(&(h_session->victor));
		if (h_session->line)
		{
			free(h_session->line);
			h_session->line = NULL;
		}
		temp = h_session;
		h_session = h_session->up;
		free(temp);
	}
}

void		shell_loop(char **env)
{
	char						**args;
	int							status;
	t_job						*job;

	status = 1;
	g_h_session = NULL;
	set_termcap(env);
	job = NULL;
	while (status >= 0)
	{
		sh_print_promt();
		g_sh->signal = 0;
		args = parser(&g_h_session, env,
				ft_strlen(basename(g_sh->cur_dir)) + ft_strlen("⦿") + 1);
		if (parser_error_print(args))
			continue ;
		if (args == NULL)
		{
			check_zombie();
			continue ;
		}
		kazekage(args);
	}
}

int			main(int argc, char **argv)
{
	extern char	**environ;

	g_input_mode = 0;
	g_search_word = NULL;
	g_old_search = NULL;
	g_h_session = NULL;
	g_env = NULL;
	g_env_copy = NULL;
	argc = 0;
	argv = NULL;
	sh_init(environ);
	phash_init();
	sh_update_cwd_info();
	alias_init();
	set_init();
	shell_loop(environ);
	return (0);
}
