/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jusilanc <jusilanc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 14:28:48 by jusilanc          #+#    #+#             */
/*   Updated: 2023/06/21 14:43:38 by jusilanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	skip_whitespace(char *line, int *i, int *len)
{
	*len = 0;
	while (line[*i] && ft_strchr(" ", line[*i]))
		(*i)++;
}

void	word_delimeter(char *line, int *i, int *len)
{
	while (line[*i + *len] && !ft_strchr(" ;|><", line[*i + *len]))
	{
		if (line[*i + *len] == '\"' && ++(*len))
		{
			while (line[*i + *len] && line[*i + *len] != '\"')
				(*len)++;
			if (line[*i + *len])
				(*len)++;
		}
		else if (line[*i + *len] == '\'' && ++(*len))
		{
			while (line[*i + *len] && line[*i + *len] != '\'')
				(*len)++;
			if (line[*i + *len])
				(*len)++;
		}
		else if (line[*i + *len])
			(*len)++;
	}
	if (*len == 0)
		while (line[*i + *len] && ft_strchr(">", line[*i + *len]))
			(*len)++;
	if (*len == 0)
		while (line[*i + *len] && ft_strchr("<", line[*i + *len]))
			(*len)++;
}

static int	output_type_selector(char *line)
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

static void	rm_redir_lst(t_lst_cmd *cmd)
{
	t_lst_arg	*arg;
	t_lst_arg	*arg_prev;
	char		*tmp;
	size_t		len;
	size_t		i;

	arg_prev = NULL;
	while (cmd)
	{
		i = 0;
		arg = cmd->arguments;
		len = ft_lst_size(arg);
		while (arg && i++ < len)
		{
			while (arg && output_type_selector(arg->content) != -1)
			{
				cmd->output_type = output_type_selector(arg->content);
				arg = arg->next;
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
				else if (arg && cmd->output_type == APPEND)
				{
					tmp = ft_strndup(arg->content, arg->len);
					if (cmd->fd_out != 1)
						close(cmd->fd_out);
					cmd->fd_out = open(tmp, O_WRONLY | O_CREAT | O_APPEND,
							0644);
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
				if (arg && arg_prev)
					arg_prev->next = arg->next;
				else if (arg)
					cmd->arguments = arg->next;
			}
			if (arg)
				arg_prev = arg;
			if (arg)
				arg = arg->next;
		}
		cmd = cmd->next;
	}
}

t_lst_cmd	*ft_parsing(char *line, int i, int len, t_lst_cmd *cmd_lst)
{
	t_lst_cmd	*cmd;

	while (line && line[i] && line[i] == ' ')
		i++;
	while (line && line[i])
	{
		cmd = ft_cmd_list_new(NULL);
		if (!cmd || !ft_cmd_lst_add_back(&cmd_lst, cmd))
			return (NULL);
		while (line[i] && !ft_strchr(";|", line[i]))
		{
			skip_whitespace(line, &i, &len);
			word_delimeter(line, &i, &len);
			if (line[i] == '|')
				break ;
			if (len > 0 && !ft_lst_add_back(&cmd->arguments, &line[i], len))
				return (ft_cmd_lst_clear(cmd_lst));
			i += len;
			if (line[i] == '"')
				i++;
			while (line[i] && line[i] == ' ')
				i++;
			if (line[i] && cmd->arguments
				&& ft_strscmp(ft_lst_last(cmd->arguments)->content, "<"))
				cmd->input_type = READ;
			else if (line[i] && cmd->arguments
					&& ft_strscmp(ft_lst_last(cmd->arguments)->content, "<<"))
				cmd->input_type = HERE_DOC;
			else if (line[i] && cmd->arguments
					&& ft_strscmp(ft_lst_last(cmd->arguments)->content, ">"))
				cmd->output_type = OVERWRITE;
			else if (line[i] && cmd->arguments
					&& ft_strscmp(ft_lst_last(cmd->arguments)->content, ">>"))
				cmd->output_type = APPEND;
			rm_redir_lst(cmd);
		}
		if (line[i] == '|')
			cmd->output_type = output_type_selector(&line[i]);
		i += (cmd->output_type == APPEND) + (line[i] != 0);
	}
	return (cmd_lst);
}
