/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jusilanc <jusilanc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 16:33:21 by jusilanc          #+#    #+#             */
/*   Updated: 2023/06/21 16:09:48 by jusilanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_is_good_char(char *str, int len)
{
	int	i;

	i = 0;
	while (str && str[i] && str[i] != '=' && (len == -1 || i < len))
	{
		if ((str[i] < '0' || str[i] > '9') && (str[i] < 'a' || str[i] > 'z')
			&& (str[i] < 'A' || str[i] > 'Z') && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int	ft_atoi(const char *str)
{
	long	nb;
	long	neg;

	nb = 0;
	neg = 1;
	while (str && *str && ((*str >= 9 && *str <= 13) || *str == 32))
		str++;
	if (str && (*str == '+' || *str == '-'))
		if (*str++ == '-')
			neg = -1;
	while (str && ft_isdigit(*str))
	{
		nb = nb * 10 + *str++ - '0';
		if (nb < 0 && neg == 1)
			return (-1);
		if (nb < 0 && neg == -1)
			return (0);
	}
	return (nb * neg);
}
