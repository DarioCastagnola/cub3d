/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcastagn <dcastagn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 11:39:41 by dcastagn          #+#    #+#             */
/*   Updated: 2023/07/31 16:37:41 by dcastagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <stdint.h>
# include "minilibx-linux/mlx.h"
# include "libft/libft.h"
# include "gnl/get_next_line.h"
# include <fcntl.h>
# include <math.h>
# include <time.h>
# include <sys/time.h>

// risoluzione
#define SCREEN_W 1920
#define SCREEN_H 1080
#define TEXTURES 1

// Field Of View
#define FOV 0.66

// Pi
#define PI 3.14159

// passo di movimento e rotazione
#define MOVSPEED 0.1
#define ROTSPEED 0.05

// Dimensioni della minimappa

#define MINIMAP_SCALE (int)(SCREEN_W / 150)
# define RGB_RED 0x00FFA0A0
# define RGB_GREEN 0x0000FF00
# define RGB_BLUE 0x000000FF
# define RGB_YELLOW 0x00FFFF00
# define RGB_WHITE 0x00FFFFFF
# define RGB_DARK_GREY 0x00282828
# define RGB_FLOOR 0x00228B22
# define RGB_SKY 0x00E0FFFF

// ---------- STRUCTS

typedef struct s_vectors
{
	double	x;
	double	y;
}	t_vectors;

typedef struct s_data 
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	double	dx;
	double	dy;
	double	px;
	double	py;
	int		pixels;
}	t_data;

typedef struct s_mini 
{
	int		width;
	int		height;
	int		y;
	int		x;
	t_data	data;
}	t_mini;

typedef struct s_img
{
	void	*img;
	void	*addr;
	int		width;
	int		height;
	int		bpp;
	int		ll;
	int		endian;

}	t_img;

typedef struct s_player
{
	t_vectors	pos;
	t_vectors	dir;
	t_vectors	mov_dir;
	t_vectors	plane;
	t_vectors	mov_speed;
	double		rot_speed;
	double		rot_dir;
}	t_player;

typedef struct s_ray
{
	t_vectors	draw_start;
	t_vectors	draw_end;
	t_vectors	side_dist;
	t_vectors	delta_dist;
	t_vectors	ray_dir;
	double		perp_wall_dist;
	double		camera_x;
	int			side;
	int			hit;
	int			line_height;
	int			step_x;
	int			step_y;
	int			map_x;
	int			map_y;
	int			color;
}	t_ray;

//PARSER

typedef struct parser
{
	char	**readmap;
	char	**map;
	int		inimap;
	int		inidata;
	int		x;
	int		y;
	int		mwidth;
	int		mheight;
	int		f[3];
	int		c[3];

}		t_parser;

//GAME

typedef struct s_game
{

	void			*mlx;
	void			*mlx_win;
	double			frame_time;
	int				fps;
	int				x;
	u_int64_t		time;
	u_int64_t		old_time;
	t_player		player;
	t_ray			ray;
	t_data			data;
	t_parser		parser;
	t_img			walls[4];
	int				mouse_x;
	int				mouse_y;
	int				screen_x;
	int				screen_y;
	t_data			screen;
	t_mini			mini;
}	t_game;


//TEMP PARSER

char	**ft_readmap(t_parser *parser, char *path);
void	ft_map(t_parser *parser);
void	ft_print_mat(char **mat);
void	ft_free_mat(char **mat);
void	ft_free_err(t_parser *parser, char *s);
void	ft_inimap(t_parser *parser);
void	ft_inidata(t_parser *parser);
void	ft_size_map(t_parser *parser);
void	ft_check_texture(t_parser *parser, t_game *game);
void	ft_check_size(t_parser *parser, char *path);
void	ft_check_fc(t_parser *parser);
void	ft_check_map(t_parser *parser);
void	ft_check_lmap(t_parser *parser);
void	ft_check_symbol_map(t_parser *parser);
void	ft_check_rgb(int y, t_parser *parser);
void	ft_load_image(t_game *game, char **temp);

//TEMP RAYCASTING

void		ft_sleep(u_int64_t time);
int			start_game(t_game *game);
void	my_mlx_pixel_put(t_data *img, int x, int y, int color);
void	draw_minimap(t_game	*game);
void		init_game(t_game *game);
u_int64_t	get_time(void);
int			player_initialization(t_game *game);
void		update_inputs(t_game *game);
void		*null_error(char *message);
int			key_hook_press(int key, t_game *game);
int			key_hook_release(int key, t_game *game);
void		raycaster(t_game *game);
void		draw_texture(t_game *game, int x);
int			draw_frames(t_game *game);
void		draw_line_on(t_data *img, t_vectors begin, t_vectors end, int color);
void		draw_background(t_data *img, t_vectors begin, t_vectors end);
int	ft_mouse(int x, int y, void *param);

#endif
