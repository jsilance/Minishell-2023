/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jusilanc <jusilanc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 14:59:45 by jusilanc          #+#    #+#             */
/*   Updated: 2023/06/21 15:23:01 by jusilanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	output_type_selector(char *line)
{
	if (!line[0] || line[0] == ';')
		return (DEFAULT);
	else if (line[0] == '|')
		return (PIPE);
	else if (line[0] == '>' && line[1] == '>')
		return (APPEND);
	else if (line[0] == '<' && line[1] == '<')
		return (HERE_DOC);
	else if (line[0] == '<')
		return (READ);
	else if (line[0] == '>')
		return (OVERWRITE);
	return (-1);
}

static void	parsing_redir_a_h(t_lst_arg *arg, t_lst_cmd *cmd)
{
	char	*tmp;

	if (arg && cmd->output_type == APPEND)
	{
		tmp = ft_strndup(arg->content, arg->len);
		if (cmd->fd_out != 1)
			close(cmd->fd_out);
		cmd->fd_out = open(tmp, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (cmd->fd_out == -1)
			perror("minishell");
		free(tmp);
	}
	else if (arg && cmd->output_type == HERE_DOC)
	{
		heredoc(arg, NULL);
		cmd->fd_in = open(".tmp", O_RDONLY);
		if (cmd->fd_in == -1)
			perror("minishell");
	}
}

static void	parsing_redir_o_r(t_lst_arg *arg, t_lst_cmd *cmd)
{
	char	*tmp;

	if (arg && cmd->input_type == READ)
	{
		tmp = ft_strndup(arg->content, arg->len);
		cmd->fd_in = open(tmp, O_RDONLY);
		if (cmd->fd_in == -1)
			perror("minishell");
		free(tmp);
	}
	else if (arg && cmd->output_type == OVERWRITE)
	{
		tmp = ft_strndup(arg->content, arg->len);
		if (cmd->fd_out != 1)
			close(cmd->fd_out);
		cmd->fd_out = open(tmp, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (cmd->fd_out == -1)
			perror("minishell");
		free(tmp);
	}
}

void	parsing_main_part(t_lst_arg **arg, t_lst_cmd **cmd,
	t_lst_arg **arg_prev)
{
	while (*arg && output_type_selector((*arg)->content) != -1)
	{
		(*cmd)->output_type = output_type_selector((*arg)->content);
		*arg = (*arg)->next;
		if (*arg && ((*cmd)->input_type == READ || (*cmd)->output_type
				== OVERWRITE))
			parsing_redir_o_r(*arg, (*cmd));
		else if (*arg && ((*cmd)->output_type == APPEND
				|| (*cmd)->output_type == HERE_DOC))
			parsing_redir_a_h(*arg, *cmd);
		if (*arg && *arg_prev)
			(*arg_prev)->next = (*arg)->next;
		else if (*arg)
			(*cmd)->arguments = (*arg)->next;
	}
	if (*arg)
		*arg_prev = *arg;
	if (*arg)
		*arg = (*arg)->next;
}
