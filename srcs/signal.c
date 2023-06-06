/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avancoll <avancoll@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 16:48:08 by avancoll          #+#    #+#             */
/*   Updated: 2023/06/06 15:29:16 by avancoll         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		g_signal_status = 0;

void	all_signal(void)
{
	signal(SIGINT, sig_handler);
	signal(SIGQUIT, sig_handler);
	signal(SIGTSTP, SIG_IGN);
}

void	sig_handler(int signum)
{
	if (signum == SIGINT)
	{
		printf("ctrl+c\n");
		g_signal_status = 130;
	}
	else if (signum == SIGQUIT)
	{
		printf("ctrl+backslash\n");
		g_signal_status = 131;
	}
	else if (signum == SIGTSTP)
	{
		printf("ctrl+z\n");
		g_signal_status = 132;
	}
}
