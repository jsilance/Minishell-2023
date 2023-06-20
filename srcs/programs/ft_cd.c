/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jusilanc <jusilanc@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 16:20:25 by jusilanc          #+#    #+#             */
/*   Updated: 2023/06/20 13:13:09 by jusilanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**get_newpwd(char *str, char *temp, char **env, char **tmp_str)
{
	if (!getcwd(str, 4096))
	{
		temp = ft_str_var_process("$PWD", env);
		ft_strlcpy(str, temp, ft_strlen(temp));
		free(temp);
	}
	*tmp_str = ft_strnstock("PWD=", str, -1, 0);
	if (!*tmp_str)
	{
		perror("minishell");
		return (env);
	}
	return (NULL);
}

static char	**get_oldpwd(char *str, char *temp, char **env, char **tmp_str)
{
	if (!getcwd(str, 4096))
	{
		temp = ft_str_var_process("$PWD", env);
		ft_strlcpy(str, temp, ft_strlen(temp));
		free(temp);
	}
	*tmp_str = ft_strnstock("OLDPWD=", str, -1, 0);
	if (!*tmp_str)
	{
		perror("minishell");
		return (env);
	}
	return (NULL);
}

static char	**env_process(char *temp, char **tmp_str, char **env)
{
	temp = ft_str_var_process(*tmp_str, env);
	if (!temp)
	{
		perror("minishell");
		return (env);
	}
	free(*tmp_str);
	if (ft_tab_finder(env, temp))
		env = ft_tab_delone(env, temp);
	env = ft_tab_append(env, temp);
	return (env);
}

static char	**change_dir_part(char *temp, t_lst_arg *arg, char **env, char
	**tmp_str)
{
	char	*dir;

	temp = ft_strndup(arg->content, arg->len);
	temp = cd_special_case(temp);
	dir = ft_str_var_process(temp, env);
	free(temp);
	if (!dir)
		free(*tmp_str);
	if (!dir)
		return (env);
	if (chdir(dir))
	{
		perror("minishell");
		free(*tmp_str);
		free(dir);
		return (env);
	}
	free(dir);
	return (NULL);
}

char	**ft_cd(t_lst_arg *arg, char **env)
{
	char	str[4096];
	char	*tmp_str;
	char	*temp;

	temp = NULL;
	tmp_str = NULL;
	if (!ft_strscmp(arg->content, "cd"))
		return (env);
	if (!arg->next)
	{
		ft_lst_add_back(&arg, "$HOME", 5);
		env = ft_cd(arg, env);
		return (env);
	}
	arg = arg->next;
	if (get_oldpwd(str, temp, env, &tmp_str))
		return (env);
	if (change_dir_part(temp, arg, env, &tmp_str))
		return (env);
	env = env_process(temp, &tmp_str, env);
	if (get_newpwd(str, temp, env, &tmp_str))
		return (env);
	env = env_process(temp, &tmp_str, env);
	return (env);
}
