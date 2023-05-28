/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tabdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jusilanc <jusilanc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 21:40:35 by jusilanc          #+#    #+#             */
/*   Updated: 2023/05/28 20:17:09 by jusilanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static size_t	ft_len_until_equal(const char *str)
{
	size_t	size;

	size = 0;
	while (str[size] && str[size] != '=')
		size++;
	return (size);
}

static size_t	ft_len_to_compare(const char *str_env, const char *variable)
{
	size_t	str_env_len;
	size_t	variable_len;

	str_env_len = ft_len_until_equal(str_env);
	variable_len = ft_len_until_equal(variable);
	if (str_env_len < variable_len)
		return (variable_len);
	return (str_env_len);
}

char	**ft_tabdup(char **tab)
{
	size_t	size;
	char	**new_tab;

	size = 0;
	if (!tab)
		return (NULL);
	while (tab[size])
		size++;
	new_tab = (char **)malloc(sizeof(char *) * (size + 1));
	if (!new_tab)
		return (NULL);
	size = 0;
	while (tab[size])
	{
		new_tab[size] = ft_strdup(tab[size]);
		size++;
	}
	new_tab[size] = NULL;
	return (new_tab);
}

char	*ft_tab_finder(char **env, char *variable)
{
	int	i;

	i = 0;
	while (env && env[i])
	{
		if (!ft_strncmp(env[i], variable, ft_len_to_compare(env[i], variable)))
			return (env[i]);
		i++;
	}
	return (NULL);
}

char	**ft_tab_append(char **old_env, char *new_str)
{
	size_t	size;
	char	**new_env;

	size = 0;
	if (!old_env)
		return (NULL);
	while (old_env && old_env[size])
		size++;
	new_env = (char **)malloc(sizeof(char *) * (size + 2));
	if (!new_env)
		return (NULL);
	size = 0;
	while (old_env[size])
	{
		new_env[size] = old_env[size];
		size++;
	}
	new_env[size++] = new_str;
	new_env[size] = 0;
	free(old_env);
	return (new_env);
}

char	**ft_tab_delone(char **old_env, char *del_str)
{
	size_t	size;
	size_t	j;
	char	**new_env;

	j = 0;
	size = 0;
	while (old_env && old_env[size])
		size++;
	new_env = (char **)malloc(sizeof(char *) * (size));
	if (!new_env)
		return (NULL);
	size = 0;
	while (old_env[size])
	{
		if (ft_strncmp(old_env[size], del_str, ft_len_to_compare(old_env[size],
					del_str)))
			new_env[j++] = old_env[size];
		else
			free(old_env[size]);
		size++;
	}
	new_env[j] = 0;
	free(old_env);
	return (new_env);
}
