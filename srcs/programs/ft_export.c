/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jusilanc <jusilanc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 15:13:27 by jusilanc          #+#    #+#             */
/*   Updated: 2023/05/28 20:01:34 by jusilanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_var_exist(char **env, const char *var)
{
	char	**tab;
	int		ret;

	ret = 0;
	tab = ft_split(var, '=');
	if (ft_tab_finder(env, tab[0]))
		ret = 1;
	ft_tab_free(tab);
	return (ret);
}

char	**ft_export(t_lst_arg *arg, char **env)
{
	char	*temp;

	if (ft_strncmp(arg->content, "export", 7) != 32)
		return (env);
	else
		arg = arg->next;
	while (arg)
	{
		if (ft_strnchr(arg->content, '=', arg->len))
		{
			temp = ft_strndup(arg->content, arg->len);
			if (!temp)
				return (env);
			if (is_var_exist(env, arg->content))
				env = ft_tab_delone(env, temp);
			env = ft_tab_append(env, temp);
		}
		arg = arg->next;
	}
	return (env);
}