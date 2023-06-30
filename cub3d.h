/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcastagn <dcastagn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 11:39:41 by dcastagn          #+#    #+#             */
/*   Updated: 2023/06/30 15:37:05 by dcastagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include "minilibx-linux/mlx.h"
# include "libft/libft.h"
# include "errors/errors.h"
# include "gnl/gnl.h"
# include <fcntl.h>
# include <math.h>
# include <time.h>

// risoluzione
#define SCREEN_W 640
#define SCREEN_H 480

// Field Of View
#define FOV 0.66

// Pi
#define PI 3.14159

// passo di movimento e rotazione
#define MOVSPEED 0.1
#define ROTSPEED 0.05

// ---------- STRUCTS

// framebuffer
typedef struct s_frame
{
    uint32_t width;
    uint32_t height;
    //TrueColorPixel *data;
}	t_frame;

// mappa
typedef struct s_map
{
	char		**map;
	t_vectors	player_pos;
}	t_map;

typedef struct s_vectors
{
	double	x;
	double	y;
}	t_vectors;

// informazioni sul raggio
typedef struct s_rayHit
{
    double distance;
    int mapX;
    int mapY;
    double rayDirX;
    double rayDirY;
    int side;
}	t_rayHit;

typedef struct s_game
{
	void			*mlx;
	void			*mlx_win;
}	t_game;

#endif