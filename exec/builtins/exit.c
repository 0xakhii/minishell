/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojamal <ojamal@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 01:17:10 by ymenyoub          #+#    #+#             */
/*   Updated: 2023/07/19 01:04:34 by ojamal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	check_max_min(int i, char *str)
{
	if (i >= 19 && str[0] != '-')
	{
		if (str[i - 1] > '7')
			return (0);
		else if (i > 19)
			return (0);
	}
	else if (i > 19 && str[0] == '-')
	{
		if (str[i - 1] > '8')
			return (0);
		else if (i > 20)
			return (0);
	}
	return (1);
}

int	is_digit(char *str)
{
	int	i;
	int	sign;

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
	if (!check_max_min(i, str))
		return (0);
	return (1);
}

void	check_args_exit(t_cmd *cmd)
{
	if (cmd->cmd[2])
	{
		if (!is_digit(cmd->cmd[1]))
		{
			if (!cmd->pipe)
				printf("exit\n");
			printf("exit: %s: numeric argument required\n", cmd->cmd[1]);
			exit(255);
		}
		else
		{
			if (!cmd->pipe)
				printf("exit\n");	
			printf("Exit: too many arguments!\n");
			if (cmd->pipe)
				exit(1);
		}
	}
}

void	my_exit(t_cmd *cmd)
{
	if (cmd->cmd[0] && !cmd->cmd[1])
	{
		if (!cmd->pipe)
			printf("exit\n");
		exit(0);
	}
	if (cmd->cmd[1] && !cmd->cmd[2])
	{
		if (!is_digit(cmd->cmd[1]) || cmd->cmd[1][0] == '\0')
		{
			if (!cmd->pipe)
				printf("exit\nexit: %s: numeric argument required\n", cmd->cmd[1]);
			exit(255);
		}
		if (cmd->cmd[1])
		{
			if (is_digit(cmd->cmd[1]))
			{
				if (!cmd->pipe)
					printf("exit\n");
				exit(ft_atoi(cmd->cmd[1]));
			}
		}
	}
	check_args_exit(cmd);
}
