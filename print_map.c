/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afesyk <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/19 19:09:46 by afesyk            #+#    #+#             */
/*   Updated: 2018/03/19 19:10:15 by afesyk           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	plot_line_low(t_dot a, t_dot b, t_pack *p)
{
	int	x;
	int	y;

	x = a.x + p->x_offset;
	y = a.y + p->y_offset;
	p->dx = b.x - a.x;
	p->dy = b.y - a.y;
	p->yi = 1;
	if (p->dy < 0 && (p->yi = -1))
		p->dy = -(p->dy);
	p->d = 2 * p->dy - p->dx;
	p->xi = 0;
	p->color_change = (b.x - a.x) ? ((b.color - a.color) / (b.x - a.x)) : 0;
	while (a.x + ++p->xi < b.x)
	{
		mlx_pixel_put(p->mlx, p->win, x + p->xi, y, a.color);
		if (p->d > 0)
		{
			y += p->yi;
			p->d -= 2 * p->dx;
		}
		p->d += 2 * p->dy;
		a.color += p->color_change;
	}
}

void	plot_line_high(t_dot a, t_dot b, t_pack *p)
{
	int	x;
	int	y;

	x = a.x + p->x_offset;
	y = a.y + p->y_offset;
	p->dx = b.x - a.x;
	p->dy = b.y - a.y;
	p->xi = 1;
	if (p->dx < 0 && (p->xi = -1))
		p->dx = -(p->dx);
	p->d = 2 * p->dx - p->dy;
	p->yi = 0;
	p->color_change = (b.y - a.y) ? ((b.color - a.color) / (b.y - a.y)) : 0;
	while (a.y + ++p->yi < b.y)
	{
		mlx_pixel_put(p->mlx, p->win, x, y + p->yi, a.color);
		if (p->d > 0)
		{
			x += p->xi;
			p->d -= 2 * p->dy;
		}
		p->d += 2 * p->dx;
		a.color += p->color_change;
	}
}

void	plot_line(t_dot a, t_dot b, t_pack *p)
{
	if (ft_abs(b.y - a.y) < ft_abs(b.x - a.x))
	{
		if (a.x > b.x)
			plot_line_low(b, a, p);
		else
			plot_line_low(a, b, p);
	}
	else
	{
		if (a.y > b.y)
			plot_line_high(b, a, p);
		else
			plot_line_high(a, b, p);
	}
}

void	draw_map(t_pack *p)
{
	int	x;
	int	y;

	y = -1;
	while (++y < p->height)
	{
		x = -1;
		while (++x < p->width)
		{
			if (x == p->width - 1 && y == p->height - 1)
				return ;
			if (x < p->width - 1)
				plot_line(p->res[x + y * p->width],
				p->res[(x + 1) + y * p->width], p);
			if (y < p->height - 1)
				plot_line(p->res[x + y * p->width],
				p->res[(x + p->width) + y * p->width], p);
		}
	}
}

void	print_map(t_pack *p)
{
	int	i;

	p->x_offset = (WIDTH / 2) + p->x_shift + 200;
	p->y_offset = (HEIGHT / 2) + p->y_shift;
	rotate_map(p);
	(p->color_mode) ? paint_map(p) : wipe_map(p);
	i = -1;
	while (++i < p->height * p->width)
		mlx_pixel_put(p->mlx, p->win, p->res[i].x + p->x_offset,
		p->res[i].y + p->y_offset, p->res[i].color);
	draw_map(p);
	set_legend(p);
}
