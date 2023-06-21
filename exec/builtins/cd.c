/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojamal <ojamal@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 01:13:46 by ymenyoub          #+#    #+#             */
/*   Updated: 2023/06/21 03:37:09 by ojamal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// cd av[1] ==  - == OLDPWD(env) == 0 chdir("oldpwd")  !=0 OLDPWD NOT SET

// cd ||  cd~ chdir("HOME")

void    cd_cmd(t_cmd *cmd, t_env_node *env)
{
    t_env_node *tmp = env;
    if (cmd->cmd[1] && (cmd->cmd[1][0] == '~'))
    {
        while(tmp)
        {
            if (!ft_strcmp(tmp->key, "HOME"))
                chdir(tmp->value);
            tmp = tmp->next;
        }
    }
    else if (!cmd->cmd[1])
    {
        tmp = env;
        while(tmp)
        {
            if (!ft_strcmp(tmp->key, "HOME"))
                chdir(tmp->value);
            tmp = tmp->next;
        }
    }
    else
    {
        tmp = env;
        while(tmp)
        {
            if (cmd->cmd[1])
                chdir(cmd->cmd[1]);
            tmp = tmp->next;
        }
    }
}