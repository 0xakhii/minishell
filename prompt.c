/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojamal <ojamal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 09:28:52 by ojamal            #+#    #+#             */
/*   Updated: 2023/04/04 01:28:27 by ojamal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_prompt()
{
	char	*cwd;
	char	*input;

	while (1)
	{
		signal(SIGQUIT, SIG_IGN);
    	cwd = getcwd(NULL, sizeof(cwd));
		cwd = ft_strjoin(cwd, "$>");
		input = readline(cwd);
		check_all(input);
		char **out = ft_split(input, ' ');
		for(int i = 0; out[i]; i++)
			printf("%s\n", out[i]);
		add_history(input);
		if (ft_strcmp(input, "exit") == 0)
			exit(0);
	}
	return (input);
}


int	get_cmd()
{
	char	*cmd;
	cmd = get_prompt();
	return 0;
}