/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojamal <ojamal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 09:28:52 by ojamal            #+#    #+#             */
/*   Updated: 2023/04/05 09:28:08 by ojamal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char **lexer(char *input)
{
	char **tokens;
	int	i;
	int	j;
	int	k;

	i = 0;
	j = 0;
	k = 0;
	tokens = (char **)malloc(sizeof(char *) * 100);
	while(input[i])
	{
		tokens[j] = malloc(sizeof(char *) * 100);
		if (ft_isquote(input[i]))
		{
			while (input[i] && !ft_isquote(input[++i]))
				tokens[j][k++] = input[i];
			if (!ft_isquote(input[i]))
				printf("Minishell: Unmatched quotes\n");
			tokens[j][k] = '\0';
		}
		else if
		i++;
	}
	
	return (tokens);
}

char	*get_prompt()
{
	char	*cwd;
	char	*input;
	char	**tokens;

	while (1)
	{
    	cwd = getcwd(NULL, sizeof(cwd));
		cwd = ft_strjoin(cwd, "$>");
		input = readline(cwd);
		// check_all(input);
		tokens = lexer(input);
		if (input && *input)
			add_history(input);
		for (int i = 0; tokens[i]; i++)
			printf("%s\n", tokens[i]);
	}
	return (input);
}


int	get_cmd()
{
	char	*cmd;
	cmd = get_prompt();
	return 0;
}