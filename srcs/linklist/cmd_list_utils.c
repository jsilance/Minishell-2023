/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_list_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jusilanc <jusilanc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 17:33:56 by jusilanc          #+#    #+#             */
/*   Updated: 2023/05/29 13:20:23 by jusilanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_lst_cmd	*ft_cmd_list_new(t_lst_arg *arg)
{
	t_lst_cmd	*node;

	node = (t_lst_cmd *)malloc(sizeof(t_lst_cmd));
	if (!node)
		return (NULL);
	node->arguments = arg;
	node->fd_in = 0;
	node->fd_out = 1;
	node->output_type = 0;
	node->next = NULL;
	return (node);
}

t_lst_cmd	*ft_cmd_lst_last(t_lst_cmd *lst)
{
	t_lst_cmd	*temp;

	while (lst)
	{
		temp = lst;
		lst = lst->next;
	}
	return (temp);
}

t_lst_cmd	*ft_cmd_lst_add_back(t_lst_cmd **list, t_lst_cmd *new)
{
	t_lst_cmd	*temp;
	t_lst_cmd	*lst;

	lst = *list;
	if (!lst)
	{
		lst = new;
		*list = lst;
		return (lst);
	}
	temp = ft_cmd_lst_last(lst);
	if (!temp)
		return (NULL);
	temp->next = new;
	if (!temp->next)
		return (NULL);
	*list = lst;
	return (lst);
}

t_lst_cmd	*ft_cmd_lst_clear(t_lst_cmd *lst)
{
	t_lst_cmd	*temp;

	while (lst)
	{
		temp = lst->next;
		if (lst->fd_in != 0)
			close(lst->fd_in);
		if (lst->fd_out != 1)
			close(lst->fd_out);
		ft_lst_clear(lst->arguments);
		free(lst);
		lst = temp;
	}
	return (NULL);
}
