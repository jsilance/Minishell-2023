/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jusilanc <jusilanc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 18:48:21 by jusilanc          #+#    #+#             */
/*   Updated: 2023/06/13 11:03:01 by jusilanc         ###   ########.fr       */
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
	pid_t	pid;

	pid = fork();
	if (pid == 0)
		if (execve(cmd, all_args, env) == -1)
			perror("minishell");
	wait(0);
	ft_multi_free(all_args, ft_tab_size(all_args));
}

static int	command_selector(t_lst_arg *ptr, char ***env)
{
	char	*path_cmd;
	char	*cmd_str;

	if (ft_strscmp(ptr->content, "echo"))
		ft_echo(ptr, *env);
	else if (ft_strscmp(ptr->content, "cd"))
		*env = ft_cd(ptr, *env);
	else if (ft_strscmp(ptr->content, "pwd"))
		ft_pwd(ptr, *env);
	else if (ft_strscmp(ptr->content, "unset"))
		*env = ft_unset(ptr, *env);
	else if (ft_strscmp(ptr->content, "export"))
		*env = ft_export(ptr, *env);
	else if (ft_strscmp(ptr->content, "env"))
		ft_env(*env);
	else
	{
		cmd_str = ft_strndup(ptr->content, ptr->len);
		path_cmd = cmd_path(cmd_str, ft_path_finder(*env));
		if (!path_cmd)
			printf("minishell: %s: %s\n", cmd_str, "command not found");
		else
			ft_execute(path_cmd, arg_to_tab(ptr, *env), *env);
		free(cmd_str);
		free(path_cmd);
	}
	return (0);
}

void	ft_cmd_lst_execute(t_lst_cmd *cmd, char ***env)
{
	// pid_t	pid;
	while (cmd)
	{
		// pid = fork();
		// if (pid == 0)
		// {
		if (command_selector(cmd->arguments, env) == -1)
			printf("Error\n");
		// }
		cmd = cmd->next;
	}
	// wait(0);
}
