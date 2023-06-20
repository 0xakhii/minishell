/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojamal <ojamal@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 01:17:53 by ymenyoub          #+#    #+#             */
/*   Updated: 2023/06/20 10:45:00 by ojamal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	print_env(char **cmd, t_env_node *env)
{
	t_env_node *tmp;

	tmp = env;
	if (cmd[1])
			printf("env: ‘%s’: No such file or directory\n", cmd[1]);
	else
	{
		while (tmp)
		{
			ft_putstr_fd(tmp->key, 1);
			ft_putchar_fd('=', 1);
			ft_putstr_fd(tmp->value, 1);
			ft_putchar_fd('\n', 1);
			tmp = tmp->next;
		}
	}
}