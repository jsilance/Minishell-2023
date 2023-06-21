/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_programs.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avancoll <avancoll@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 13:48:18 by jusilanc          #+#    #+#             */
/*   Updated: 2023/06/21 11:38:31 by avancoll         ###   ########.fr       */
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
int		ft_exit(t_lst_arg *arg, char **env);

char	*var_to_str(char *str, char **env, size_t *i);
char	*ft_str_var_process(char *arg, char **env);
void	home_checker(char *arg, size_t *i, char **ptr, char **env);
int		command_selector(t_lst_arg *ptr, char ***env);
int		basic_builtin(t_lst_arg *ptr, char ***env);
char	*cd_special_case(char *str);

void	ft_swap(char **a, char **b);
void	ft_sort_char_tab(char **tab, int size);
size_t	ft_tab_len(char **tab);

#endif