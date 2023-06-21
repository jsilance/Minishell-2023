/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avancoll <avancoll@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 16:48:08 by avancoll          #+#    #+#             */
/*   Updated: 2023/06/21 11:17:40 by avancoll         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	restore_prompt(int sig)
{
	g_sig_status = 1;
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	(void)sig;
}

static void	ctrl_c(int sig)
{
	g_sig_status = 130;
	printf("^C\n");
	(void)sig;
}

static void	ctrl_backslash(int sig)
{
	g_sig_status = 131;
	printf("Quit: 3\n");
	(void)sig;
}

void	sig_handler(int process)
{
	struct termios	term;

	if (process == 0)
	{
		signal(SIGINT, restore_prompt);
		signal(SIGQUIT, SIG_IGN);
	}
	else if (process == 1)
	{
		signal(SIGINT, ctrl_c);
		signal(SIGQUIT, ctrl_backslash);
	}
	else if (process == 2)
	{
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
	}
	tcgetattr(0, &term);
	term.c_lflag &= ~ECHOCTL;
	tcsetattr(0, TCSANOW, &term);
}
