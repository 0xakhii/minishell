/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_builtins.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojamal <ojamal@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 00:10:21 by ymenyoub          #+#    #+#             */
/*   Updated: 2023/06/22 06:41:57 by ojamal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"


void	execute_builtins(t_cmd *cmd, t_env_node *env)
{
	if (!cmd->cmd)
		return;
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
	else if (!ft_strcmp(cmd->cmd[0], "unset"))
		my_unset(cmd, env);
	else
		EXIT_FAILURE;
}
int	is_builtins(t_cmd *cmd)
{
	if (!cmd->cmd)
		return 0;
	if (!ft_strcmp(cmd->cmd[0], "echo"))
		return (1);
	else if (!ft_strcmp(cmd->cmd[0], "env"))
		return (1);
	else if (!ft_strcmp(cmd->cmd[0], "exit"))
		return (1);
	if (!ft_strcmp(cmd->cmd[0], "pwd"))
		return (1);
	else if (!ft_strcmp(cmd->cmd[0], "cd"))
		return (1);
	// else if (!ft_strcmp(cmd, "export"))
	else if (!ft_strcmp(cmd->cmd[0], "unset"))
		return (1);
	return (0);
}