/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_to_tab.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jusilanc <jusilanc@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 12:53:53 by jusilanc          #+#    #+#             */
/*   Updated: 2023/06/03 21:15:13 by jusilanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**arg_to_tab(t_lst_arg *arg, char **env)
{
	size_t	len;
	size_t	i;
	char	**tab;
	char	*str;

	i = 0;
	len = ft_lst_size(arg);
	tab = (char **)malloc(sizeof(char *) * (len + 1));
	if (!tab)
		return (NULL);
	while (len > i && arg)
	{
		str = ft_strndup(arg->content, arg->len);
		if (!str)
			return (env);
		tab[i] = ft_str_var_process(str, env);
		free(str);
		if (!tab[i])
			return (ft_multi_free(tab, i));
		arg = arg->next;
		i++;
	}
	tab[i] = NULL;
	return (tab);
}
