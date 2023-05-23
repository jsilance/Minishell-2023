/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_to_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jusilanc <jusilanc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 17:01:47 by jusilanc          #+#    #+#             */
/*   Updated: 2023/05/23 20:43:44 by jusilanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_lst_cmd	*ft_list_new(char *content, int len)
{
	t_lst_cmd	*node;

	node = (t_lst_cmd *)malloc(sizeof(t_lst_cmd));
	if (!node)
		return (NULL);
	node->content = content;
	node->len = len;
	node->next = NULL;
	return (node);
}

t_lst_cmd	*ft_lst_last(t_lst_cmd *lst)
{
	t_lst_cmd	*temp;

	while (lst)
	{
		temp = lst;
		lst = lst->next;
	}
	return (temp);
}

t_lst_cmd	*ft_lst_add_back(t_lst_cmd *lst, char *content, int len)
{
	t_lst_cmd	*temp;

	if (!lst)
		return (NULL);
	temp = ft_lst_last(lst);
	if (!temp)
		return (NULL);
	temp->next = ft_list_new(content, len);
	if (!temp->next)
		return (NULL);
	return (lst);
}

t_lst_cmd	*ft_lst_clear(t_lst_cmd *lst)
{
	t_lst_cmd	*temp;

	while (lst)
	{
		temp = lst->next;
		free(lst);
		lst = temp;
	}
	return (NULL);
}

t_lst_cmd	*ft_parsing(char *line)
{
	int			i;
	int			len;
	t_lst_cmd	*lst;

	lst = NULL;
	i = 0;
	while (line && line[i])
	{
		len = 0;
		while (line[i] && !ft_strchr("\t ", line[i]))
			i++;
		while (line[i + len] && ft_strchr("\t ", line[i + len]))
			len++;
		if (len > 0 && !ft_lst_add_back(lst, &line[i], len))
			return (ft_lst_clear(lst));
	}
	return (lst);
}
