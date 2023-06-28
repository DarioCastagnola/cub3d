/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcastagn <dcastagn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 11:39:41 by dcastagn          #+#    #+#             */
/*   Updated: 2023/06/28 12:13:13 by dcastagn         ###   ########.fr       */
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

// ---------- TILES

typedef struct s_game
{
	void			*mlx;
	void			*mlx_win;
}		t_game;

#endif