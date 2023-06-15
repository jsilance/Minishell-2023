/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avancoll <avancoll@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 13:46:59 by avancoll          #+#    #+#             */
/*   Updated: 2023/06/15 13:47:39 by avancoll         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	heredoc(t_lst_arg *ptr, char **env)
{
	(void)env;
	int		input_fd;
	char	*line;
	char	*tmp;
	char	*str;

	input_fd = open(".tmp", O_RDWR | O_CREAT | O_TRUNC, 0644);
	while (1)
	{
		line = readline("> ");
		if (!ft_strcmp(line, ptr->next->content))
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
	input_fd = open(".tmp", O_RDONLY);
	dup2(input_fd, STDIN_FILENO);
	str = ft_strndup(ptr->content, ptr->len);
	printf("str: %s\n", str);
	// ft_execute(str, arg_to_tab(ptr, env), env);
	free(str);
	close(input_fd);
	unlink(".tmp");
}
