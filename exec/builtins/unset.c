/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymenyoub <ymenyoub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 01:16:49 by ymenyoub          #+#    #+#             */
/*   Updated: 2023/06/22 05:54:34 by ymenyoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int check_empty(char *str)
{
	int i = 0;
	while (str[i])
	{
		if (str[i] != ' ' && str[i] != '\t')
			return (1);
		i++;
	}
	return (0);
}

int	check_input(char *str)
{

	if (!((str[0] >= 'a' && str[0] <= 'z') || (str[0] >= 'A' && str[0] <= 'Z')
			|| str[0] == '_') || !check_empty(str))
	{
		printf("unset: not a valid identifier\n");
		return (0);
	}
	return (1);
}

void delete_node(t_env_node **head, const char *key)
{
	t_env_node *current = *head;
	t_env_node *prev = NULL;

	if (*head == NULL)
		return;
	// Check if the head node has the key
	if (current != NULL && ft_strcmp(current->key, key) == 0)
	{
		*head = current->next;
		free(current->key);
		free(current->value);
		free(current);
		return;
	}
	// Search for the node with the key
	while (current != NULL && ft_strcmp(current->key, key) != 0)
	{
		prev = current;
		current = current->next;
	}
	//If key was not found in the list
	if (current == NULL)
		return;
	prev->next = current->next;
	free(current->key);
	free(current->value);
	free(current);
}

int loop_env(t_env_node *head, char *key)
{
	t_env_node *tmp = head;

	while (tmp)
	{
		if (ft_strcmp(tmp->key, key) == 0)
			return 1;
		tmp = tmp->next;
	}
	return 0;
}
void	my_unset(char *key, t_env_node *env)
{
	// int	i;

	// i = 1;
	// while (args[i])
	// {
		if (!check_input(key))
			return ;
		if (loop_env(env, key))
			delete_node(&env, key);
	// 	i++;
	// }
}