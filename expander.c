/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojamal <ojamal@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 12:07:55 by ojamal            #+#    #+#             */
/*   Updated: 2023/06/07 04:57:42 by ojamal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env_node	*create_env_node(char *key, char *value)
{
	t_env_node	*new_node;

	new_node = malloc(sizeof(t_env_node));
	new_node->key = ft_strdup(key);
	new_node->value = ft_strdup(value);
	new_node->next = NULL;
	return (new_node);
}

void	split_key_value(t_env_node *head, t_env_node *tail,
		t_env_node *new_node)
{
	if (head == NULL)
	{
		head = new_node;
		tail = new_node;
	}
	else
	{
		tail->next = new_node;
		tail = new_node;
	}
}

t_env_node	*create_env_list(char **env)
{
	t_env_node	*head;
	t_env_node	*tail;
	int			i;
	char		*equal_sign;
	size_t		key_len;
	char		*value_start;
			char key[key_len + 1];
	t_env_node	*new_node;

	head = NULL;
	tail = NULL;
	i = 0;
	while (env[i] != NULL)
	{
		equal_sign = ft_strchr(env[i], '=');
		if (equal_sign != NULL)
		{
			key_len = equal_sign - env[i];
			value_start = equal_sign + 1;
			ft_strncpy(key, env[i], key_len);
			key[key_len] = '\0';
			new_node = create_env_node(key, value_start);
			split_key_value(head, tail, new_node);
		}
		i++;
	}
	return (head);
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
	while (quote_token != lexer)
	{
		if (quote_token->val[0] == '\'' && quote_token->types == T_STR)
			in_single_quotes = !in_single_quotes;
		quote_token = quote_token->next;
	}
	if (!in_single_quotes)
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
