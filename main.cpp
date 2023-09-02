#include <better_fractol.h>

int main(void)
{
	t_vars vars;


	if (!sdl_init(vars))
		return EXIT_FAILURE;

    vars.shader = new Shader("shaders/vertex.shader", "shaders/mandelbrot.shader");

	main_loop(vars);

	delete vars.shader;
	SDL_GL_DeleteContext(vars.context); 
	SDL_DestroyWindow(vars.window); 
	SDL_Quit(); 

	return EXIT_SUCCESS; 
}