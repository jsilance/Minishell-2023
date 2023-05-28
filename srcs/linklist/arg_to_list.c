/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_to_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jusilanc <jusilanc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 17:01:47 by jusilanc          #+#    #+#             */
/*   Updated: 2023/05/28 19:03:23 by jusilanc         ###   ########.fr       */
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
			if (first == TRUE)
			{
				if (!ft_strncmp(ptr->content, "echo", ptr->len))
					ft_echo(ptr, *env);
				else if (!ft_strncmp(ptr->content, "unset", ptr->len))
					*env = ft_unset(ptr, *env);
				else if (!ft_strncmp(ptr->content, "export", ptr->len))
					*env = ft_export(ptr, *env);
				else if (!ft_strncmp(ptr->content, "env", ptr->len))
					ft_env(*env);
				else
				{
					cmd_str = ft_strndup(ptr->content, ptr->len);
					path_cmd = cmd_path(cmd_str, ft_path_finder(*env));
					if (!path_cmd)
						printf("minishell: %s: %s\n", cmd_str,
								"command not found");
					// else
					// 	ft_execute(path_cmd, arg_to_tab(ptr), *env);
					free(cmd_str);
					free(path_cmd);
				}
				first = FALSE;
			}
			// printf("[%.*s]", ptr->len, ptr->content);
			ptr = ptr->next;
		}
		// printf("(%d)(%d)(%d)\n", cmd->fd_in, cmd->fd_out, cmd->output_type);
		cmd = cmd->next;
	}
}
