/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymenyoub <ymenyoub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 01:17:10 by ymenyoub          #+#    #+#             */
/*   Updated: 2023/06/20 00:21:24 by ymenyoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	is_digit(char *str)
{
	int	i;

	i = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '+')
		i++;
	while (str[i])
	{
		if ((str[i] < '0' || str[i] > '9'))
			return (0);
		i++;
	}
	return (1);
}

// int	check_args(char **av)
// {
// 	int	i;

// 	i = 1;
// 	while (av[i])
// 	{
// 		if (!is_digit(av[i]))
// 		{
// 			write(2, "must be digits\n", 16);
// 			return (1);
// 		}
// 		i++;
// 	}
// 	return (0);
// }

void	my_exit(int ac, char **av)
{
	char	*nextarg;

	// Check if the next argument is a digit
	nextarg = *av[2];
	while (*nextarg) 
	{
		if (!is_digit(*nextarg)) 
		{
			printf("exit: numeric argument required!\n");
			exit(1);
		}
		nextarg++;
	}
	if (ac > 3) 
	{
		printf("Exit: too many arguments!\n");
		//exit(1);
	}
	exit(0);
}