/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojamal <ojamal@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 21:36:53 by ymenyoub          #+#    #+#             */
/*   Updated: 2023/06/22 07:00:09 by ojamal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	execute(t_cmd *cmd, t_env_node *env)
{
	// int fd[2];
	// int pid;
	t_cmd *tmp;

	tmp = cmd;
	if (cmd->next == NULL && is_builtins(cmd))
		execute_builtins(cmd, env);
	else
	{
		printf("not builtins\n");
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
}
