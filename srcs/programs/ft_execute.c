/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avancoll <avancoll@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 18:48:21 by jusilanc          #+#    #+#             */
/*   Updated: 2023/06/15 13:49:39 by avancoll         ###   ########.fr       */
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

// void	input_redir(t_lst_arg *ptr)
// {
// 	int		input_fd;

// 	input_fd = open(ptr->content, O_RDONLY);
// 	dup2(input_fd, STDIN_FILENO);
// }

static int	command_selector(t_lst_arg *ptr, char ***env)
{
	char	*path_cmd;
	char	*cmd_str;
	int		ret;

	ret = 0;
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
		g_sig_status = 10;
		if (!path_cmd)
		{
			printf("minishell: %s: %s\n", cmd_str, "command not found");
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
	pid_t	pid;
	int		status;
	int		fd_d_in;
	int		fd_d_out;

	fd_d_in = dup(STDIN_FILENO);
	fd_d_out = dup(STDOUT_FILENO);
	while (cmd)
	{
		if (ft_strscmp(cmd->arguments->content, "unset")
			|| ft_strscmp(cmd->arguments->content, "export")
			|| ft_strscmp(cmd->arguments->content, "cd"))
			g_sig_status = basic_builtin(cmd->arguments, env);
		else
		{
			pid = fork();
			if (pid == 0)
			{
				// if (cmd->input_type == READ)
				// {
				// 	dup2(cmd->fd_in, STDIN_FILENO);
				// }
				if (cmd->output_type != DEFAULT)
				{
					if (cmd->next && cmd->output_type == PIPE)
						close(cmd->next->fd_in);
					dup2(cmd->fd_out, STDOUT_FILENO);
				}
				if (command_selector(cmd->arguments, env) == -1)
					printf("Error\n");
			}
			else
			{
				if (cmd->next && cmd->output_type == PIPE)
				{
					close(cmd->fd_out);
					dup2(cmd->next->fd_in, STDIN_FILENO);
				}
				waitpid(pid, &status, 0);
				if (WIFEXITED(status))
					g_sig_status = WEXITSTATUS(status);
			}
		}
		cmd = cmd->next;
	}
	dup2(fd_d_in, STDIN_FILENO);
	dup2(fd_d_out, STDOUT_FILENO);
}
