/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_programs.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jusilanc <jusilanc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 13:48:18 by jusilanc          #+#    #+#             */
/*   Updated: 2023/06/19 16:35:52 by jusilanc         ###   ########.fr       */
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
char	**ft_cd(t_lst_arg *arg, char **env);
int		ft_pwd(t_lst_arg *arg, char **env);
char	**ft_exit(t_lst_arg *arg, char **env);

char	*var_to_str(char *str, char **env, size_t *i);
char	*ft_str_var_process(char *arg, char **env);

#endif