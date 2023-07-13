/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   herdoc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymenyoub <ymenyoub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 18:06:15 by ojamal            #+#    #+#             */
/*   Updated: 2023/07/13 03:18:51 by ymenyoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*spaces_skip(char *str)
{
	int i = 0;
	while(str[i] && (str[i] != ' ' || str[i] != '\t'))
		i++;
	char *del = malloc((i + 1) * sizeof(char *));
	i = 0;
	while(str[i] && (str[i] != ' ' || str[i] != '\t'))
	{
		del[i] = str[i];
		i++;
	}
	del[i] = '\0';
	return (del);
}

void	create_herdoc(t_tokens *lexer)
{
	t_tokens	*current_token;
	char		*del;
	char		*in;
	current_token = lexer;
	while(current_token->e_types != 6)
	{
		if (current_token->e_types == 4)
		{
			lexer = lexer->next;
			current_token = lexer;
			if(current_token->e_types == 1)
				del = spaces_skip(current_token->val);
			while(1)
			{
				in = readline("herdoc> ");
				if (!in)
					break ;
				if (ft_strncmp(del, in, ft_strlen(del)) == 0
					&& ft_strlen(del) == ft_strlen(in))
					break ;
				free(in);
			}
		}
		lexer = lexer->next;
		current_token = lexer;
	}
}