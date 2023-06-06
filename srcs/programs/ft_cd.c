/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jusilanc <jusilanc@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 16:20:25 by jusilanc          #+#    #+#             */
/*   Updated: 2023/06/07 00:51:29 by jusilanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ft_cd(t_lst_arg *arg, char **env)
{
	char	str[4096];
	char	*tmp_str;
	char	*temp;
	char	*dir;

	if (ft_strncmp(arg->content, "cd", arg->len))
		return (env);
	if (arg->next)
	{
		arg = arg->next;
		if (!getcwd(str, 4096))
		{
			temp = ft_str_var_process("$PWD", env);
			ft_strlcpy(str, temp, ft_strlen(temp));
			free(temp);
		}
		tmp_str = ft_strnstock("OLDPWD=", str, -1, 0);
		if (!tmp_str)
			return (env);
		dir = ft_str_var_process(ft_strndup(arg->content, arg->len), env);
		if (!dir)
		{
			free(tmp_str);
			return (env);
		}
		if (chdir(dir))
		{
			free(tmp_str);
			free(dir);
			return (env);
		}
		temp = ft_str_var_process(tmp_str, env);
		if (!temp)
			return (env);
		free(tmp_str);
		env = ft_tab_delone(env, temp);
		env = ft_tab_append(env, temp);
		if (!getcwd(str, 4096))
		{
			temp = ft_str_var_process("$PWD", env);
			ft_strlcpy(str, temp, ft_strlen(temp));
			free(temp);
		}
		tmp_str = ft_strnstock("PWD=", str, -1, 0);
		if (!tmp_str)
			return (env);
		temp = ft_str_var_process(tmp_str, env);
		if (!temp)
			return (env);
		free(tmp_str);
		if (ft_tab_finder(env, temp))
		{
			env = ft_tab_delone(env, temp);
			env = ft_tab_append(env, temp);
		}
		else
			perror(NULL);
	}
	else
	{
		ft_lst_add_back(&arg, "$HOME", 5);
		env = ft_cd(arg, env);
	}
	return (env);
}
