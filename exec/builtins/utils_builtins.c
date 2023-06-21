/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_builtins.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojamal <ojamal@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 00:10:21 by ymenyoub          #+#    #+#             */
/*   Updated: 2023/06/21 03:32:24 by ojamal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"


void	execute_builtins(t_cmd *cmd, t_env_node *env)
{
	if (!ft_strcmp(cmd->cmd[0], "echo"))
		echo_cmd(cmd->cmd);
	else if (!ft_strcmp(cmd->cmd[0], "env"))
		print_env(cmd->cmd, env);
	else if (!ft_strcmp(cmd->cmd[0], "exit"))
		my_exit(cmd);
	if (!ft_strcmp(cmd->cmd[0], "pwd"))
		pwd_cmd();
	else if (!ft_strcmp(cmd->cmd[0], "cd"))
		cd_cmd(cmd, env);
	// else if (!ft_strcmp(cmd, "export"))
	// else if (!ft_strcmp(cmd, "unset"))
	else
		EXIT_FAILURE;
}