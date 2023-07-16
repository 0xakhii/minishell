/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymenyoub <ymenyoub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 21:36:53 by ymenyoub          #+#    #+#             */
/*   Updated: 2023/07/16 04:15:26 by ymenyoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	execute(t_cmd *cmd, t_env_node **envl)
{
	if (cmd->next == NULL && is_builtins(cmd))
		execute_builtins(cmd, envl);
	else
		ft_exec(cmd, *envl);
}

void	save_fd(int save[2])
{
	save[0] = dup(STDIN_FILENO);
	save[1] = dup(STDOUT_FILENO);
}

void	check_dir(char *cmd)
{
	int	tmp;

	tmp = open(cmd, O_DIRECTORY);
	if (tmp != -1)
	{
		if (cmd[0] == '.' && !cmd[1])
		{
			printf(": filename argument required\n");
			exit(2);
		}
		else if (cmd[0] == '.' && cmd[1] == '.' && cmd[2] != '/')
		{
			printf(": command not found\n");
			exit(127);
		}
		else
		{
			close(tmp);
			printf("%s: is a directory\n", cmd);
			exit(126);
		}
	}
}

void	norm_check(t_cmd *cmd, t_env_node *env_list)
{
	char	*p_name;
	char	**env;

	env = node_to_2d(env_list);
	p_name = ft_get_path(cmd->cmd[0], env_list);
	if (p_name != NULL && execve(p_name, cmd->cmd, env) < 0)
	{
		printf("%s: Command not found.\n", cmd->cmd[0]);
		ft_freeeeee(cmd->cmd);
		exit(127);
	}
	else if (p_name == NULL)
	{
		check_dir(cmd->cmd[0]);
		printf("%s: Command not found.\n", cmd->cmd[0]);
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
	check_dir(cmd->cmd[0]);
	if (execve(cmd->cmd[0], cmd->cmd, env) < 0)
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
