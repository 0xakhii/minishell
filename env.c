/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojamal <ojamal@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 12:07:55 by ojamal            #+#    #+#             */
/*   Updated: 2023/07/02 18:35:04 by ojamal           ###   ########.fr       */
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

char	*create_key(char *env_str, size_t key_len)
{
	char	*key;

	key = malloc((key_len + 1) * sizeof(char));
	ft_strncpy(key, env_str, key_len);
	key[key_len] = '\0';
	return (key);
}

void	append_to_list(t_env_node **head, t_env_node **tail,
		t_env_node *new_node)
{
	if (*head == NULL)
	{
		*head = new_node;
		*tail = new_node;
	}
	else
	{
		(*tail)->next = new_node;
		*tail = new_node;
	}
}

void	fill_env_list(char **env, t_env_node **head, t_env_node **tail)
{
	t_env_node	*new_node;

	g_helper.i = 0;
	while (env[g_helper.i] != NULL)
	{
		g_helper.equal_sign = ft_strchr(env[g_helper.i], '=');
		if (g_helper.equal_sign != NULL)
		{
			g_helper.key_len = g_helper.equal_sign - env[g_helper.i];
			g_helper.value_start = g_helper.equal_sign + 1;
			g_helper.key = create_key(env[g_helper.i], g_helper.key_len);
			new_node = create_env_node(g_helper.key, g_helper.value_start);
			append_to_list(head, tail, new_node);
			free(g_helper.key);
		}
		g_helper.i++;
	}
}

t_env_node	*create_env_list(char **env)
{
	t_env_node	*head;
	t_env_node	*tail;

	head = NULL;
	tail = NULL;
	
	fill_env_list(env, &head, &tail);
	return (head);
}
