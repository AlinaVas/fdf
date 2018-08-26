/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afesyk <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/19 19:10:42 by afesyk            #+#    #+#             */
/*   Updated: 2018/03/19 19:11:31 by afesyk           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_pack	*create_pack(void)
{
	t_pack	*p;

	if (!(p = (t_pack*)malloc(sizeof(t_pack))))
		error_exit(3);
	p->map = NULL;
	p->res = NULL;
	p->head = NULL;
	return (p);
}

void	free_lst(t_list **head)
{
	t_list	*tmp;
	t_list	*curr;

	curr = *head;
	while (curr)
	{
		tmp = curr;
		curr = curr->next;
		if (tmp->content)
			free(tmp->content);
		free(tmp);
	}
}

void	free_array(char **array)
{
	int i;

	i = -1;
	while (array[++i] != NULL)
		free(array[i]);
	free(array);
	array = NULL;
}

void	free_everything(t_pack *p)
{
	ft_memdel((void**)&p->map);
	ft_memdel((void**)&p->res);
	ft_memdel((void**)&p);
}

void	error_exit(int n)
{
	if (n == 0)
		ft_putstr_fd("MLX error\n", 2);
	if (n == 1)
		ft_putstr_fd("usage: ./fdf [filename]\n", 2);
	if (n == 2)
		ft_putstr_fd("Cannot open the indicated file\nusage: ./fdf [filename] \
			\n", 2);
	if (n == 3)
		ft_putstr_fd("Memory allocation failed. Try again, pleeeease!\n", 2);
	if (n == 4)
		ft_putstr_fd("Error while reading the file\n", 2);
	if (n == 5)
		ft_putstr_fd("Map has invalid format\n", 2);
	if (n == 6)
		ft_putstr_fd("Invalid format of specified coordinates\n", 2);
	if (n != 6)
		exit(-1);
}
