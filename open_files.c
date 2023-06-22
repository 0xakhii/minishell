/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_files.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojamal <ojamal@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 07:49:12 by ojamal            #+#    #+#             */
/*   Updated: 2023/06/22 10:54:33 by ojamal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// int	open_files(t_cmd *cmd)
// {
// 	int fd;
// 	t_cmd *tmp = NULL;
// 	if (cmd)
// 		tmp = cmd;
// 	while (tmp)
// 	{
// 		if (tmp->e_types == T_IN_FILE)
// 		{
// 			if (tmp->in_file)
// 				fd = open(tmp->in_file, O_RDONLY, 0644);
// 		}
// 		else if (tmp->e_types == T_OUT_FILE)
// 		{
// 			if (tmp->out_file)
// 				fd = open(tmp->out_file, O_CREAT | O_WRONLY, 0644);
// 		}
// 		else if (tmp->e_types == T_APP_FILE)
// 		{
// 			if (tmp->in_file)
// 				fd = open(tmp->in_file, O_RDWR | O_APPEND, 0644);
// 		}
// 		tmp = tmp->next;
// 	}
// 	if (fd == -1)
// 	{
// 		msg_er("No such file or directory");
// 		return (-1);
// 	}
// 	return (fd);
// }