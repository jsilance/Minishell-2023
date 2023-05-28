/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_to_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jusilanc <jusilanc@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 17:01:47 by jusilanc          #+#    #+#             */
/*   Updated: 2023/05/29 01:25:26 by jusilanc         ###   ########.fr       */
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
			printf("[%.*s]", ptr->len, ptr->content);
			ptr = ptr->next;
		}
		printf("(%d)(%d)(%d)\n", cmd->fd_in, cmd->fd_out, cmd->output_type);
		cmd = cmd->next;
	}
}
