/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcastagn <dcastagn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 16:34:39 by dcastagn          #+#    #+#             */
/*   Updated: 2023/07/06 16:40:28 by dcastagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// void	draw_line_on(t_data *img, t_vector begin, t_vector end, int color)
// {
// 	double	dx;
// 	double	dy;
// 	double	px;
// 	double	py;
// 	int		pixels;

// 	dx = end.x - begin.x;
// 	dy = end.y - begin.y;
// 	pixels = sqrt((dx * dx) + (dy * dy)) + 1;
// 	dx /= pixels;
// 	dy /= pixels;
// 	px = begin.x;
// 	py = begin.y;
// 	while (pixels)
// 	{
// 		my_mlx_pixel_put(img, (int)px, (int)py, color);
// 		px += dx;
// 		py += dy;
// 		--pixels;
// 	}
// }