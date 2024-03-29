/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_list_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jusilanc <jusilanc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 17:33:56 by jusilanc          #+#    #+#             */
/*   Updated: 2023/05/26 12:56:32 by jusilanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_lst_arg	*ft_list_new(char *content, int len)
{
	t_lst_arg	*node;

	node = (t_lst_arg *)malloc(sizeof(t_lst_arg));
	if (!node)
		return (NULL);
	node->content = content;
	node->len = len;
	node->next = NULL;
	return (node);
}

t_lst_arg	*ft_lst_last(t_lst_arg *lst)
{
	t_lst_arg	*temp;

	if (!lst)
		return (lst);
	while (lst)
	{
		temp = lst;
		lst = lst->next;
	}
	return (temp);
}

t_lst_arg	*ft_lst_add_back(t_lst_arg **list, char *content, int len)
{
	t_lst_arg	*temp;
	t_lst_arg	*lst;

	lst = *list;
	if (!lst)
	{
		lst = ft_list_new(content, len);
		*list = lst;
		return (lst);
	}
	temp = ft_lst_last(lst);
	if (!temp)
		return (NULL);
	temp->next = ft_list_new(content, len);
	if (!temp->next)
		return (NULL);
	*list = lst;
	return (lst);
}

t_lst_arg	*ft_lst_clear(t_lst_arg *lst)
{
	t_lst_arg	*temp;

	while (lst)
	{
		temp = lst->next;
		free(lst);
		lst = temp;
	}
	return (NULL);
}

size_t	ft_lst_size(t_lst_arg *lst)
{
	size_t	size;

	size = 0;
	while (lst)
	{
		lst = lst->next;
		size++;
	}
	return (size);
}
