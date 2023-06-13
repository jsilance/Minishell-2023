/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jusilanc <jusilanc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 15:13:27 by jusilanc          #+#    #+#             */
/*   Updated: 2023/06/13 11:16:05 by jusilanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_swap(char **a, char **b)
{
	char	*tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

void	ft_sort_char_tab(char **tab, int size)
{
	int	i;
	int	j;

	i = 0;
	while (i < size)
	{
		j = i + 1;
		while (j < size)
		{
			if (ft_strncmp(tab[i], tab[j], ft_strlen(tab[i])) > 0)
				ft_swap(&tab[i], &tab[j]);
			j++;
		}
		i++;
	}
}

static size_t	ft_tab_len(char **tab)
{
	size_t	size;

	size = 0;
	while (tab && tab[size])
		size++;
	return (size);
}

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
	char	*str;
	char	**env_cpy;

	env_cpy = NULL;
	if (!ft_strscmp(arg->content, "export"))
		return (env);
	else
		arg = arg->next;
	if (!arg)
	{
		env_cpy = ft_tabdup(env);
		ft_sort_char_tab(env_cpy, ft_tab_len(env_cpy));
		env_cpy = ft_tab_delone(env_cpy, "_=");
		ft_env(env_cpy);
		ft_tab_free(env_cpy);
	}
	while (arg)
	{
		if (ft_strnchr(arg->content, '=', arg->len))
		{
			str = ft_strndup(arg->content, arg->len);
			if (!str)
				return (env);
			temp = ft_str_var_process(str, env);
			if (!temp)
				return (env);
			free(str);
			if (is_var_exist(env, arg->content))
				env = ft_tab_delone(env, temp);
			env = ft_tab_append(env, temp);
		}
		arg = arg->next;
	}
	return (env);
}
