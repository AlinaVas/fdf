/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_modificator.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afesyk <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/19 19:14:09 by afesyk            #+#    #+#             */
/*   Updated: 2018/03/19 19:14:35 by afesyk           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	ft_rotate(t_pack *p, int x, int y)
{
	int	i;
	int x_zoomed;
	int y_zoomed;
	int z_zoomed;

	i = x + y * p->width;
	x_zoomed = p->map[i].x * p->zoom;
	y_zoomed = p->map[i].y * p->zoom;
	z_zoomed = p->map[i].z * p->zoom * p->z_shift;
	p->res[i].y = y_zoomed * cos(p->x_angle) - z_zoomed * sin(p->x_angle);
	p->res[i].z = y_zoomed * sin(p->x_angle) + z_zoomed * cos(p->x_angle);
	p->res[i].x = x_zoomed * cos(p->y_angle) + p->res[i].z * sin(p->y_angle);
	p->res[i].z = -x_zoomed * sin(p->y_angle) + p->res[i].z * cos(p->y_angle);
}

void	rotate_map(t_pack *p)
{
	int	x;
	int	y;

	y = -1;
	while (++y < p->height)
	{
		x = -1;
		while (++x < p->width)
			ft_rotate(p, x, y);
	}
}

void	paint_map(t_pack *p)
{
	int	min_z;
	int	max_z;
	int	i;
	int	step;

	i = 0;
	max_z = p->map[i].z;
	min_z = p->map[i].z;
	while (++i < p->width * p->height)
	{
		if (max_z < p->map[i].z)
			max_z = p->map[i].z;
		if (min_z > p->map[i].z)
			min_z = p->map[i].z;
	}
	if (min_z == max_z)
		step = 0;
	else
		step = (0xFFFFCC - 0xFF00CC) / (max_z - min_z);
	i = -1;
	while (++i < p->width * p->height)
		p->res[i].color = 0xFFFFCC - p->map[i].z * step;
}

void	wipe_map(t_pack *p)
{
	int	i;

	i = -1;
	while (++i < p->width * p->height)
	{
		if (p->map[i].color == 0)
			p->res[i].color = 0xFFFFFF;
		else
			p->res[i].color = p->map[i].color;
	}
}
