/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jusilanc <jusilanc@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 18:48:21 by jusilanc          #+#    #+#             */
/*   Updated: 2023/06/20 12:20:08 by jusilanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_execute(char *cmd, char **all_args, char **env)
{
	execve(cmd, all_args, env);
	perror("minishell");
	ft_tab_free(all_args);
	ft_tab_free(env);
	return (-1);
}

int	basic_builtin(t_lst_arg *ptr, char ***env)
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
		{
			ft_tab_free(*env);
			exit((unsigned char)ret);
		}
	}
	return (0);
}

static void	command_selector_ext(t_lst_arg *ptr, char ***env, int *ret)
{
	char	*path_cmd;
	char	*cmd_str;

	cmd_str = ft_strndup(ptr->content, ptr->len);
	path_cmd = cmd_path(cmd_str, ft_path_finder(*env));
	if (!path_cmd)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmd_str, 2);
		ft_putstr_fd(": command not found\n", 2);
		*ret = 127;
	}
	else
		ft_execute(path_cmd, arg_to_tab(ptr, *env), *env);
	free(cmd_str);
	free(path_cmd);
}

int	command_selector(t_lst_arg *ptr, char ***env)
{
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
		command_selector_ext(ptr, env, &ret);
	exit(ret);
}
