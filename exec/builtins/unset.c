/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymenyoub <ymenyoub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 01:16:49 by ymenyoub          #+#    #+#             */
/*   Updated: 2023/07/14 00:15:17 by ymenyoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	check_empty(char *str)
{
	int	i;

	i = 0;
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
	int	i;

	i = 0;
	while (str[i])
	{
		if (!((str[i] >= 'a' && str[i] <= 'z')
				|| (str[i] >= 'A' && str[i] <= 'Z')
				|| str[i] == '_') || !check_empty(str))
		{
			printf("unset: not a valid identifier\n");
			return (0);
		}
		i++;
	}
	return (1);
}

void	delete_node(t_env_node **head, const char *key)
{
	t_env_node	*current;
	t_env_node	*prev;

	current = *head;
	prev = NULL;
	if (current != NULL && ft_strcmp(current->key, key) == 0)
	{
		*head = current->next;
		free(current->key);
		free(current->value);
		free(current);
		return ;
	}
	while (current != NULL && ft_strcmp(current->key, key) != 0)
	{
		prev = current;
		current = current->next;
	}
	if (current == NULL)
		return ;
	prev->next = current->next;
	free(current->key);
	free(current->value);
	free(current);
}

int	loop_env(t_env_node *head, char *key)
{
	t_env_node	*tmp;

	tmp = head;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, key) == 0)
			return (1);
		tmp = tmp->next;
	}
	return (0);
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
