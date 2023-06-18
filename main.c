/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojamal <ojamal@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/16 16:42:56 by ojamal            #+#    #+#             */
/*   Updated: 2023/06/18 03:27:13 by ojamal           ###   ########.fr       */
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

void print_cmd_table(t_cmd *cmd_t)
{
    t_cmd *cmd = cmd_t;

    while (cmd)
    {
		int i = 0;
		while (cmd->cmd && cmd->cmd[i])
		{
			printf("Command: %s\n", cmd->cmd[i]);
			i++;
		}
		printf("Input file: %s\n", cmd->in_file);
		printf("Output file: %s\n", cmd->out_file);
		printf("Append file: %s\n", cmd->out_file);
		printf("Heredoc file: %s\n", cmd->in_file);
        cmd = cmd->next;
    }
}



int	main(int ac, char **av, char **env)
{
	t_tokens	*lexer;
	t_env_node	*env_list;
	t_cmd *cmd_table;
	char		*in;
	int		exit_stat;

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
		if (token_check(lexer))
			exit_stat = 1;
		if (syntax_check(lexer))
			exit_stat = 127;
		expand_command(lexer, env_list);
		cmd_table = create_command_table(lexer);
		// print_cmd_table(cmd_table);
		free_tokens(&lexer);
		free(in);
	}
}
