/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrosamon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/02 12:13:36 by jrosamon          #+#    #+#             */
/*   Updated: 2016/03/05 17:30:23 by jrosamon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef WOLF_H
# define WOLF_H

# include <math.h>
# include <stdlib.h>
# include <unistd.h>
# include "mlx.h"
# include "libft.h"
# include "stdio.h"
# include "time.h"

# define WIN_WIDTH 640
# define WIN_HEIGHT 480

# define map_width 24
# define map_height 24

# define texture_width 64
# define texture_height 64

# define KEYCODE_EXIT 53

# define PPOSX e->p->pos->x
# define PPOSY e->p->pos->y
# define PDIRX e->p->dir->x
# define PDIRY e->p->dir->y
# define PPLANEX e->p->plane->x
# define PPLANEY e->p->plane->y
# define PROTS e->p->rt_speed
# define PMOVS e->p->mv_speed

# define BLUE 0x0000cc
# define GREEN 0x00cc00
# define BROWN 0xcc660
# define GREY 0x999999
# define FUSHIA 0xcc00cc
# define YELLOW 0xcccc00
# define WHITE 0xffffff
# define RED 0xff0000


extern int	worldMap[map_width][map_height];
extern int	worldMap2[map_width][map_height];

typedef struct s_vertex
{
	double		x;
	double		y;
}				t_vertex;

typedef struct	s_player
{
	t_vertex	*pos;
	t_vertex	*dir;
	t_vertex	*plane;
	double		mv_speed;
	double		rt_speed;
}				t_player;

typedef struct	s_color
{
	int			r;
	int			g;
	int			b;
}				t_color;

typedef struct	s_img
{
	void		*data;
	int			bpp;
	int			sizeline;
	int			bits;
	int			iendian;
}				t_img;

typedef	struct	s_raycast
{
	int			x;
	double		cameraX;
	double		rayPosX;
	double		rayPosY;
	double		rayDirX;
	double		rayDirY;
	int			mapX;
	int			mapY;
	double		sideDistX;
	double		sideDistY;
	double		deltaDistX;
	double		deltaDistY;
	double		perpWallDist;
	int			stepX;
	int			stepY;
	int			hit;
	int			side;
	int			lineHeight;
	int			drawStart;
	int			drawEnd;

}				t_raycast;

typedef struct	s_env
{
	void		*mlx;
	void		*win;
	void		*img;
	char		*idata;
	int			bpp;
	int			isizeline;
	int			iendian;
	int			ibits;
	double		time;
	double		oldtime;
	double		frametime;
	int			buffer[WIN_WIDTH][WIN_HEIGHT];
	t_raycast	*rc;
	t_img		**texture;
	t_player	*p;
}				t_env;

int				mouse_event(int button, int x, int y, t_env *e);
int				keyboard_event(int keycode, t_env *e);
void			img_put_pixel(t_env *e, int x, int y, int color);
int				draw(t_env *e);
int				color_in_int(t_color *color);
void			choose_color(t_color *color, int r, int g, int b);
void			fill_img(t_env *env, int color);
void			img_put_vline(t_env *e, t_vertex *v1, t_vertex *v2, int color);
void			ft_raycasting(t_env *e);

#endif
