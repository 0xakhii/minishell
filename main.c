/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojamal <ojamal@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/16 16:42:56 by ojamal            #+#    #+#             */
/*   Updated: 2023/07/01 11:29:49 by ojamal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void free_tokens(t_tokens **t)
{
	t_tokens *tmp;

	while (*t)
	{
		tmp = (*t)->next;
		free((*t)->val);
		free(*t);
		*t = tmp;
	}
}

void free_cmd(t_cmd **cmd)
{
	t_cmd *tmp;

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

void free_env_list(t_env_node *head)
{
	t_env_node *current = head;
	t_env_node *next;

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

void	put_minishell()
{
	ft_putstr_fd("\033[1;32m███╗   ███╗██╗███╗   ██╗██╗███████╗██╗  ██╗███████╗██╗     ██╗     \n", 1);
	ft_putstr_fd("████╗ ████║██║████╗  ██║██║██╔════╝██║  ██║██╔════╝██║     ██║     \n", 1);
	ft_putstr_fd("██╔████╔██║██║██╔██╗ ██║██║███████╗███████║█████╗  ██║     ██║     \n", 1);
	ft_putstr_fd("██║╚██╔╝██║██║██║╚██╗██║██║╚════██║██╔══██║██╔══╝  ██║     ██║     \n", 1);
	ft_putstr_fd("██║ ╚═╝ ██║██║██║ ╚████║██║███████║██║  ██║███████╗███████╗███████╗\n", 1);
	ft_putstr_fd("╚═╝     ╚═╝╚═╝╚═╝  ╚═══╝╚═╝╚══════╝╚═╝  ╚═╝╚══════╝╚══════╝╚══════╝\n\033[0m", 1);
}

char *get_dir(int flag)
{
    char *currdir;
    char *color;
    char *prompt;
    char *tmp;

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
    prompt = join_str(prompt, currdir);
    free(currdir);
    return prompt;
}

int	main(int ac, char **av, char **env)
{
	t_tokens	*lexer;
	t_env_node	*env_list;
	t_cmd		*cmd_table;
	char		*in;
	char		*prompt;
	int			flag;

	flag = 0;
	(void)ac;
	(void)av;
	lexer = NULL;
	cmd_table = NULL;
	put_minishell();
	env_list = create_env_list(env);
	while (1)
	{
		prompt = get_dir(flag);
		in = readline(prompt);
		free(prompt);
		if (!in)
			return (0);
		add_history(in);
		lexer = lexer_init(in);
		if (lexer && lexer->e_types != 6 && !token_check(lexer)
			&& !syntax_check(lexer))
		{
			cmd_table = create_command_table(lexer, env_list);
			execute(cmd_table, &env_list);
			flag = 0;
		}
		else
			flag = 1;
		free(in);
		free_cmd(&cmd_table);
	}
	free_env_list(env_list);
}
