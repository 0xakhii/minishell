/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymenyoub <ymenyoub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 01:17:53 by ymenyoub          #+#    #+#             */
/*   Updated: 2023/06/20 00:43:07 by ymenyoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	print_env(t_env_node *env, char **cmd)
{
	t_env_node *tmp;

	tmp = env;
	if (cmd[1])
			ft_putstr_fd("env: No such file or directory", 1);
	else
	{
		while (tmp)
		{
			ft_putstr_fd(tmp->key, 1);
			ft_putchar_fd("=", 1);
			ft_putstr_fd(tmp->value, 1);
			tmp = tmp->next;
		}
	}
}