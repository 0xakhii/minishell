/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojamal <ojamal@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/16 16:42:56 by ojamal            #+#    #+#             */
/*   Updated: 2023/06/20 10:50:07 by ojamal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_tokens(t_tokens **t)
{
	t_tokens	*tmp;

	while ((*t))
	{
		free((*t)->val);
		(*t)->val = NULL;
		tmp = (*t)->next;
		free((*t));
		(*t) = tmp;
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
		if (cmd->e_types == T_CMD)
		{	
			printf("Command: %s\n", cmd->cmd[0]);
			while (cmd->cmd && cmd->cmd[i - 1] && cmd->cmd[i])
			{
				printf("args: %s\n", cmd->cmd[i]);
				i++;
			}
		}
		if (cmd->e_types == T_IN_FILE)
			printf("Input file: %s\n", cmd->in_file);
		if (cmd->e_types == T_OUT_FILE)
			printf("Output file: %s\n", cmd->out_file);
		if (cmd->e_types == T_APP_FILE)
			printf("Append file: %s\n", cmd->out_file);
		if (cmd->e_types == T_HERD_FILE)
			printf("Heredoc file: %s\n", cmd->in_file);
		if (cmd->pipe)
			printf("is piped\n");
		cmd = cmd->next;
	}
}

char	**new_expand(char *str, char **env);

int	main(int ac, char **av, char **env)
{
	t_tokens	*lexer;
	t_env_node	*env_list;
	t_cmd		*cmd_table;
	char		*in;

	(void)ac;
	(void)av;
	lexer = NULL;
	cmd_table = NULL;
	env_list = create_env_list(env);
	while (1)
	{
		in = readline("minishell$>");
		if (!in)
			return (0);
		if (in)
			add_history(in);
		// if (!ft_strcmp(in, "exit"))
		// 	exit(0);
		lexer = lexer_init(in);
		if (lexer && lexer->e_types != 6 && !token_check(lexer)
			&& !syntax_check(lexer))
		{
			expand_command(lexer, env_list);
			cmd_table = create_command_table(lexer);
			execute_builtins(cmd_table, env_list);
		}
		// printing(lexer);
		// print_cmd_table(cmd_table);
		cmd_table = NULL;
		free_tokens(&lexer);
		free(in);
	}
}
