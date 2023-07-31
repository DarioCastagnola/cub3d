/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcastagn <dcastagn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 15:15:09 by dcastagn          #+#    #+#             */
/*   Updated: 2023/07/31 12:47:51 by dcastagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

// Calcola la coordinata X della texture in base al punto di impatto sulla parete
// dell'intersezione del raggio con la griglia del mondo di gioco.
// Se il lato del raggio è 0 (orizzontale), calcola wall_x basandosi sulla posizione Y del giocatore
// e la distanza perpendicolare alla parete.
// Altrimenti, il lato del raggio è 1 (verticale), calcola wall_x basandosi sulla posizione X del giocatore
// e la distanza perpendicolare alla parete.
// Normalizza wall_x sottraendo la parte intera, mantenendo solo la parte frazionaria.
// Calcola tex_x moltiplicando la parte frazionaria di wall_x per il numero di pixel in una texture.
// Ciò determina quale pixel della texture sarà selezionato in base alla parte frazionaria della coordinata X.
// Se il lato del raggio è 0 (orizzontale) e il raggio sta andando verso destra (direzione X positiva),
// l'immagine della texture verrà riflessa lungo l'asse verticale.
// Se il lato del raggio è 1 (verticale) e il raggio sta andando verso l'alto (direzione Y negativa),
// l'immagine della texture verrà riflessa lungo l'asse verticale.
// Restituisce l'indice del pixel nella texture da utilizzare per il rendering della colonna corrente.

int	get_texture_x(t_game *game)
{
	double	wall_x;
	int		tex_x;

	if (game->ray.side == 0)
		wall_x = game->player.pos.y + game->ray.perp_wall_dist
			* game->ray.ray_dir.y;
	else
		wall_x = game->player.pos.x + game->ray.perp_wall_dist
			* game->ray.ray_dir.x;
	wall_x -= (int)(wall_x);
	tex_x = (int)(wall_x * (double)(game->walls[game->ray.color].width));
	if (game->ray.side == 0 && game->ray.ray_dir.x > 0)
		tex_x = game->walls[game->ray.color].width - tex_x - 1;
	if (game->ray.side == 1 && game->ray.ray_dir.y < 0)
		tex_x = game->walls[game->ray.color].width - tex_x - 1;
	return (tex_x);
}

void    render_texture(t_game *game, int x)
{
    double          step;
    double          texPos;
    int             y;
    t_vectors       tex;
    unsigned int    color;

    tex.x = get_texture_x(game);
    step = 1.0 * game->walls[game->ray.color].width / game->ray.line_height;
    texPos = (game->ray.draw_start.y - SCREEN_H / 2 + game->ray.line_height / 2) * step;
    y = game->ray.draw_start.y - 1;
	draw_background(&game->data, game->ray.draw_start, game->ray.draw_end);
    while (++y < game->ray.draw_end.y)
    {
        // Cast the texture coordinate to integer, and mask with (texHeight - 1) in case of overflow
        tex.y = (int)texPos & (game->walls[game->ray.color].width - 1);
        texPos += step;
        color = *(unsigned int *)(game->walls[game->ray.color].addr
				+ 4 * (game->walls[game->ray.color].width * (int)tex.y + (int)tex.x));
		my_mlx_pixel_put(&game->data, x, y, color);
    }
}

void	select_texture(t_game *game)
{
	if (game->ray.side == 1 && game->player.pos.y <= game->ray.map_y)
		game->ray.color = 0;
	else if (game->ray.side == 1)
		game->ray.color = 1;
	else if (game->ray.side == 0 && game->player.pos.x <= game->ray.map_x)
		game->ray.color = 2;
	else if (game->ray.side == 0)
		game->ray.color = 3;
	else
		game->ray.color = 0;
}

void	draw_texture(t_game *game, int x)
{
	int	colors[4];

	select_texture(game);
	if (TEXTURES)
		render_texture(game, x);
	else
	{
		colors[0] = RGB_BLUE;
		colors[1] = RGB_GREEN;
		colors[2] = RGB_RED;
		colors[3] = RGB_YELLOW;
		draw_line_on(&game->data, game->ray.draw_start,
		game->ray.draw_end, colors[game->ray.color]);
	}
}