/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojamal <ojamal@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 01:17:10 by ymenyoub          #+#    #+#             */
/*   Updated: 2023/06/25 08:15:26 by ojamal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	is_digit(char *str)
{
	int			i;
	int			sign;

	i = 0;
	sign = 1;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	if (i > 19)
		return (0);
	return (1);
}

void	my_exit(t_cmd *cmd)
{
	char	*nextarg;

	if (cmd->cmd[0] && !cmd->cmd[1])
	{
		printf("exit\n");
		exit(0);
	}
	// Check if the next argument is a digit
	if (cmd->cmd[1] && !cmd->cmd[2])
	{
		nextarg = cmd->cmd[1];
		while (*nextarg)
		{
			if (!is_digit(nextarg)) 
			{
				printf("-->%d\n", ft_atoi(nextarg));
				printf("exit\n");
				printf("exit: %s: numeric argument required\n", nextarg);
				exit(1);
			}
			nextarg++;
		}
		if (cmd->cmd[1])
		{
			if (is_digit(nextarg))
			{
				printf("exit\n");
				exit(0);
			}
		}
	}
	if (cmd->cmd[2]) 
	{
		nextarg = cmd->cmd[1];
		if (!is_digit(nextarg)) 
		{
			printf("exit\n");
			printf("exit: %s: numeric argument required\n", nextarg);
			exit(1);
		}
		else
		{
			printf("exit\n");
			printf("Exit: too many arguments!\n");
		}
	}
}
