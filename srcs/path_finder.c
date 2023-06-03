/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_finder.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jusilanc <jusilanc@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 20:15:34 by jusilanc          #+#    #+#             */
/*   Updated: 2023/06/04 01:03:24 by jusilanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ft_multi_free(char **ptr, size_t len)
{
	size_t	i;

	i = 0;
	if (!ptr)
		return (NULL);
	while (ptr[i] && i < len)
		free(ptr[i++]);
	free(ptr);
	return (NULL);
}

char	**ft_tab_free(char **ptr)
{
	size_t	i;

	i = 0;
	if (!ptr)
		return (NULL);
	while (ptr[i])
		free(ptr[i++]);
	free(ptr);
	return (NULL);
}

char	*cmd_path(char *cmd, char **path)
{
	int		i;
	int		ret;
	char	*ptr;

	i = 0;
	ret = access(cmd, X_OK);
	ptr = NULL;
	if (ret == 0)
		return (cmd);
	while (path && path[i])
	{
		ptr = ft_strjoin(path[i++], "/");
		if (!ptr)
			return (NULL);
		ptr = ft_strnstock(ptr, cmd, ft_strlen(cmd), 1);
		if (!ptr)
			return (NULL);
		ret = access(ptr, X_OK);
		if (ret == 0)
			break ;
		free(ptr);
		ptr = NULL;
	}
	ft_tab_free(path);
	return (ptr);
}

char	**ft_path_finder(char **env)
{
	char	*ptr;
	char	**path_ptr;
	int		i;

	ptr = NULL;
	path_ptr = NULL;
	i = 0;
	while (env && env[i])
	{
		if (ft_strnstr(env[i], "PATH=", 5))
		{
			ptr = ft_strtrim(env[i], "PATH=");
			if (!ptr)
				return (NULL);
			path_ptr = ft_split(ptr, ':');
			free(ptr);
			if (!path_ptr)
				return (NULL);
			return (path_ptr);
		}
		i++;
	}
	return (NULL);
}
