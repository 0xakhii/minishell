/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojamal <ojamal@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 21:36:53 by ymenyoub          #+#    #+#             */
/*   Updated: 2023/07/19 21:54:22 by ojamal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	execute(t_cmd *cmd, t_env_node **envl)
{
	if (cmd->next == NULL && is_builtins(cmd))
	{
		execute_builtins(cmd, envl);
		g_helper.exit_status = 0;
	}
	else
		ft_exec(cmd, *envl);
}

void	check_dir(char *cmd)
{
	int	tmp;

	tmp = open(cmd, O_DIRECTORY);
	if (tmp != -1)
	{
		if (cmd[0] == '.' && !cmd[1])
		{
			ft_putstr_fd(". : filename argument required\n", 2);
			exit(2);
		}
		else if (cmd[0] == '.' && cmd[1] == '.' && cmd[2] != '/')
		{
			ft_putstr_fd(cmd, 2);
			ft_putstr_fd(": Command not found.\n", 2);
			exit(127);
		}
		else
		{
			close(tmp);
			ft_putstr_fd(cmd, 2);
			ft_putstr_fd(": is a directory\n", 2);
			exit(126);
		}
	}
}

void	norm_check(t_cmd *cmd, t_env_node *env_list)
{
	char	*p_name;
	char	**env;

	p_name = NULL;
	env = node_to_2d(env_list);
	if (cmd->cmd[0])
		p_name = ft_get_path(cmd->cmd[0], env_list);
	if ((p_name != NULL && execve(p_name, cmd->cmd, env) < 0)
		|| !cmd->cmd[0])
	{
		ft_putstr_fd(cmd->cmd[0], 2);
		ft_putstr_fd(": Command not found.\n", 2);
		ft_freeeeee(cmd->cmd);
		exit(127);
	}
	else if (p_name == NULL)
	{
		check_dir(cmd->cmd[0]);
		ft_putstr_fd(cmd->cmd[0], 2);
		ft_putstr_fd(": Command not found.\n", 2);
		ft_freeeeee(cmd->cmd);
		exit(127);
	}
}

void	ft_lunch(t_cmd *cmd, t_env_node *env_list)
{
	char	*p_name;
	char	**env;

	p_name = NULL;
	env = node_to_2d(env_list);
	if (cmd->cmd[0])
		check_dir(cmd->cmd[0]);
	if (cmd->cmd[0] && execve(cmd->cmd[0], cmd->cmd, env) < 0)
	{
		if ((cmd->cmd[0][0] == '.' && cmd->cmd[0][1] == '/')
			|| cmd->cmd[0][0] == '/')
		{
			if (access(cmd->cmd[0], X_OK) == 0)
				execve(p_name, cmd->cmd, env);
			else
			{
				perror(cmd->cmd[0]);
				exit(127);
			}
		}
		norm_check(cmd, env_list);
		ft_freeeeee(env);
		exit(127);
	}
}
