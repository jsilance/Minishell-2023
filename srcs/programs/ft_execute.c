/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jusilanc <jusilanc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 18:48:21 by jusilanc          #+#    #+#             */
/*   Updated: 2023/06/16 11:35:07 by jusilanc         ###   ########.fr       */
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
	if (ft_strscmp(ptr->content, "unset"))
		*env = ft_unset(ptr, *env);
	else if (ft_strscmp(ptr->content, "export"))
		*env = ft_export(ptr, *env);
	else if (ft_strscmp(ptr->content, "cd"))
		*env = ft_cd(ptr, *env);
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
	else if (ft_strscmp(ptr->content, "<<"))
		heredoc(ptr, *env);
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

void	ft_cmd_lst_execute(t_lst_cmd *cmd, char ***env)
{
	pid_t		pid;
	int			status;
	t_lst_cmd	*tmp_cmd;

	// int		fd_d_in;
	// int		fd_d_out;
	// fd_d_in = dup(STDIN_FILENO);
	// fd_d_out = dup(STDOUT_FILENO);
	tmp_cmd = cmd;
	// ft_cmd_lst_print(cmd);
	while (cmd)
	{
		if (cmd->arguments && (ft_strscmp(cmd->arguments->content, "unset")
				|| ft_strscmp(cmd->arguments->content, "export")
				|| ft_strscmp(cmd->arguments->content, "cd")))
			g_sig_status = basic_builtin(cmd->arguments, env);
		else
		{
			pid = fork();
			if (pid == 0)
			{
				if (cmd->output_type == PIPE || cmd->output_type == APPEND
					|| cmd->output_type == OVERWRITE)
				{
					dup2(cmd->fd_out, STDOUT_FILENO);
					close(cmd->fd_out);
				}
				if (cmd->fd_in)
				{
					dup2(cmd->fd_in, STDIN_FILENO);
					close(cmd->fd_in);
				}
				if (command_selector(cmd->arguments, env) == -1)
					ft_putstr_fd("Error\n", 2);
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
		waitpid(-1, &status, 0);
		if (WIFEXITED(status))
			g_sig_status = WEXITSTATUS(status);
		tmp_cmd = tmp_cmd->next;
	}
	// dup2(fd_d_in, STDIN_FILENO);
	// dup2(fd_d_out, STDOUT_FILENO);
}
