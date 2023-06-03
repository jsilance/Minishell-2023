/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jusilanc <jusilanc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 13:39:43 by jusilanc          #+#    #+#             */
/*   Updated: 2023/06/03 17:00:16 by jusilanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_valid_var_char(char c)
{
	return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0'
		&& c <= '9') || (c == '-') || (c == '_');
}

static char	*var_to_str(char *str, char **env, size_t *i)
{
	size_t	j;
	char	*temp;
	char	*ptr;
	char	*tmp_ptr;

	j = 0;
	while (str[j] && is_valid_var_char(str[j]))
		j++;
	temp = ft_substr(str, 0, j);
	if (!temp)
		return (NULL);
	tmp_ptr = ft_tab_finder(env, temp);
	ptr = ft_strndup(&tmp_ptr[ft_len_until_equal(tmp_ptr) + 1], -1);
	free(temp);
	free(tmp_ptr);
	(*i) += j;
	return (ptr);
}

char	*ft_str_var_process(char *arg, size_t ar_len, char **env)
{
	char	*ptr;
	char	*temp;
	size_t	i;
	size_t	j;

	temp = NULL;
	ptr = NULL;
	i = 0;
	while (arg[i] && i < ar_len)
	{
		j = 0;
		if (!ft_strchr("'\"$", arg[i]))
		{
			while (arg[i + j] && i + j < ar_len && !ft_strchr("'\"$", arg[i
					+ j]))
				j++;
			ptr = ft_strnstock(ptr, ft_substr(&arg[i], i, j), -1, 3);
			i += j;
		}
		if (arg[i] == '"' && i < ar_len)
		{
			j = 0;
			i++;
			while (arg[i] && arg[i] != '"')
				if (arg[i] == '$')
					ptr = ft_strnstock(ptr, var_to_str(&arg[i], env, &i), -1,
							3);
				else
					ptr = ft_strnstock(ptr, ft_substr(arg, i++, 1), -1, 3);
			temp = NULL;
			if (arg[i] == '\'')
				j++;
			i += j;
		}
		if (arg[i] == '$')
			ptr = ft_strnstock(ptr, var_to_str(&arg[++i], env, &i), -1, 3);
		if (arg[i] == '\'')
		{
			j = 0;
			i++;
			while (arg[i] && arg[i] != '\'')
				j++;
			ptr = ft_strnstock(ptr, ft_substr(arg, i, j - 1), -1, 3);
			if (arg[i] == '\'')
				j++;
			i += j;
		}
	}
	return (ptr);
}

static int	n_option(char *arg, size_t arg_len)
{
	size_t	i;

	i = 0;
	while (ft_strchr("'\"", arg[i]))
		i++;
	if (arg[i++] == '-')
	{
		while (arg[i] == 'n' && i < arg_len)
			i++;
		if (ft_strchr("\"'n", arg[i]))
			return (1);
	}
	return (0);
}

int	ft_echo(t_lst_arg *arg, char **env)
{
	int		no_newline;
	char	*str;

	str = NULL;
	no_newline = 0;
	if (ft_strncmp(arg->content, "echo", 5) != 32)
		return (-1);
	else
		arg = arg->next;
	while (arg && n_option(arg->content, arg->len))
	{
		no_newline = 1;
		arg = arg->next;
	}
	while (arg)
	{
		if (arg && !(ft_strchr("\"", arg->content[-1]) && !ft_strchr(" ",
					arg->content[-2])))
			printf(" ");
		str = ft_str_var_process(arg->content, arg->len, env);
		printf("%s", str);
		free(str);
		// printf("%.*s", arg->len, arg->content);
		arg = arg->next;
	}
	if (!no_newline)
		printf("\n");
	return (0);
}
