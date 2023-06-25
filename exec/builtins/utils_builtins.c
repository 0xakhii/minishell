/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_builtins.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojamal <ojamal@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 00:10:21 by ymenyoub          #+#    #+#             */
/*   Updated: 2023/06/25 08:56:24 by ojamal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"


void	execute_builtins(t_cmd *cmd, t_env_node **env)
{
	if (!cmd->cmd)
		return;
	if (!ft_strcmp(cmd->cmd[0], "echo"))
		echo_cmd(cmd->cmd);
	else if (!ft_strcmp(cmd->cmd[0], "env"))
		print_env(cmd->cmd, *env);
	else if (!ft_strcmp(cmd->cmd[0], "exit"))
		my_exit(cmd);
	if (!ft_strcmp(cmd->cmd[0], "pwd"))
		pwd_cmd();
	else if (!ft_strcmp(cmd->cmd[0], "cd"))
		cd_cmd(cmd, env);
	else if (!ft_strcmp(cmd->cmd[0], "export"))
		export_variable(cmd, env);
	else if (!ft_strcmp(cmd->cmd[0], "unset"))
		my_unset(cmd, env);
	else
		EXIT_FAILURE;
}
int	is_builtins(t_cmd *cmd)
{
	if (!cmd->cmd)
		return 0;
	if (!ft_strcmp(cmd->cmd[0], "echo") || (!ft_strcmp(cmd->cmd[0], "env")) 
	|| (!ft_strcmp(cmd->cmd[0], "exit")) || (!ft_strcmp(cmd->cmd[0], "pwd")) 
	|| (!ft_strcmp(cmd->cmd[0], "cd")) || (!ft_strcmp(cmd->cmd[0], "export"))
	|| (!ft_strcmp(cmd->cmd[0], "unset")))
		return (1);
	return (0);
}