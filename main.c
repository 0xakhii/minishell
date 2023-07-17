/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojamal <ojamal@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/16 16:42:56 by ojamal            #+#    #+#             */
/*   Updated: 2023/07/17 01:13:06 by ojamal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_cmd(t_cmd **cmd)
{
	t_cmd	*tmp;

	while (*cmd)
	{
		tmp = (*cmd)->next;
		free((*cmd)->in_file);
		free((*cmd)->out_file);
		close((*cmd)->in_fd);
		close((*cmd)->out_fd);
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

void	starting_point(char *in, t_env_node *env_list, t_tokens *lexer,
		t_cmd *cmd_table)
{
	add_history(in);
	if (!token_check(lexer) && !syntax_check(lexer))
	{
		cmd_table = create_command_table(lexer, env_list);
		if (cmd_table->in_fd == -1 || cmd_table->out_fd == -1)
			g_helper.exit_status = 1;
		if (cmd_table->cmd)
		{
			signal(SIGINT, SIG_IGN);
			execute(cmd_table, &env_list);
			free_cmd(&cmd_table);
		}
		if (g_helper.exit_status != 0)
			g_helper.flag = 1;
		else
			g_helper.flag = 0;
	}
	else
		g_helper.flag = 1;
}

void	rdline_loop(t_tokens *lexer, t_cmd *cmd_table, t_env_node *env_list,
		char *in)
{
	g_helper.flag = 0;
	lexer = lexer_init(in);
	if (lexer && lexer->e_types != 6)
		starting_point(in, env_list, lexer, cmd_table);
	else
	{
		g_helper.flag = 0;
		g_helper.exit_status = 0;
	}
	cmd_table = NULL;
	free(in);
}

int	main(int ac, char **av, char **env)
{
	t_tokens	*lexer;
	t_env_node	*env_list;
	t_cmd		*cmd_table;
	char		*prompt;
	char		*in;

	(void)ac;
	(void)av;
	prompt = NULL;
	lexer = NULL;
	cmd_table = NULL;
	env_list = create_env_list(env);
	signal(SIGINT, sig_handler);
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		prompt = get_dir(g_helper.flag, env_list);
		in = readline(prompt);
		free(prompt);
		if (!in)
			return (0);
		rdline_loop(lexer, cmd_table, env_list, in);
		signal(SIGINT, sig_handler);
	}
	free_env_list(env_list);
}
