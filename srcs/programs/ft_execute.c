/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jusilanc <jusilanc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 18:48:21 by jusilanc          #+#    #+#             */
/*   Updated: 2023/06/19 17:16:15 by jusilanc         ###   ########.fr       */
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

static void	ft_execute(char *cmd, char **all_args, char **env)
{
	execve(cmd, all_args, env);
	perror("execve");
	ft_multi_free(all_args, ft_tab_size(all_args));
}

static int	basic_builtin(t_lst_arg *ptr, char ***env)
{
	int	ret;

	ret = 0;
	if (ft_strscmp(ptr->content, "unset"))
		*env = ft_unset(ptr, *env);
	else if (ft_strscmp(ptr->content, "export"))
		*env = ft_export(ptr, *env);
	else if (ft_strscmp(ptr->content, "cd"))
		*env = ft_cd(ptr, *env);
	else if (ft_strscmp(ptr->content, "exit"))
	{
		ret = ft_exit(ptr, *env);
		if (ret != -1)
			exit((unsigned char)ret);
	}
	return (0);
}

static int	command_selector(t_lst_arg *ptr, char ***env)
{
	char	*path_cmd;
	char	*cmd_str;
	int		ret;

	ret = 0;
	if (!ptr)
		return (-1);
	if (ft_strscmp(ptr->content, "echo"))
		ft_echo(ptr, *env);
	else if (ft_strscmp(ptr->content, "pwd"))
		ft_pwd(ptr, *env);
	else if (ft_strscmp(ptr->content, "env"))
		ft_env(*env);
	else
	{
		cmd_str = ft_strndup(ptr->content, ptr->len);
		path_cmd = cmd_path(cmd_str, ft_path_finder(*env));
		if (!path_cmd)
		{
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(cmd_str, 2);
			ft_putstr_fd(": command not found\n", 2);
			ret = 127;
		}
		else
			ft_execute(path_cmd, arg_to_tab(ptr, *env), *env);
		free(cmd_str);
		free(path_cmd);
	}
	exit(ret);
}

void	ft_close_all(t_lst_cmd *cmd)
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

void	ft_cmd_lst_execute(t_lst_cmd *cmd, char ***env)
{
	int			status;
	t_lst_cmd	*tmp_cmd;

	tmp_cmd = cmd;
	while (cmd)
	{
		if (cmd->arguments && (ft_strscmp(cmd->arguments->content, "unset")
				|| ft_strscmp(cmd->arguments->content, "export")
				|| ft_strscmp(cmd->arguments->content, "exit")
				|| ft_strscmp(cmd->arguments->content, "cd")))
			g_sig_status = basic_builtin(cmd->arguments, env);
		else
		{
			cmd->pid = fork();
			if (cmd->pid == 0)
			{
				if (cmd->output_type == PIPE || cmd->output_type == APPEND
					|| cmd->output_type == OVERWRITE)
					dup2(cmd->fd_out, STDOUT_FILENO);
				if (cmd->fd_in)
					dup2(cmd->fd_in, STDIN_FILENO);
				ft_close_all(tmp_cmd);
				command_selector(cmd->arguments, env);
			}
			else
			{
				if (cmd->next && cmd->output_type == PIPE)
					close(cmd->fd_out);
				if (cmd->fd_in)
					close(cmd->fd_in);
			}
		}
		cmd = cmd->next;
	}
	while (tmp_cmd)
	{
		waitpid(tmp_cmd->pid, &status, 0);
		if (WIFEXITED(status))
			g_sig_status = WEXITSTATUS(status);
		tmp_cmd = tmp_cmd->next;
	}
}
