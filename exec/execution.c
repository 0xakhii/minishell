/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojamal <ojamal@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 21:36:53 by ymenyoub          #+#    #+#             */
/*   Updated: 2023/07/13 22:22:50 by ojamal           ###   ########.fr       */
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

void	ft_lunch(t_cmd *cmd, t_env_node *env_list)
{
	char	*p_name;
	char	**env;

	p_name = NULL;
	env = node_to_2d(env_list);
	if (cmd->cmd && execve(cmd->cmd[0], cmd->cmd, env) < 0)
	{
		if (cmd->cmd[0][0] == '.' && cmd->cmd[0][1] == '/')
		{
			if (access(cmd->cmd[0], X_OK) == 0)
				execve(p_name, cmd->cmd, env);
			else
			{
				perror(cmd->cmd[0]);
				return ;
			}
		}
		p_name = ft_get_path(cmd->cmd[0], env_list);
		if (access(p_name, X_OK) == 0)
		{
			if (p_name != NULL && execve(p_name, cmd->cmd, env) < 0)
			{
				printf("%s: Command not found.\n", cmd->cmd[0]);
				ft_freeeeee(cmd->cmd);
				exit(127);
			}
			else if (p_name == NULL)
			{
				printf("%s: Command not found.\n", cmd->cmd[0]);
				ft_freeeeee(cmd->cmd);
				exit(127);
			}
		}
		else
		{
			printf("hh\n");
		}
	}
	ft_freeeeee(env);
}

void	ft_exec(t_cmd *cmd, t_env_node *env)
{
	t_cmd	*temp;

	temp = cmd;
	while (cmd)
	{
		if (cmd->next)
			pipe(cmd->fd);
		cmd->pid = fork();
		if (cmd->pid == 0)
		{
			if (!cmd->in_file)
				dup2(cmd->in_fd, STDIN_FILENO);
			else if (cmd->prev)
			{
				close(cmd->prev->fd[1]);
				dup2(cmd->prev->fd[0], STDIN_FILENO);
			}
			if (cmd->out_fd != -2)
				dup2(cmd->out_fd, STDOUT_FILENO);
			else if (cmd->next)
			{
				close(cmd->fd[0]);
				dup2(cmd->fd[1], STDOUT_FILENO);
			}
			ft_lunch(cmd, env);
			exit(0);
		}
		else
		{
			if (cmd->prev)
			{
				close(cmd->prev->fd[0]);
				close(cmd->prev->fd[1]);
			}
		}
		cmd = cmd->next;
	}
	while (temp)
	{
		// if(cmd->in_file)
		// 	close(cmd->in_fd);
		// if(cmd->out_file)
		// 	close(cmd->out_fd);
		waitpid(temp->pid, NULL, 0);
		// g_helper.exit_status = 0;
		temp = temp->next;
	}
}
// void	multiple_pipe(t_cmd *cmd, t_env_node *env)
// {
// 	int fd[cmd->pipe][2];
// 	int pid;
// 	int i = 0;
// 	int j = 0;

// 	while (i++ < cmd->pipe)
// 	{
// 		if ((pid == fork()) == -1)
// 		{
// 			perror("pipe");
// 			exit(1);
// 		}
// 		if (pid == 0)
// 		{
// 			//"1st child"
// 			if (i == 0)
// 				dup2(fd[i][1], STDOUT_FILENO); //Write
// 			//last
// 			else if (i == cmd->pipe)
// 				dup2(fd[i - 1][0], STDIN_FILENO);//read from before last
// 			//MIDDLE
// 			else
// 			{
// 				dup2(fd[i - 1][0], STDIN_FILENO);
// 				dup2(fd[i][1], STDOUT_FILENO);

// 			}
// 			// Close all pipe ends in the child process
// 			while (j++ < cmd->pipe)
// 			{
// 				close(fd[j][0]);
// 				close(fd[j][1]);
// 			}
// 		}
// 	}
// 	// Close all pipe ends in the parent process
// 	clode(fd[i][1]);
// 	if (pid > 0)
// 	{
// 		while (i < cmd->pipe)
// 			waitpid(pid, NULL, 0);
// 	}
// }
