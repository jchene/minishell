/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anguinau <constantasg@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 10:27:26 by anguinau          #+#    #+#             */
/*   Updated: 2022/02/04 10:27:26 by anguinau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/header.h"

int	free_exec(int ret)
{
	if ((data())->exec_struc)
	{
		free((data())->exec_struc->infiles);
		(data())->exec_struc->infiles = NULL;
		free((data())->exec_struc->outfiles);
		(data())->exec_struc->outfiles = NULL;
		free((data())->exec_struc->to_close);
		(data())->exec_struc->to_close = NULL;
		free((data())->exec_struc->path);
		(data())->exec_struc->path = NULL;
		free_ptabn((void **)(data())->exec_struc->args);
		free((data())->exec_struc);
		(data())->exec_struc = NULL;
	}
	(data())->nb_inf = 0;
	(data())->nb_ouf = 0;
	(data())->nb_cls = 0;
	return (ret);
}

int	init_data(char **envp)
{
	data();
	(data())->stop = 0;
	(data())->exit_code = 0;
	(data())->exit_calls = 0;
	(data())->line = NULL;
	(data())->envp = NULL;
	(data())->envp_size = 0;
	if (envp)
	{
		(data())->envp = cp_str_tab2(envp);
		if (!(data())->envp)
			return (0);
		(data())->i = -1;
		while ((data())->envp[++(data())->i])
			continue ;
		(data())->envp_size = (data())->i;
	}
	(data())->h_start = NULL;
	(data())->p_start = NULL;
	(data())->exp_start = NULL;
	(data())->exp_end = NULL;
	(data())->he_start = NULL;
	return (1);
}

int	new_prompt(void)
{
	if ((data())->p_start)
		free_p_struct();
	if (!read_input())
		return (0);
	if (!split_line())
		return (0);
	if (!rm_dollars())
		return (0);
	if (!flag_words())
		return (1);
	if (!rm_quotes())
		return (0);
	if (!start_exec((data()->envp)))
		return (0);
	wait_all();
	if ((data())->child_ids)
	{
		free((data())->child_ids);
		(data())->child_ids = NULL;
	}
	if ((data())->exit_calls > 1)
		(data())->exit_code = 0;
	if ((data())->exit_calls == 1)
		(data())->stop = 1;
	(data())->exit_calls = 0;
	if ((data())->he_start)
	{
		clear_all_heredocs((data())->he_start);
		(data())->he_start = NULL;
	}
	return (1);
}

int	main(int ac, char **av, char **envp)
{
	(void)ac;
	(void)av;
	ft_signal();
	if (!init_data(envp))
		return (exit_properly(-1));
	if (!create_exp_struct())
		return (-1);
	while (!(data())->stop)
		if (!new_prompt())
			return (exit_properly(-1));
	return (exit_properly((data())->exit_code));
}