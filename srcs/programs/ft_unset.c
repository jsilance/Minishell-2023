/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jusilanc <jusilanc@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 23:12:48 by jusilanc          #+#    #+#             */
/*   Updated: 2023/05/27 00:06:04 by jusilanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_unset(t_lst_arg *arg, char **env)
{
	char	*temp;

	if (ft_strncmp(arg->content, "unset", arg->len))
		return (-1);
	else
		arg = arg->next;
	while (arg)
	{
		temp = ft_strndup(arg->content, arg->len);
		if (!temp)
			return (-1);
		env = ft_tab_delone(env, temp);
		free(temp);
		arg = arg->next;
	}
	return (0);
}
