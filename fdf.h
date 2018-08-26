/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afesyk <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/19 12:56:08 by afesyk            #+#    #+#             */
/*   Updated: 2018/03/19 12:57:30 by afesyk           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <mlx.h>
# include <math.h>
# include <fcntl.h>
# include "libft/libft.h"

# define WIDTH 1500
# define HEIGHT 800

typedef struct	s_dot
{
	int			x;
	int			y;
	int			z;
	int			color;
}				t_dot;

typedef struct	s_pack
{
	void		*mlx;
	void		*win;
	int			width;
	int			height;
	int			zoom;
	int			zoom_by;
	int			x_offset;
	int			y_offset;
	int			x_shift;
	int			y_shift;
	double		z_shift;
	int			dx;
	int			dy;
	int			xi;
	int			yi;
	int			d;
	t_dot		*map;
	t_dot		*res;
	t_list		*head;
	int			line_color;
	int			color_change;
	int			color_mode;
	double		x_angle;
	double		y_angle;
	double		z_angle;
	double		rotate_by;

}				t_pack;

void			free_lst(t_list **head);
void			free_array(char **array);
void			free_everything(t_pack *p);
void			paint_map(t_pack *p);
void			wipe_map(t_pack *p);
int				deal_key(int key, t_pack *p);
void			deal_key2(int key, t_pack *p);
void			rotate_map(t_pack *p);
void			ft_rotate(t_pack *p, int x, int y);
t_pack			*open_file(char *filename);
t_list			*read_file(int fd, t_pack *p);
int				save_map(t_list *lst, t_pack *p);
void			fill_dot(t_pack *p, int x, int y, char *array);
int				valid_format(char *dot);
int				valid_matrix(t_list *line, t_pack *p);
int				get_color(char *dot);
int				hex_to_dec(char *s);
void			print_map(t_pack *p);
void			draw_map(t_pack *p);
void			plot_line(t_dot a, t_dot b, t_pack *p);
void			plot_line_high(t_dot a, t_dot b, t_pack *p);
void			plot_line_low(t_dot a, t_dot b, t_pack *p);
void			set_legend(t_pack *p);
void			fill_pack(t_pack *p);
void			create_map(t_pack *p);
void			auto_zoom(t_pack *p);
void			error_exit(int n);
t_pack			*create_pack(void);

#endif
