/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_to_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jusilanc <jusilanc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 17:01:47 by jusilanc          #+#    #+#             */
/*   Updated: 2023/06/21 15:22:35 by jusilanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_cmd_lst_print(t_lst_cmd *cmd)
{
	t_lst_arg	*ptr;

	while (cmd)
	{
		ptr = cmd->arguments;
		while (ptr)
		{
			printf("\033[0;32m");
			printf("[%.*s]", ptr->len, ptr->content);
			ptr = ptr->next;
			printf("\033[0m");
		}
		printf("(%d)(%d)(%d)(%d)\n", cmd->fd_in, cmd->fd_out, cmd->input_type,
			cmd->output_type);
		cmd = cmd->next;
	}
}
