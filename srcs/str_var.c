/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_var.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jusilanc <jusilanc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 23:28:04 by jusilanc          #+#    #+#             */
/*   Updated: 2023/06/21 12:25:31 by jusilanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_valid_var_char(char c)
{
	return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0'
			&& c <= '9') || (c == '-') || (c == '_') || (c == '?'));
}

static void	single_quote(char *arg, size_t *i, char **ptr)
{
	size_t	j;

	j = 0;
	(*i)++;
	while (arg[(*i) + j] && arg[(*i) + j] != '\'')
		j++;
	*ptr = ft_strnstock(*ptr, ft_substr(arg, *i, j), -1, 3);
	if (arg[*i] == '\'')
		j++;
	(*i) += j;
}

static void	double_quote(char *arg, size_t *i, char **ptr, char **env)
{
	(*i)++;
	while (arg[*i] && arg[*i] != '"')
	{
		if (arg[*i] == '$')
			*ptr = ft_strnstock(*ptr, var_to_str(&arg[++(*i)], env, i), -1, 3);
		else
			*ptr = ft_strnstock(*ptr, ft_substr(arg, (*i)++, 1), -1, 3);
	}
	if (arg[*i] == '"')
		(*i)++;
}

char	*var_to_str(char *str, char **env, size_t *i)
{
	size_t	j;
	char	*temp;
	char	*ptr;
	char	*tmp_ptr;

	j = 0;
	ptr = NULL;
	tmp_ptr = NULL;
	if (!str)
		return (NULL);
	while (str[j] && is_valid_var_char(str[j]))
		j++;
	temp = ft_substr(str, 0, j);
	if (!temp)
		return (NULL);
	if (!ft_strcmp(temp, "?"))
		ptr = ft_itoa(g_sig_status);
	else
		tmp_ptr = ft_tab_finder(env, temp);
	if (tmp_ptr)
		ptr = ft_strndup(&tmp_ptr[ft_len_until_equal(tmp_ptr) + 1], -1);
	free(temp);
	(*i) += j;
	return (ptr);
}

char	*ft_str_var_process(char *arg, char **env)
{
	char	*ptr;
	size_t	i;
	size_t	j;

	ptr = NULL;
	i = 0;
	while (arg && arg[i])
	{
		j = 0;
		home_checker(arg, &i, &ptr, env);
		if (arg[i] && !ft_strchr("'\"$", arg[i]))
		{
			while (arg[i + j] && !ft_strchr("'\"$", arg[i + j]))
				j++;
			ptr = ft_strnstock(ptr, ft_substr(&arg[i], 0, j), -1, 3);
			i += j;
		}
		if (arg[i] == '"')
			double_quote(arg, &i, &ptr, env);
		if (arg[i] == '$')
			ptr = ft_strnstock(ptr, var_to_str(&arg[++i], env, &i), -1, 3);
		if (arg[i] == '\'')
			single_quote(arg, &i, &ptr);
	}
	return (ptr);
}
