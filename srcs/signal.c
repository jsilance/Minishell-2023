/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jusilanc <jusilanc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 16:48:08 by avancoll          #+#    #+#             */
/*   Updated: 2023/06/06 18:25:04 by jusilanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			g_sig_status = 0; //=127 qd cmd not found,
						// 130 qd cmd interrompue,
//0 qd tout va bien,

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
	(void)sig;
}

static void	ctrl_backslash(int sig)
{
	g_sig_status = 131;
	(void)sig;
}
void	sig_handler(int process)
{
	struct termios	term;

	if (!process)
	{
		signal(SIGINT, restore_prompt);
		signal(SIGQUIT, SIG_IGN);
	}
	else
	{
		signal(SIGINT, ctrl_c);
		signal(SIGQUIT, ctrl_backslash);
	}
	tcgetattr(0, &term);
	term.c_lflag &= ~ECHOCTL;
	tcsetattr(0, TCSANOW, &term);
}
