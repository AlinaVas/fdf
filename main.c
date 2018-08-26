/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afesyk <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/19 18:38:21 by afesyk            #+#    #+#             */
/*   Updated: 2018/03/19 18:46:38 by afesyk           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	fill_pack(t_pack *p)
{
	p->zoom_by = 2;
	p->x_angle = 0;
	p->y_angle = 0;
	p->z_angle = 0;
	p->rotate_by = 0.08;
	p->color_mode = 0;
	p->x_shift = 0;
	p->y_shift = 0;
	p->z_shift = 1;
}

void	deal_key2(int key, t_pack *p)
{
	if (key == 53)
	{
		ft_putstr("Good bye!\n");
		mlx_destroy_window(p->mlx, p->win);
		free_everything(p);
		exit(0);
	}
	if (key == 84)
		p->x_angle -= p->rotate_by;
	if (key == 91)
		p->x_angle += p->rotate_by;
	if (key == 86)
		p->y_angle -= p->rotate_by;
	if (key == 88)
		p->y_angle += p->rotate_by;
	if (key == 87)
		fill_pack(p);
	if (key == 46)
		system("afplay 1.mp3 &");
}

int		deal_key(int key, t_pack *p)
{
	deal_key2(key, p);
	if (key == 125)
		p->y_shift += 5;
	if (key == 126)
		p->y_shift -= 5;
	if (key == 123)
		p->x_shift -= 5;
	if (key == 124)
		p->x_shift += 5;
	if (key == 89)
		p->z_shift += 0.1;
	if (key == 83)
		p->z_shift -= 0.1;
	if (key == 35)
		p->color_mode = 1;
	if (key == 13)
		p->color_mode = 0;
	if (key == 69)
		p->zoom += p->zoom_by;
	if (key == 78)
		(p->zoom > 1) ? p->zoom -= p->zoom_by : 0;
	mlx_clear_window(p->mlx, p->win);
	print_map(p);
	return (0);
}

void	set_legend(t_pack *p)
{
	mlx_string_put(p->mlx, p->win, 20, 20, 0xFF00CC,
			"Press ESC to quit");
	mlx_string_put(p->mlx, p->win, 20, 80, 0xFFDDDD,
			"Use arrows to shift an image");
	mlx_string_put(p->mlx, p->win, 20, 120, 0xFFDDDD,
			"1 and 7       change altitude");
	mlx_string_put(p->mlx, p->win, 20, 100, 0xFFDDDD,
			"2, 4, 6, 8    rotate");
	mlx_string_put(p->mlx, p->win, 20, 140, 0xFFDDDD,
			"W / P         color mode");
	mlx_string_put(p->mlx, p->win, 20, 160, 0xFFDDDD,
			"5             reset settings");
	mlx_string_put(p->mlx, p->win, 20, 180, 0xFFDDDD,
			"+, -          zoom in / out");
	mlx_string_put(p->mlx, p->win, 20, 220, 0xFFDDDD,
			"M             is for MAGIC");
}

int		main(int ac, char **av)
{
	t_pack	*p;

	if (ac != 2)
		error_exit(1);
	p = open_file(av[1]);
	fill_pack(p);
	if (!(p->mlx = mlx_init()))
		error_exit(0);
	if (!(p->win = mlx_new_window(p->mlx, WIDTH, HEIGHT, av[1])))
		error_exit(0);
	print_map(p);
	mlx_hook(p->win, 2, 5, deal_key, p);
	mlx_loop(p->mlx);
	return (0);
}
