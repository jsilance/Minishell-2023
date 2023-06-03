/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jusilanc <jusilanc@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 23:12:48 by jusilanc          #+#    #+#             */
/*   Updated: 2023/06/03 20:47:44 by jusilanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ft_unset(t_lst_arg *arg, char **env)
{
	char	*temp;
	char	*str;

	if (ft_strncmp(arg->content, "unset", 6) != 32)
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
