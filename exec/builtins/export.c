/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojamal <ojamal@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 01:16:05 by ymenyoub          #+#    #+#             */
/*   Updated: 2023/06/23 23:38:36 by ojamal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int check_emptyy(char *cmd)
{
	int i = 0;
	while (cmd[i])
	{
		if (cmd[i] != ' ' && cmd[i] != '\t')
			return (1);
		i++;
	}
	return (0);
}

int	check_inputt(char *str)
{
	int i = 0;
	while(str[i])
	{
		if (!((str[i] >= 'a' && str[i] <= 'z') || (str[i] >= 'A' && str[i] <= 'Z') 
		|| str[i] == '_') || !check_emptyy(str))
		{
			printf("export: not a valid identifier\n");
			return (0);
		}
		i++;
	}
	return (1);
}

void add_node(t_env_node **env, char *key, char *value)
{
	t_env_node *new_node = (t_env_node *)malloc(sizeof(t_env_node));
	new_node->key = ft_strdup(key);
	new_node->value = ft_strdup(value); 
	new_node->next = NULL;

	// If the env list is empty, make the new node the head
	if (*env == NULL)
		*env = new_node;
	else
	{
		// Find the last node and add the new node to the end
		t_env_node *temp = *env;
		while (temp->next != NULL)
		{
			temp = temp->next;
		}
		temp->next = new_node;
	}
}

void export_variable(t_cmd *cmd, t_env_node **env)
{
	// if (check_inputt(cmd->cmd[1]))
	// {
		// Check if there is a key-value pair separated by '='
		char *equal_sign = ft_strchr(cmd->cmd[1], '=');
		if (equal_sign != NULL)
		{
			// Split the string into key and value
			*equal_sign = '\0';
			char *key = cmd->cmd[1];
			char *value = equal_sign + 1;
			add_node(env, key, value);
			printf("Exported variable: %s=%s\n", key, value);
		}
		else
		{
			printf("export: invalid format. Expected key=value\n");
		}
	// }
}

void p_env(t_env_node *env)
{
	printf("\nExported variables:\n");
	t_env_node *temp = env;
	while (temp != NULL)
	{
		printf("%s=%s\n", temp->key, temp->value);
		temp = temp->next;
	}
}

void free_env(t_env_node *env)
{
	t_env_node *temp = env;
	while (temp != NULL)
	{
		t_env_node *next = temp->next;
		free(temp->key);
		free(temp->value);
		free(temp);
		temp = next;
	}
}
