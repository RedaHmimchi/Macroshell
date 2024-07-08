/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhmimchi <rhmimchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 18:28:12 by rhmimchi          #+#    #+#             */
/*   Updated: 2024/07/06 07:23:02 by rhmimchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "macroshell.h"

void ft_chdir(t_data *data)
{
	if (data->args[1] == NULL || ft_strcmp(data->args[1], "~") == 0)
	{
		data->args[1] = getenv("HOME");
        if (data->args[1] == NULL)
        {
            ft_putstr_fd("macroshell: cd: HOME not set\n", 2);
            return;
        }
		if (chdir(data->args[1]) != 0)
			perror("macroshell : cd");
	}
	else if (chdir(data->args[1]) != 0)
	{
        perror("macroshell : cd");
	}
}

void ft_pwd()
{
	char cwd[1024];
	if (getcwd(cwd, sizeof(cwd)) != NULL)
	{
		ft_putstr_fd(cwd, 1);
		ft_putstr_fd("\n", 1);
	}
	else
		perror("minihsell");
	return;
}

void ft_echo(t_data *data)
{
    int i = 1;
    while (data->args[i] != NULL)
    {
        ft_putstr_fd(data->args[i], 1);
        if (data->args[i + 1] != NULL)
            ft_putstr_fd(" ", 1);
        i++;
    }
    ft_putstr_fd("\n", 1);
}

