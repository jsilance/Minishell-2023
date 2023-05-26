/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_to_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jusilanc <jusilanc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 17:01:47 by jusilanc          #+#    #+#             */
/*   Updated: 2023/05/26 19:32:48 by jusilanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static size_t	ft_tab_size(char **tab)
{
	size_t	size;

	size = 0;
	while (tab && tab[size])
		size++;
	return (size);
}

void	ft_execute(char *cmd, char **all_args, char **env)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
		execve(cmd, all_args, env);
	wait(0);
	ft_multi_free(all_args, ft_tab_size(all_args));
}

void	ft_cmd_lst_print(t_lst_cmd *cmd, char **env)
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
				if (!ft_strncmp(ptr->content, "echo", 4))
					ft_echo(ptr);
				else
				{
					cmd_str = ft_strndup(ptr->content, ptr->len);
					path_cmd = cmd_path(cmd_str, ft_path_finder(env));
					if (!path_cmd)
						printf("minishell: %s: %s\n", cmd_str,
								"command not found");
					else
						ft_execute(path_cmd, arg_to_tab(ptr), env);
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
