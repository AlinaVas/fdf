/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afesyk <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/19 19:02:28 by afesyk            #+#    #+#             */
/*   Updated: 2018/03/19 19:02:41 by afesyk           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	fill_dot(t_pack *p, int x, int y, char *array)
{
	p->map[x + y * p->width].x = x - p->width / 2;
	p->map[x + y * p->width].y = y - p->height / 2;
	p->map[x + y * p->width].z = ft_atoi(array);
	p->map[x + y * p->width].color = get_color(array);
}

int		save_map(t_list *lst, t_pack *p)
{
	int		x;
	int		y;
	char	**array;

	y = -1;
	while (++y < p->height)
	{
		x = -1;
		array = ft_strsplit(lst->content, ' ');
		while (++x < p->width)
		{
			if (!valid_format(array[x]))
			{
				free_array(array);
				ft_memdel((void**)&p->map);
				error_exit(6);
				return (0);
			}
			fill_dot(p, x, y, array[x]);
		}
		free_array(array);
		lst = lst->next;
	}
	return (1);
}

t_list	*read_file(int fd, t_pack *p)
{
	t_list	*line;
	int		ret;

	if (!(p->head = ft_lstnew(NULL, 0)))
		return (NULL);
	line = p->head;
	while ((ret = get_next_line(fd, (char**)&line->content)) &&
		(line->content_size = 1))
	{
		if (ret == -1)
		{
			free_lst(&p->head);
			return (NULL);
		}
		if (!(line->next = ft_lstnew(NULL, 0)))
			return (NULL);
		line = line->next;
	}
	if (!ret && !p->head->content_size)
	{
		free_lst(&p->head);
		return (NULL);
	}
	return (p->head);
}

void	create_map(t_pack *p)
{
	p->map = (t_dot*)malloc(sizeof(t_dot) * (p->width * p->height));
	if (!p->map)
		error_exit(3);
	p->res = (t_dot*)malloc(sizeof(t_dot) * (p->width * p->height));
	if (!p->res)
		error_exit(3);
}

t_pack	*open_file(char *filename)
{
	int		fd;
	t_pack	*p;

	if ((fd = open(filename, O_RDONLY)) < 0)
		error_exit(2);
	p = create_pack();
	if (!(p->head = read_file(fd, p)))
		error_exit(4);
	if (!valid_matrix(p->head, p))
		error_exit(5);
	create_map(p);
	if (!(save_map(p->head, p)))
	{
		free_lst(&p->head);
		exit(-1);
	}
	free_lst(&p->head);
	close(fd);
	return (p);
}
