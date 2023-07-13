/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   herdoc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojamal <ojamal@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 18:06:15 by ojamal            #+#    #+#             */
/*   Updated: 2023/07/13 20:49:16 by ojamal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*spaces_skip(char *str)
{
	int		i;
	char	*del;

	i = 0;
	while (str[i] && (str[i] == ' ' || str[i] == '\t'))
		i++;
	del = malloc((i + 1) * sizeof(char *));
	i = 0;
	while (str[i])
	{
		del[i] = str[i];
		i++;
	}
	del[i] = '\0';
	return (del);
}

void	create_herdoc(t_tokens *lexer, t_env_node *env)
{
	t_tokens	*current_token;
	char		*del;
	char		*in;
	int			pipefd[2];
	int			pid;
	char		buffer[1024];
	int			n;

	current_token = lexer;
	while (current_token->e_types != 6)
	{
		if (current_token->e_types == 4)
		{
			lexer = lexer->next;
			current_token = lexer;
			if (current_token->e_types == 1)
				del = spaces_skip(current_token->val);
			pipe(pipefd);
			pid = fork();
			if (pid == -1)
			{
				perror("fork");
				exit(1);
			}
			if (pid == 0)
			{
				close(pipefd[0]);
				while (1)
				{
					in = readline("herdoc> ");
					if (!in)
						break ;
					if (strcmp(del, in) == 0 && ft_strlen(del) == ft_strlen(in))
					{
						free(in);
						break ;
					}
					in = replace_value(in, env, 1);
					while ((n = read(pipefd[0], buffer, sizeof(buffer))) > 0)
						write(pipefd[1], buffer, n);
					free(in);
				}
				close(pipefd[1]);
				exit(0);
			}
			else
			{
				close(pipefd[1]);
				wait(NULL);
			}
		}
		lexer = lexer->next;
		current_token = lexer;
	}
}
