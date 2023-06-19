/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avancoll <avancoll@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 14:28:48 by jusilanc          #+#    #+#             */
/*   Updated: 2023/06/19 13:56:08 by avancoll         ###   ########.fr       */
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

	arg_prev = NULL;
	while (cmd)
	{
		arg = cmd->arguments;
		while (arg)
		{
			// print les operations de dl car dl qu'une seule fois
			while (output_type_selector(arg->content) != -1)
			{
				cmd->output_type = output_type_selector(arg->content);
				arg = arg->next;
				if (cmd->input_type == READ)
				{
					tmp = ft_strndup(arg->content, arg->len);
					cmd->fd_in = open(tmp, O_RDONLY);
					if (cmd->fd_in == -1)
						perror("minishell");
					free(tmp);
				}
				else if (cmd->output_type == OVERWRITE)
				{
					tmp = ft_strndup(arg->content, arg->len);
					cmd->fd_out = open(tmp, O_WRONLY | O_CREAT | O_TRUNC, 0644);
					if (cmd->fd_out == -1)
						perror("minishell");
					free(tmp);
				}
				else if (cmd->output_type == APPEND)
				{
					tmp = ft_strndup(arg->content, arg->len);
					cmd->fd_out = open(tmp, O_WRONLY | O_CREAT | O_APPEND,
							0644);
					if (cmd->fd_out == -1)
						perror("minishell");
					free(tmp);
				}
				else if (cmd->output_type == HERE_DOC)
				{
					heredoc(arg, NULL);
					cmd->fd_in = open(".tmp", O_RDONLY);
					if (cmd->fd_in == -1)
						perror("minishell");
					// printf("(%d)\n", cmd->fd_in);
					// envoyer cmd plutot que cmd->arguments
					// unlink .tmp apres execution
				}
				// free(arg_prev->next);
				if (arg_prev)
					arg_prev->next = arg->next;
				else
					cmd->arguments = arg->next;
				// free(arg);
				// need to free previous arg
				// ft_cmd_lst_print(cmd);
			}
			arg_prev = arg;
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
			if (ft_strscmp(ft_lst_last(cmd->arguments)->content, "<"))
				cmd->input_type = READ;
			else if (ft_strscmp(ft_lst_last(cmd->arguments)->content, "<<"))
				cmd->input_type = HERE_DOC;
			else if (ft_strscmp(ft_lst_last(cmd->arguments)->content, ">"))
				cmd->output_type = OVERWRITE;
			else if (ft_strscmp(ft_lst_last(cmd->arguments)->content, ">>"))
				cmd->output_type = APPEND;
			// cmd->input_type = READ;
		}
		cmd->output_type = output_type_selector(&line[i]);
		i += (cmd->output_type == APPEND) + (line[i] != 0);
		rm_redir_lst(cmd);
	}
	// ft_cmd_lst_print(cmd_lst);
	return (cmd_lst);
}
