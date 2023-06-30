/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojamal <ojamal@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/16 16:42:56 by ojamal            #+#    #+#             */
/*   Updated: 2023/06/30 17:04:04 by ojamal           ###   ########.fr       */
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

void	free_cmd(t_cmd **cmd)
{
	t_cmd	*tmp;

	while (*cmd)
	{
		ft_freeeeee((*cmd)->cmd);
		free((*cmd)->in_file);
		free((*cmd)->out_file);
		tmp = (*cmd)->next;
		free(*cmd);
		(*cmd) = tmp;
	}
	(*cmd) = NULL;
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

void	put_minishell()
{
	ft_putstr_fd("\033[1;32m███╗   ███╗██╗███╗   ██╗██╗███████╗██╗  ██╗███████╗██╗     ██╗     \n", 1);
	ft_putstr_fd("\033[1;32m████╗ ████║██║████╗  ██║██║██╔════╝██║  ██║██╔════╝██║     ██║     \n", 1);
	ft_putstr_fd("\033[1;32m██╔████╔██║██║██╔██╗ ██║██║███████╗███████║█████╗  ██║     ██║     \n", 1);
	ft_putstr_fd("\033[1;32m██║╚██╔╝██║██║██║╚██╗██║██║╚════██║██╔══██║██╔══╝  ██║     ██║     \n", 1);
	ft_putstr_fd("\033[1;32m██║ ╚═╝ ██║██║██║ ╚████║██║███████║██║  ██║███████╗███████╗███████╗\n", 1);
	ft_putstr_fd("\033[1;32m╚═╝     ╚═╝╚═╝╚═╝  ╚═══╝╚═╝╚══════╝╚═╝  ╚═╝╚══════╝╚══════╝╚══════╝\n\033[0m", 1);
}

char	*get_dir()
{
	char	*currdir;
	char	*prompt;
	
	currdir = get_currdir();
	currdir = join_str(" \033[1;36m", currdir);
	currdir = join_str(currdir, "\033[0m ");
	prompt = join_str("\033[1;32m➜ \033[0m", currdir);
	return (prompt);
}

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
	put_minishell();
	env_list = create_env_list(env);
	while (1)
	{
		in = readline(get_dir());
		if (!in)
			return (0);
		add_history(in);
		lexer = lexer_init(in);
		if (lexer && lexer->e_types != 6 && !token_check(lexer)
			&& !syntax_check(lexer))
		{
			cmd_table = create_command_table(lexer, env_list);
			execute(cmd_table, &env_list);
		}
		free(in);
		free_cmd(&cmd_table);
	}
}
