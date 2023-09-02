#ifndef BETTER_FRACTOL_H
# define BETTER_FRACTOL_H


// INCLUDES

# include <SDL2/SDL.h>
# include <GL/glew.h>
# include <SDL2/SDL_opengl.h>
# include <iostream>
# include <string>
# include <fstream>
# include <Shader.h>


// DEFINES

# define WIDTH 980
# define HEIGHT 980
# define MOVE_SENSI 0.005f
# define ZOOM_SENSI 0.02f;


// STRUCTS

typedef struct s_vars
{
	SDL_Window *window;
	SDL_GLContext context;

	unsigned int VAO;

	Shader *shader;
	float center_x;
	float center_y;
	float zoom;

	bool run;
} t_vars;


// WINDOW

int sdl_init(t_vars &vars);
void deal_key(SDL_KeyboardEvent &event, t_vars &vars);
void deal_mouse_scroll(SDL_MouseWheelEvent &event, t_vars &vars);
void main_loop(t_vars &vars);


// ACTIONS

void move(t_vars &vars, int dir_x, int dir_y);
void zoom(t_vars &vars, int dir);

#endif