/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymenyoub <ymenyoub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 04:14:46 by ymenyoub          #+#    #+#             */
/*   Updated: 2023/07/16 04:25:16 by ymenyoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	get_exit_status(int status)
{
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	else if (WIFSIGNALED(status))
		return (WTERMSIG(status) + 128);
	return (0);
}

void	child_process(t_cmd *cmd, t_env_node *env, int *in)
{
	signal(SIGINT, sig_handler);
	signal(SIGQUIT, SIG_DFL);
	if (cmd->in_fd == -1 || cmd->out_fd == -1)
		exit(1);
	if (cmd->in_fd != -2)
		dup2(cmd->in_fd, STDIN_FILENO);
	else
		dup2(*in, STDIN_FILENO);
	if (cmd->out_fd != -2)
		dup2(cmd->out_fd, STDOUT_FILENO);
	else if (cmd->next)
		dup2(cmd->fd[1], STDOUT_FILENO);
	if (cmd->next)
	{
		close(cmd->fd[1]);
		close(cmd->fd[0]);
	}
	ft_lunch(cmd, env);
	exit(0);
}

void	wait_and_signal(t_cmd *cmd)
{
	t_cmd	*temp;
	int		status;

	temp = cmd;
	while (temp)
	{
		waitpid(temp->pid, &status, 0);
		g_helper.exit_status = get_exit_status(status);
		if (WIFSIGNALED(status) && WTERMSIG(status) == SIGQUIT)
			printf("^\\Quit: %d\n", WTERMSIG(status));
		temp = temp->next;
	}
}

void	ft_exec(t_cmd *cmd, t_env_node *env)
{
	t_cmd	*temp;
	int		in;

	in = 0;
	temp = cmd;
	while (cmd)
	{
		if (cmd->next)
			pipe(cmd->fd);
		cmd->pid = fork();
		if (cmd->pid == 0)
			child_process(cmd, env, &in);
		else
		{
			if (cmd->prev)
				close(in);
			in = cmd->fd[0];
			if (cmd->next)
				close(cmd->fd[1]);
		}
		cmd = cmd->next;
	}
	wait_and_signal(temp);
}
