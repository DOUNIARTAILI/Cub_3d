/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaqbour <mmaqbour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/29 20:57:09 by drtaili           #+#    #+#             */
/*   Updated: 2023/09/06 14:08:55 by mmaqbour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

static void	draw_line(t_data *data, int x, int draw_start)
{
	int	y;

	y = 0;
	while (y < draw_start)
	{
		data->addr[y * WIN_WIDTH + x] = 0x87CEEB;
		y++;
	}
	while (y < WIN_HEIGHT)
	{
		data->addr[y * WIN_WIDTH + x] = 0x7CFC00;
		y++;
	}
}
// floor : 0xDC6400 ceilling : 0xE11E00

static int	get_color(t_data *data, t_dda *dda_, t_raycast *rc)
{
	int	color;

	color = 0;
	//side = 0 => (top or bottom)
	//side = 1 => (left or right)
	if (dda_->side == 0 && rc->ray.x > 0)//south
		color = *(data->cnv_addr1 + (data->tex_h * data->texy + data->texx));
	else if (dda_->side == 0 && rc->ray.x < 0)//north
		color = *(data->cnv_addr2 + (data->tex_h * data->texy + data->texx));
	else if (dda_->side == 1 && rc->ray.y > 0)//east
		color = *(data->cnv_addr3 + (data->tex_h * data->texy + data->texx));
	else if (dda_->side == 1 && rc->ray.y < 0)//west
		color = *(data->cnv_addr4 + (data->tex_h * data->texy + data->texx));
	return (color);
}

void	texture_prep(t_data *data, t_dda *dda_, t_raycast *rc)
{
	double	wallx;

	if (dda_->side == 0)
		wallx = data->pos.y + dda_->perp_wall_dist * rc->ray.y;
	else
		wallx = data->pos.x + dda_->perp_wall_dist * rc->ray.x;
	wallx -= floor(wallx);
	data->texx = (int)(wallx * (double)data->tex_w);
	if (dda_->side == 0 && rc->ray.x > 0) // (south)
		data->texx = data->tex_w - data->texx - 1;
	if (dda_->side == 1 && rc->ray.y < 0) // (west)
		data->texx = data->tex_w - data->texx - 1;
}

void	texture_loop(t_data *data, t_dda *dda_, t_raycast *rc, int x)
{
	double	step;
	double	texpos;
	int		y;
	int		color;

	color = 0;
	texture_prep(data, dda_, rc);
	step = 1.0 * data->tex_h / dda_->line_height;
	texpos = (dda_->draw_start - WIN_HEIGHT / 2 + dda_->line_height / 2) * step;
	y = dda_->draw_start;
	while (y < dda_->draw_end + 1)
	{
		data->texy = (int)texpos & (data->tex_h - 1);
		texpos += step;
		color = get_color(data, dda_, rc);
		if (dda_->side == 1)
			color = (color >> 1) & 8355711;
		data->addr[y * WIN_WIDTH + x] = color;
		y++;
	}
}

void	raycast_helper(t_data *data, t_raycast *rc, t_dda *dda_, int x)
{
	(*rc).camera_x = 2.0 * x / (double)WIN_WIDTH - 1;
	(*rc).ray.x = data->dir.x + data->plane.x * (*rc).camera_x;
	(*rc).ray.y = data->dir.y + data->plane.y * (*rc).camera_x;
	dda(data, rc, dda_);
	(*dda_).line_height = (int)(WIN_HEIGHT / (*dda_).perp_wall_dist);
	(*dda_).draw_start = (int)(-(*dda_).line_height / 2.0)
		+ (int)(WIN_HEIGHT / 2.0);
}

int	raycast(void *param)
{
	t_data		*data;
	t_raycast	rc;
	t_dda		dda_;
	int			x;

	x = 0;
	data = param;
	move_shape(data);
	while (x < WIN_WIDTH)
	{
		raycast_helper(data, &rc, &dda_, x);
		if (dda_.draw_start < 0)
			dda_.draw_start = 0;
		dda_.draw_end = (int)(dda_.line_height / 2.0) + (int)(WIN_HEIGHT / 2.0);
		if (dda_.draw_end >= WIN_HEIGHT)
			dda_.draw_end = WIN_HEIGHT - 1;
		draw_line(data, x, dda_.draw_start);
		texture_loop(data, &dda_, &rc, x);
		x++;
	}
	draw_map2d(data);
	mlx_clear_window(data->mlx.mlx_ptr, data->mlx.win_ptr);
	mlx_put_image_to_window(data->mlx.mlx_ptr,
		data->mlx.win_ptr, data->img, 0, 0);
	return (0);
}
