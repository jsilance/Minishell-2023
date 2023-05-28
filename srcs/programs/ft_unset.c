/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jusilanc <jusilanc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 23:12:48 by jusilanc          #+#    #+#             */
/*   Updated: 2023/05/28 19:32:03 by jusilanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ft_unset(t_lst_arg *arg, char **env)
{
	char	*temp;

	if (ft_strncmp(arg->content, "unset", 6) != 32)
		return (env);
	else
		arg = arg->next;
	while (arg)
	{
		temp = ft_strndup(arg->content, arg->len);
		if (!temp)
			return (env);
		if (ft_tab_finder(env, temp))
			env = ft_tab_delone(env, temp);
		free(temp);
		arg = arg->next;
	}
	return (env);
}
