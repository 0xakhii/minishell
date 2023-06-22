/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojamal <ojamal@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 01:16:49 by ymenyoub          #+#    #+#             */
/*   Updated: 2023/06/23 00:45:10 by ojamal           ###   ########.fr       */
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
	int i = 0;
	while(str[i])
	{
		if (!((str[i] >= 'a' && str[i] <= 'z') || (str[i] >= 'A' && str[i] <= 'Z')
			|| (str[i] >= '0' && str[i] <= '9')	|| str[i] == '_') || !check_empty(str))
		{
			printf("unset: not a valid identifier\n");
			return (0);
		}
		i++;
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
	// if (!tmp)
	// 	printf("unset: not a valid identifier\n");
	return 0;
}
void	my_unset(t_cmd *cmd, t_env_node **env)
{
	if (!cmd->cmd[1])
		return ;
	if (!check_input(cmd->cmd[1]))
		return ;
	if (loop_env(*env, cmd->cmd[1]))
		delete_node(env, cmd->cmd[1]);
}