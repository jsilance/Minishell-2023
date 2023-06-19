/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jusilanc <jusilanc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 13:46:59 by avancoll          #+#    #+#             */
/*   Updated: 2023/06/19 18:44:26 by jusilanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	heredoc(t_lst_arg *ptr, char **env)
{
	int		input_fd;
	char	*line;
	char	*tmp;
	char	*delimiter;

	(void)env;
	input_fd = open(".tmp", O_RDWR | O_CREAT | O_TRUNC, 0644);
	while (1)
	{
		line = readline("> ");
		delimiter = ft_strndup(ptr->content, ptr->len);
		if (!ft_strcmp(line, delimiter))
		{
			free(line);
			break ;
		}
		tmp = ft_strjoin(line, "\n");
		write(input_fd, tmp, ft_strlen(tmp));
		free(tmp);
		free(line);
	}
	close(input_fd);
}
