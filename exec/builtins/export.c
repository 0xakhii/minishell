/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojamal <ojamal@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 01:16:05 by ymenyoub          #+#    #+#             */
/*   Updated: 2023/07/20 23:18:53 by ojamal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	check_emptyy(char *cmd)
{
	int	i;

	i = 0;
	while (cmd[i] && ((cmd[i] == ' ') || cmd[i] == '\t'))
		i++;
	if (ft_strlen(cmd) == (size_t)i)
		return (1);
	return (0);
}

int	check_inputt(char *str)
{
	int	i;

	i = 0;
	if (!str || (!ft_isalpha(str[0]) && str[0] != '_'))
		return (msg_er("export: not a valid identifier1"));
	while (str && str[i] != '\0' && str[i] != '=')
	{
		if (str && !((str[i] >= 'a' && str[i] <= 'z') || (str[i] >= 'A'
					&& str[i] <= 'Z') || str[i] == '_'))
		{
			if (check_emptyy(str))
				return (msg_er("export: not a valide identifier2"));
		}
		i++;
	}
	return (0);
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
		{
			free(existing->value);
			existing->value = ft_strdup(value);
		}
		else
			add_node(env, key, value);
	}
}

char	*set_value(t_cmd *cmd, char **equal_sign, int *i, char *value)
{
	char	*str;

	str = ft_strchr(cmd->cmd[*i], '=');
	if (cmd->cmd[*i][0] && cmd->cmd[*i][0] != '=' && equal_sign[1] == NULL
		&& ft_strchr(cmd->cmd[*i], '='))
	{
		value = ft_strdup("\"\"");
	}
	else if (equal_sign[0] && equal_sign[1] == NULL)
		value = ft_strdup("");
	else if (equal_sign[0] && equal_sign[1])
	{
		value = ft_substr(str, 1, ft_strlen(str) - 1);
	}
	return (value);
}

void	export_variable(t_cmd *cmd, t_env_node **env)
{
	char	**equal_sign;
	char	*value;
	char	*key;

	g_helper.i = 0;
	equal_sign = NULL;
	key = NULL;
	if (!cmd->cmd[1])
		print_export(env);
	else
	{
		while (cmd->cmd[++g_helper.i])
		{
			value = NULL;
			if (check_inputt(cmd->cmd[g_helper.i]))
				return ;
			equal_sign = ft_split(cmd->cmd[g_helper.i], '=');
			if (equal_sign[0])
				key = equal_sign[0];
			value = set_value(cmd, equal_sign, &g_helper.i, value);
			append_to_export(key, value, env);
			free(value);
			ft_freeeeee(equal_sign);
		}
	}
}
