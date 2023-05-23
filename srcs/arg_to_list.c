/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_to_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jusilanc <jusilanc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 17:01:47 by jusilanc          #+#    #+#             */
/*   Updated: 2023/05/23 17:22:40 by jusilanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_lst_cmd	*ft_list_new(char *content, int len)
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

static t_lst_cmd	*ft_lst_add_back(t_lst_cmd *lst)
{
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
		while (!ft_strchr("\t ", line[i]))
			i++;
		while (ft_strchr("\t ", line[i + len]))
			len++;
	}
}
