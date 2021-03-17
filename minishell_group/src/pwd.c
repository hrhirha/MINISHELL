/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ler-rech <ler-rech@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/12 10:12:11 by ler-rech          #+#    #+#             */
/*   Updated: 2021/03/17 17:37:12 by ler-rech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	shell_pwd(t_minishell *minishell)
{
	int i;
	char *pwd;

	pwd = getcwd(NULL, 0);
	if (!pwd)
	{
		ft_putstr_fd("minishell: cd: error retrieving current directory: getcwd: cannot access parent directories: ", 2);
		ft_putendl_fd(strerror(errno), 2);
		g_exist.last_exec = 1;
	}
	ft_putstr_fd(pwd, 1);
	ft_putstr_fd("\n", 1);
	g_exist.last_exec = 0;
	return (1);
}
