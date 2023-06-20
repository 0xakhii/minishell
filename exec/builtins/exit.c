/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojamal <ojamal@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 01:17:10 by ymenyoub          #+#    #+#             */
/*   Updated: 2023/06/20 10:59:06 by ojamal           ###   ########.fr       */
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

void	my_exit(t_cmd *cmd)
{
	char	*nextarg;

	// Check if the next argument is a digit
	if (cmd->cmd[1])
	{
		nextarg = cmd->cmd[1];
		while (*nextarg)
		{
			if (!is_digit(nextarg)) 
			{
				printf("exit\n");
				printf("exit: %s: numeric argument required\n", nextarg);
				exit(1);
			}
			nextarg++;
		}
		if (cmd->cmd[2]) 
		{
			printf("exit\n");
			printf("Exit: too many arguments!\n");
			//exit(1);
		}
	}
	printf("exit\n");
	exit(0);
}