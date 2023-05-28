/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_to_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jusilanc <jusilanc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 17:01:47 by jusilanc          #+#    #+#             */
/*   Updated: 2023/05/28 20:18:18 by jusilanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_cmd_lst_print(t_lst_cmd *cmd, char ***env)
{
	t_lst_arg	*ptr;
	int			first;
	char		*path_cmd;
	char		*cmd_str;

	while (cmd)
	{
		first = TRUE;
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
