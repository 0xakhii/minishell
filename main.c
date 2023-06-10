/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojamal <ojamal@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/16 16:42:56 by ojamal            #+#    #+#             */
/*   Updated: 2023/06/10 04:41:47 by ojamal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av, char **env)
{
	t_tokens	*lexer;
	t_env_node	*env_list;
	char		*in;

	(void)ac;
	(void)av;
	lexer = NULL;
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
		syntax_check(lexer);
		token_check(lexer);
		env_list = create_env_list(env);
		expand_command(lexer, env_list);
		printing(lexer);
	}
}

		// printing2(env_list);