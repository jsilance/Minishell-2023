/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute_ext.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jusilanc <jusilanc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 12:18:17 by jusilanc          #+#    #+#             */
/*   Updated: 2023/06/21 13:09:15 by jusilanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_close_all(t_lst_cmd *cmd)
{
	while (cmd)
	{
		if (cmd->fd_in)
			close(cmd->fd_in);
		if (cmd->fd_out != 1)
			close(cmd->fd_out);
		cmd = cmd->next;
	}
}

static void	parent_process(t_lst_cmd *cmd)
{
	if (cmd->next && cmd->output_type == PIPE)
		close(cmd->fd_out);
	if (cmd->fd_in)
		close(cmd->fd_in);
}

static void	child_process(t_lst_cmd *cmd, t_lst_cmd *tmp_cmd, char ***env)
{
	if (cmd->output_type == PIPE || cmd->output_type == APPEND
		|| cmd->output_type == OVERWRITE)
		dup2(cmd->fd_out, STDOUT_FILENO);
	if (cmd->fd_in)
		dup2(cmd->fd_in, STDIN_FILENO);
	ft_close_all(tmp_cmd);
	command_selector(cmd->arguments, env);
}

static void	waiting_pid(t_lst_cmd *tmp_cmd)
{
	int	status;

	while (tmp_cmd)
	{
		waitpid(tmp_cmd->pid, &status, 0);
		if (WIFEXITED(status))
			g_sig_status = WEXITSTATUS(status);
		tmp_cmd = tmp_cmd->next;
	}
}

void	ft_cmd_lst_execute(t_lst_cmd *cmd, char ***env)
{
	t_lst_cmd	*tmp_cmd;

	tmp_cmd = cmd;
	while (cmd)
	{
		// ft_cmd_lst_print(cmd);
		if (cmd->arguments && (ft_strscmp(cmd->arguments->content, "unset")
				|| ft_strscmp(cmd->arguments->content, "export")
				|| ft_strscmp(cmd->arguments->content, "exit")
				|| ft_strscmp(cmd->arguments->content, "cd")))
			g_sig_status = basic_builtin(cmd->arguments, env);
		else if (cmd->arguments)
		{
			cmd->pid = fork();
			if (cmd->pid == 0)
				child_process(cmd, tmp_cmd, env);
			else
				parent_process(cmd);
		}
		cmd = cmd->next;
	}
	waiting_pid(tmp_cmd);
}
