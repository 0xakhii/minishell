/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojamal <ojamal@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 12:07:55 by ojamal            #+#    #+#             */
/*   Updated: 2023/06/21 11:00:42 by ojamal           ###   ########.fr       */
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
	t_helper	helper;
	t_env_node	*new_node;

	helper.i = 0;
	while (env[helper.i] != NULL)
	{
		helper.equal_sign = ft_strchr(env[helper.i], '=');
		if (helper.equal_sign != NULL)
		{
			helper.key_len = helper.equal_sign - env[helper.i];
			helper.value_start = helper.equal_sign + 1;
			helper.key = create_key(env[helper.i], helper.key_len);
			new_node = create_env_node(helper.key, helper.value_start);
			append_to_list(head, tail, new_node);
			free(helper.key);
		}
		helper.i++;
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
