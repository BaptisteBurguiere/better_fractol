#include <better_fractol.h>

int is_arg(std::string arg, t_vars &vars)
{
	if (arg == "Julia")
	{
		vars.shader_path = "shaders/julia.shader";
		vars.name = "Julia";
		vars.center_x = 0.0f;
		vars.center_y = 0.0f;
		vars.zoom = 4.0f;
		vars.julia_real = -1.0f;
		vars.julia_img = 0.0f;
		return 1;
	}
	else if (arg == "Mandelbrot")
	{
		vars.shader_path = "shaders/mandelbrot.shader";
		vars.name = "Mandelbrot";
		vars.center_x = 0.0f;
		vars.center_y = 0.0f;
		vars.zoom = 2.0f;
		vars.julia_real = 0.0f;
		vars.julia_img = 0.0f;
		return 1;
	}
	else if (arg == "Burning_ship")
	{
		vars.shader_path = "shaders/burning_ship.shader";
		vars.name = "Burning_ship";
		vars.center_x = 0.0f;
		vars.center_y = 0.0f;
		vars.zoom = 2.0f;
		vars.julia_real = 0.0f;
		vars.julia_img = 0.0f;
		return 1;
	}
	return 0;
}



int main(int argc, char **argv)
{
	t_vars vars;

	if (argc != 2 || !is_arg(argv[1], vars))
	{
		std::cout << "Choose a fractal:" << std::endl;
		std::cout << "Julia" << std::endl;
		std::cout << "Mandelbrot" << std::endl;
		std::cout << "Burning_ship" << std::endl;
		return EXIT_SUCCESS;
	}

	if (!sdl_init(vars))
		return EXIT_FAILURE;

    vars.shader = new Shader("shaders/vertex.shader", vars.shader_path);

	main_loop(vars);

	delete vars.shader;
	SDL_GL_DeleteContext(vars.context); 
	SDL_DestroyWindow(vars.window); 
	SDL_Quit(); 

	return EXIT_SUCCESS; 
}