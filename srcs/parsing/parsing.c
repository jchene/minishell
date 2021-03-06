/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchene <jchene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 09:34:26 by anguinau          #+#    #+#             */
/*   Updated: 2022/06/22 15:04:44 by jchene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/header.h"

int	fill_p_struct_str(void)
{
	(data())->p_index->str = ft_strndup((data())->line,
			(data())->j - (data())->i, (data())->i);
	if (!(data())->p_index->str)
		return (0);
	return (1);
}

int	free_p_struct(void)
{
	t_parsing	*temp;

	(data())->p_index = (data())->p_start;
	while ((data())->p_index)
	{
		temp = (data())->p_index;
		(data())->p_index = (data())->p_index->next;
		free(temp->str);
		free(temp);
	}
	(data())->p_start = NULL;
	return (1);
}

int	new_p_struct_member(void)
{
	if (!(data())->p_start)
	{
		(data())->p_start = malloc(sizeof(t_parsing));
		if (!((data())->p_start))
			return (0);
		(data())->p_start->prev = NULL;
		(data())->p_start->next = NULL;
		(data())->p_index = (data())->p_start;
	}
	else
	{
		(data())->p_index = (data())->p_start;
		while ((data())->p_index->next)
			(data())->p_index = (data())->p_index->next;
		(data())->p_index->next = malloc(sizeof(t_parsing));
		if (!((data())->p_index->next))
			return (0);
		(data())->p_index->next->prev = (data())->p_index;
		(data())->p_index->next->next = NULL;
		(data())->p_index = (data())->p_index->next;
	}
	return (1);
}

int	read_input(void)
{
	(data())->line = readline("$ ");
	if (!(data())->line)
	{
		ft_putstr_fd("exit\n", 1);
		(data())->stop = 1;
	}
	if ((data())->line && (data())->line[0])
	{
		add_history((data())->line);
		if (!(data())->h_start)
		{
			if (!init_history((data())->line))
				return (0);
		}
		else if (!add_in_history((data())->line))
			return (0);
	}
	return (1);
}
