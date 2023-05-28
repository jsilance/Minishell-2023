/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_programs.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jusilanc <jusilanc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 13:48:18 by jusilanc          #+#    #+#             */
/*   Updated: 2023/05/28 19:06:46 by jusilanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PROGRAMS_H
# define FT_PROGRAMS_H

# include "minishell.h"

void	ft_cmd_lst_execute(t_lst_cmd *cmd, char ***env);

int		ft_echo(t_lst_arg *arg, char **env);
char	**ft_export(t_lst_arg *arg, char **env);
char	**ft_unset(t_lst_arg *arg, char **env);
int		ft_env(char **env);

#endif