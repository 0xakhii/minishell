/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojamal <ojamal@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 23:13:04 by ojamal            #+#    #+#             */
/*   Updated: 2023/06/10 04:16:25 by ojamal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	check_squote(t_tokens *quote_token, t_tokens *lexer,
		bool in_single_quotes)
{
	while (quote_token != lexer)
	{
		if (quote_token->val[0] == '\'' && quote_token->e_types == T_STR)
			in_single_quotes = !in_single_quotes;
		quote_token = quote_token->next;
	}
	return (in_single_quotes);
}

void	expander_help(t_tokens *lexer, t_env_node *env_list, t_tokens *lexerv1,
		char *env_name)
{
	t_env_node	*env_node;
	t_tokens	*quote_token;
	bool		in_single_quotes;

	env_node = env_list;
	in_single_quotes = false;
	quote_token = lexerv1;
	in_single_quotes = check_squote(quote_token, lexer, in_single_quotes);
	if (!in_single_quotes)
	{
		while (env_node != NULL)
		{
			if (ft_strcmp(env_node->key, env_name) == 0)
			{
				free(lexer->val);
				lexer->val = ft_strdup(env_node->value);
				break ;
			}
			env_node = env_node->next;
		}
	}
}

t_tokens	*expand_command(t_tokens *lexer, t_env_node *env_list)
{
	t_tokens	*current_token;
	char		*token_value;
	char		*env_name;

	current_token = lexer;
	while (current_token)
	{
		token_value = current_token->val;
		if (token_value && token_value[0] == '$')
		{
			env_name = token_value + 1;
			expander_help(current_token, env_list, lexer, env_name);
		}
		current_token = current_token->next;
	}
	return (lexer);
}
