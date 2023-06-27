/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojamal <ojamal@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 01:15:54 by ymenyoub          #+#    #+#             */
/*   Updated: 2023/06/27 06:35:19 by ojamal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	pwd_cmd(t_env_node *env)
{
	char *tmp;
	tmp = getcwd(0, 0);
	if (!tmp)
		printf("%s\n", get_env_val(env, "PWD"));
	else
		printf("%s\n", tmp);
	free(tmp);
}
