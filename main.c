/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojamal <ojamal@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/16 16:42:56 by ojamal            #+#    #+#             */
/*   Updated: 2023/07/13 15:04:35 by ojamal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_tokens(t_tokens **t)
{
	t_tokens	*tmp;

	while (*t)
	{
		tmp = (*t)->next;
		free((*t)->val);
		free(*t);
		*t = tmp;
	}
}

void	free_cmd(t_cmd **cmd)
{
	t_cmd	*tmp;

	while (*cmd)
	{
		tmp = (*cmd)->next;
		free((*cmd)->in_file);
		free((*cmd)->out_file);
		ft_freeeeee((*cmd)->cmd);
		free(*cmd);
		*cmd = tmp;
	}
	*cmd = NULL;
}

void	free_env_list(t_env_node *head)
{
	t_env_node	*current;
	t_env_node	*next;

	current = head;
	while (current != NULL)
	{
		next = current->next;
		free(current->key);
		free(current->value);
		free(current);
		current = next;
	}
}

void	print_cmd_table(t_cmd *cmd_t)
{
	t_cmd	*cmd;
	int		i;

	cmd = cmd_t;
	while (cmd)
	{
		i = 1;
		if (cmd && cmd->cmd)
		{
			printf("Command: %s\n", cmd->cmd[0]);
			while (cmd->cmd && cmd->cmd[i - 1] && cmd->cmd[i])
			{
				printf("args: %s\n", cmd->cmd[i]);
				i++;
			}
		}
		printf("Input file: %s\n", cmd->in_file);
		printf("Output file: %s\n", cmd->out_file);
		printf("Append file: %s\n", cmd->out_file);
		printf("Heredoc file: %s\n", cmd->in_file);
		if (cmd->pipe)
			printf("is piped\n");
		cmd = cmd->next;
	}
}

char	*get_dir(int flag)
{
	char	*currdir;
	char	*color;
	char	*prompt;
	char	*tmp;

	currdir = get_currdir();
	if (flag)
		color = "\033[1;31m";
	else
		color = "\033[1;32m";
	prompt = join_str(color, "➜ \033[0m");
	tmp = join_str(" \033[1;36m", currdir);
	free(currdir);
	currdir = tmp;
	tmp = join_str(currdir, "\033[0m ");
	free(currdir);
	currdir = tmp;
	tmp = join_str(prompt, currdir);
	free(currdir);
	free(prompt);
	return (tmp);
}

void	sig_handler(int sig)
{
	if (sig == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		// rl_replace_line("", 0);
		rl_redisplay();
	}
}

int	main(int ac, char **av, char **env)
{
	t_tokens	*lexer;
	t_env_node	*env_list;
	t_cmd		*cmd_table;
	char		*in;
	char		*prompt;
	int			flag;

	// atexit(leak_report);
	flag = 0;
	(void)ac;
	(void)av;
	(void)env;
	lexer = NULL;
	cmd_table = NULL;
	env_list = create_env_list(env);
	signal(SIGINT, sig_handler);
	while (1)
	{
		prompt = get_dir(flag);
		in = readline(prompt);
		free(prompt);
		if (!in)
			return (0);
		lexer = lexer_init(in);
		if (lexer && lexer->e_types != 6)
		{
			add_history(in);
		 	if (!token_check(lexer) && !syntax_check(lexer))
			{
				create_herdoc(lexer);
				cmd_table = create_command_table(lexer, env_list);
				if (cmd_table->in_fd == -1 || cmd_table->out_fd == -1)
					g_helper.exit_status = 1;
				else
					execute(cmd_table, &env_list);
				flag = 0;
			}
			else
				flag = 1;
		}
		else
		{
			flag = 1;
			g_helper.exit_status = 0;
		}
		free_tokens(&lexer);
		free_cmd(&cmd_table);
		cmd_table = NULL;
		free(in);
	}
	free_env_list(env_list);
}
