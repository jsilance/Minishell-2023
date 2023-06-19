/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jusilanc <jusilanc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 16:20:55 by jusilanc          #+#    #+#             */
/*   Updated: 2023/06/19 16:29:37 by jusilanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ft_exit(t_lst_arg *arg, char **env)
{
	char *temp;
	char *str;

	if (!ft_strscmp(arg->content, "exit"))
		return (env);
	else
		arg = arg->next;
	while (arg)
	{
		str = ft_strndup(arg->content, arg->len);
		if (!str)
			return (env);
		temp = ft_str_var_process(str, env);
		if (!temp)
			return (env);
		free(str);
		if (ft_tab_finder(env, temp))
			env = ft_tab_delone(env, temp);
		free(temp);
		arg = arg->next;
	}
	return (env);
}