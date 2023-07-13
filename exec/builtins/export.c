/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojamal <ojamal@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 01:16:05 by ymenyoub          #+#    #+#             */
/*   Updated: 2023/07/13 23:50:29 by ojamal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	check_emptyy(char *cmd)
{
	int	i;

	i = 0;
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
	int	i;
	int	id;

	i = 0;
	id = 0;
	if (!str[0] || str[0] == '+')
		return (msg_er("export: not a valid identifier"));
	while (str[i])
	{
		if (!((str[i] >= 'a' && str[i] <= 'z') || (str[i] >= 'A'
					&& str[i] <= 'Z') || str[i] == '_'))
		{
			if (id && str[i] != '+' && !(str[i] == '=' && str[i - 1] == '+'))
				return (msg_er("export: not a valid identifier"));
			else if (!id)
				id = 1;
		}
		i++;
	}
	return (0);
}

void	print_export(t_env_node **env)
{
	t_env_node	*tmp;

	tmp = *env;
	while (tmp)
	{
		if (tmp->key)
		{
			printf("declare -x %s", tmp->key);
			if (ft_strcmp(tmp->value, "\0"))
			{
				if (tmp->value[0] != '\"' && tmp->value[ft_strlen(tmp->value)
					- 1] != '\"')
					printf("=\"%s\"", tmp->value);
				else
					printf("=%s", tmp->value);
			}
			printf("\n");
		}
		tmp = tmp->next;
	}
}

void	append_to_export(char *key, char *value, t_env_node **env)
{
	t_env_node	*existing;

	if (check_inputt(key))
		return ;
	else
	{
		existing = find_node(env, key);
		if (existing && value)
			existing->value = ft_strdup(value);
		else
			add_node(env, key, value);
	}
}

void	export_variable(t_cmd *cmd, t_env_node **env)
{
	char	**equal_sign;
	char	*value;
	char	*key;
	int		i;

	i = 0;
	if (!cmd->cmd[1])
		print_export(env);
	else
	{
		while (cmd->cmd[++i])
		{
			value = NULL;
			equal_sign = ft_split(cmd->cmd[i], '=');
			if (equal_sign[0])
				key = equal_sign[0];
			if (cmd->cmd[i][0] && equal_sign[1] == NULL && ft_strchr(cmd->cmd[i], '='))
				value = "\"\"";
			else if (equal_sign[0] && equal_sign[1] == NULL)
				value = "";
			else if (equal_sign[0] && equal_sign[1])
				value = equal_sign[1];
			append_to_export(key, value, env);
		}
	}
}
