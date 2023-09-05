#include <better_fractol.h>

void move(t_vars &vars, int dir_x, int dir_y)
{
	if (dir_x == 1)
		vars.center_x += MOVE_SENSI * vars.zoom;
	else if (dir_x == -1)
		vars.center_x -= MOVE_SENSI * vars.zoom;
	else if (dir_y == -1)
		vars.center_y -= MOVE_SENSI * vars.zoom;
	else
		vars.center_y += MOVE_SENSI * vars.zoom;
}

void zoom(t_vars &vars, int dir)
{
	if (dir == 1)
	{
		vars.zoom *= 1.0 - ZOOM_SENSI;
	}
	else
	{
		vars.zoom *= 1.0 + ZOOM_SENSI;
	}
}

void next_julia(t_vars &vars, int dir_x, int dir_y)
{
	if (dir_x == 1)
		vars.julia_real += JULIA_SENSI;
	else if (dir_x == -1)
		vars.julia_real -= JULIA_SENSI;
	else if (dir_y == -1)
		vars.julia_img -= JULIA_SENSI;
	else
		vars.julia_img += JULIA_SENSI;
}