/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jusilanc <jusilanc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 13:46:59 by avancoll          #+#    #+#             */
/*   Updated: 2023/06/16 11:33:52 by jusilanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	heredoc(t_lst_arg *ptr, char **env)
{
	int		input_fd;
	char	*line;
	char	*tmp;
	char	*delimiter;

	// char	*str;
	(void)env;
	input_fd = open(".tmp", O_RDWR | O_CREAT | O_TRUNC, 0644);
	while (1)
	{
		line = readline("> ");
		//probleme par ici avec la string
		delimiter = ft_strndup(ptr->content, ptr->len);
		printf("(%s)\t\t", line);
		printf("[%s]\n", delimiter);
		if (!ft_strcmp(line, delimiter))
		{
			printf("encountered delimiter\n");
			free(line);
			break ;
		}
		tmp = ft_strjoin(line, "\n");
		write(input_fd, tmp, ft_strlen(tmp));
		free(tmp);
		free(line);
	}
	close(input_fd);
	// input_fd = open(".tmp", O_RDONLY);
	// dup2(input_fd, STDIN_FILENO);
	// str = ft_strndup(ptr->content, ptr->len);
	// printf("str: %s\n", str);
	// ft_execute(str, arg_to_tab(ptr, env), env);
	// free(str);
	// close(input_fd);
	// unlink(".tmp");
}
