/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avancoll <avancoll@student.19.be>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 16:48:08 by avancoll          #+#    #+#             */
/*   Updated: 2023/06/01 17:19:55 by avancoll         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../includes/minishell.h"

int signal_status = 0;

void	sig_handler(int signum)
{
	if (signum == SIGINT)
	{
		printf("control + C\n");
		signal_status = 130;
	}
	else if (signum == SIGQUIT)
	{
		printf("exit_shell\n");
		signal_status = 131;
	}
}
