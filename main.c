/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojamal <ojamal@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/16 16:42:56 by ojamal            #+#    #+#             */
/*   Updated: 2023/06/18 00:51:01 by ojamal           ###   ########.fr       */
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
	t_cmd *cmd = cmd_t;
	while(cmd)
	{
		if(cmd->e_types == T_CMD)
			for(int i = 0; cmd->cmd[i]; i++)
				printf("command: %s\n", cmd->cmd[i]);
		if (cmd->e_types == T_IN_FILE)
			printf("in file: %s	its type: %d\n", cmd->in_file, cmd->e_types);
		if (cmd->e_types == T_OUT_FILE)
			printf("out file: %s	its type: %d\n", cmd->out_file, cmd->e_types);
		cmd = cmd->next;
	}
}

int	main(int ac, char **av, char **env)
{
	t_tokens	*lexer;
	t_env_node	*env_list;
	t_cmd *cmd_table;
	char		*in;

	(void)ac;
	(void)av;
	lexer = NULL;
	cmd_table = NULL;
	env_list = create_env_list(env);
	while (1)
	{
		in = readline("minishell$>");
		if (in)
			add_history(in);
		if (!ft_strcmp(in, "exit"))
			exit(0);
		else if (!ft_strcmp(in, "clear"))
			system("clear");
		lexer = lexer_init(in);
		token_check(lexer);
		syntax_check(lexer);
		expand_command(lexer, env_list);
		printing(lexer);
		// cmd_table = create_command_table(lexer);
		// print_cmd_table(cmd_table);
		free_tokens(&lexer);
		free(in);
	}
}
