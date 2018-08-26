/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afesyk <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/19 19:04:54 by afesyk            #+#    #+#             */
/*   Updated: 2018/03/19 19:06:00 by afesyk           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	auto_zoom(t_pack *p)
{
	int	w_zoom;
	int	h_zoom;

	w_zoom = (WIDTH - 600) / p->width;
	h_zoom = (HEIGHT - 400) / p->height;
	if (w_zoom < h_zoom)
		p->zoom = w_zoom;
	else
		p->zoom = h_zoom;
}

int		valid_matrix(t_list *line, t_pack *p)
{
	t_list	*tmp;
	int		num_of_dots;

	tmp = line;
	num_of_dots = word_cnt(tmp->content);
	tmp = tmp->next;
	while (tmp->next)
	{
		if (word_cnt(tmp->content) != num_of_dots)
		{
			free_lst(&line);
			free(p);
			return (0);
		}
		tmp = tmp->next;
	}
	p->width = word_cnt(line->content);
	p->height = ft_lstsize(line) - 1;
	auto_zoom(p);
	return (1);
}

int		valid_format(char *dot)
{
	int	n;

	n = 0;
	while (*dot != ',' && *dot != '\0')
	{
		if ((*dot < '0' || *dot > '9') && *dot != '-')
			return (0);
		dot++;
	}
	if (*dot == ',')
	{
		if (*(++dot) != '0')
			return (0);
		if (*(++dot) != 'x')
			return (0);
		while (*(++dot) && ++n)
			if (*dot < '0' || (*dot > '9' && *dot < 'A') ||
				(*dot > 'F' && *dot < 'a') || *dot > 'f' ||
				n < 1 || n > 6)
				return (0);
	}
	if (*dot == '\0' || !n)
		return (1);
	return (0);
}

int		hex_to_dec(char *s)
{
	int res;

	res = 0;
	if (*s >= '0' && *s <= '9')
		res += *s - '0';
	else if (*s >= 'A' && *s <= 'F')
		res += *s - 'A' + 10;
	else if (*s >= 'a' && *s <= 'f')
		res += *s - 'a' + 10;
	else
		res += 0;
	if (*(--s) == ',')
		return (res);
	if (*s >= '0' && *s <= '9')
		res += (*s - '0') * 16;
	else if (*s >= 'A' && *s <= 'F')
		res += (*s - 'A' + 10) * 16;
	else if (*s >= 'a' && *s <= 'f')
		res += (*s - 'a' + 10) * 16;
	else
		res += 0;
	return (res);
}

int		get_color(char *dot)
{
	char	*tmp;
	int		r;
	int		g;
	int		b;

	if (!(tmp = ft_strchr(dot, ',')))
		return (0);
	while (*tmp)
		tmp++;
	b = hex_to_dec(tmp - 1);
	if (b < 16 && *(tmp - 3) == ',')
		return (b);
	g = hex_to_dec(tmp - 3);
	if (g < 16 && *(tmp - 5) == ',')
		return (g << 8 | b);
	r = hex_to_dec(tmp - 5);
	return (r << 16 | g << 8 | b);
}
