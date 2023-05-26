/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jusilanc <jusilanc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 16:16:48 by avancoll          #+#    #+#             */
/*   Updated: 2023/05/26 18:52:07 by jusilanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_pipe(t_lst_cmd *cmd)
{
	int	fd[2];

	while (cmd && cmd->next && cmd->output_type == PIPE)
	{
		if (pipe(fd) < 0)
			return (-1);
		// printf("\033[0;34mHERE\033[0m\n");
		cmd->fd_out = fd[0];
		cmd->next->fd_in = fd[1];
		cmd = cmd->next;
	}
	return (0);
}
