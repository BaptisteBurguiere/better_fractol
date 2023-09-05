#ifndef BETTER_FRACTOL_H
# define BETTER_FRACTOL_H


// INCLUDES

# include <SDL2/SDL.h>
# include <GL/glew.h>
# include <SDL2/SDL_opengl.h>
# include <iostream>
# include <string>
# include <fstream>
# include <vector>
# include <algorithm>
# include <Shader.h>


// DEFINES

# define WIDTH 980
# define HEIGHT 980
// # define WIDTH 1920
// # define HEIGHT 1080
# define MOVE_SENSI 0.005f
# define ZOOM_SENSI 0.02f
# define JULIA_SENSI 0.001f


// STRUCTS

typedef struct s_vars
{
	SDL_Window *window;
	SDL_GLContext context;

	unsigned int VAO;

	Shader *shader;
	std::string shader_path;
	std::string name;
	float center_x;
	float center_y;
	float zoom;
	float julia_real;
	float julia_img;

	bool run;
} t_vars;


// WINDOW

int sdl_init(t_vars &vars);
void deal_key(SDL_KeyboardEvent &event, t_vars &vars);
void deal_mouse_scroll(SDL_MouseWheelEvent &event, t_vars &vars);
void main_loop(t_vars &vars);


// COLORS

glm::vec4 find_ranges(std::vector<float> & data);


// ACTIONS

void move(t_vars &vars, int dir_x, int dir_y);
void zoom(t_vars &vars, int dir);
void next_julia(t_vars &vars, int dir_x, int dir_y);

#endif