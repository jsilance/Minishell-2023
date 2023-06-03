/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jusilanc <jusilanc@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 16:48:08 by avancoll          #+#    #+#             */
/*   Updated: 2023/06/03 21:52:53 by jusilanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int		g_signal_status = 0;

void	sig_handler(int signum)
{
	if (signum == SIGINT)
	{
		printf("control + C\n");
		g_signal_status = 130;
	}
	else if (signum == SIGQUIT)
	{
		printf("exit_shell\n");
		g_signal_status = 131;
	}
}
