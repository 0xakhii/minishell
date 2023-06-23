/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojamal <ojamal@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 21:36:53 by ymenyoub          #+#    #+#             */
/*   Updated: 2023/06/23 23:39:26 by ojamal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	execute(t_cmd *cmd, t_env_node *env_list, char **env)
{
	char	*path;
	int		pid;
	int		status;

	// int fd[2];
	// int pid;
	// t_cmd *tmp;
	// tmp = cmd;
	if (cmd->next == NULL && is_builtins(cmd))
		execute_builtins(cmd, env_list);
	else
	{
		path = NULL;
		if (cmd->cmd[0])
		{
			if (cmd->cmd[0][0] == '.' && cmd->cmd[0][1] == '/')
			{
				if (access(cmd->cmd[0], F_OK) == 0)
					path = ft_strjoin(path, cmd->cmd[0] + 2);
			}
			else
				path = ft_get_path(cmd->cmd[0], env_list);
			pid = fork();
			if (pid == 0)
			{
				if (path != NULL)
				{
					execve(path, cmd->cmd, env);
					printf("Error executing the command.\n");
					exit(1);
				}
				else
				{
					printf("%s: Command not found.\n", cmd->cmd[0]);
					exit(1);
				}
				exit(0);
			}
			else if (pid > 0)
			{
				waitpid(pid, &status, 0);
			}
		}
	}
	// while (tmp)
	// {
	// 	if (pipe(fd) == -1)
	// 		return (1);
	// 	pid = fork;
	// 	if (pid == 0)
	// 	{
	// 		dup2(fd[1], 1);
	// 		dup2(fd[0], 0);
	// 	}
	// }
}
