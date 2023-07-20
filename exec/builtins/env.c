/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojamal <ojamal@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 01:17:53 by ymenyoub          #+#    #+#             */
/*   Updated: 2023/07/20 22:30:10 by ojamal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	print_env(char **cmd, t_env_node *env)
{
	t_env_node	*tmp;

	tmp = env;
	if (cmd[1])
		printf("env: ‘%s’: No such file or directory\n", cmd[1]);
	else
	{
		while (tmp)
		{
			if (tmp->key && tmp->value && ft_strcmp(tmp->value, "\0"))
			{
				ft_putstr_fd(tmp->key, 1);
				ft_putchar_fd('=', 1);
				if (ft_strcmp(tmp->value, "\"\""))
					ft_putstr_fd(tmp->value, 1);
				ft_putchar_fd('\n', 1);
			}
			tmp = tmp->next;
		}
	}
}
