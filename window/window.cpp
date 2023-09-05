#include <better_fractol.h>

int sdl_init(t_vars &vars)
{
	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE); 

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);

	vars.window = SDL_CreateWindow(vars.name.c_str(), 0, 0, WIDTH, HEIGHT, SDL_WINDOW_OPENGL);
	vars.context = SDL_GL_CreateContext(vars.window);
	glewExperimental = GL_TRUE;

	if (GLEW_OK != glewInit()) 
	{ 
		std::cout << "Failed to initialize GLEW" << std::endl; 
		return 0; 
	}

	glViewport(0, 0, WIDTH, HEIGHT);

	float vertices[] = 
	{
	//    x      y      z   
	    -1.0f, -1.0f, -0.0f,
	     1.0f,  1.0f, -0.0f,
	    -1.0f,  1.0f, -0.0f,
	     1.0f, -1.0f, -0.0f
	};
	 
	unsigned int indices[] = 
	{
	//  2---,1
	//  | .' |
	//  0'---3
	    0, 1, 2,
	    0, 3, 1
	};

	unsigned int VBO, EBO;
    glGenVertexArrays(1, &(vars.VAO));
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
 
    glBindVertexArray(vars.VAO);
 
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
 
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
 
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
 
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    return 1;
}

void deal_key(SDL_KeyboardEvent &event, t_vars &vars)
{
	switch (event.keysym.sym)
	{
		case SDLK_ESCAPE:
			vars.run = false;
			break;

		case SDLK_w:
			move(vars, 0, 1);
			break;

		case SDLK_s:
			move(vars, 0, -1);
			break;

		case SDLK_a:
			move(vars, -1, 0);
			break;

		case SDLK_d:
			move(vars, 1, 0);
			break;

		case SDLK_LSHIFT:
			zoom(vars, 1);
			break;

		case SDLK_LCTRL:
			zoom(vars, -1);
			break;

		case SDLK_UP:
			next_julia(vars, 0, 1);
			break;

		case SDLK_DOWN:
			next_julia(vars, 0, -1);
			break;

		case SDLK_LEFT:
			next_julia(vars, -1, 0);
			break;

		case SDLK_RIGHT:
			next_julia(vars, 1, 0);
			break;

		default:
			break;
	}
}

void deal_mouse_scroll(SDL_MouseWheelEvent &event, t_vars &vars)
{
	if (event.y > 0)
		zoom(vars, 1);
	else if (event.y < 0)
		zoom(vars, -1);
}

void main_loop(t_vars &vars)
{
	SDL_Event windowEvent;
	vars.run = true;
	// std::vector<float> pixel_data(WIDTH * HEIGHT, 0.0f);
	// glm::vec4 ranges = glm::vec4(0.0001f, 0.33333f, 0.66667f, 1.00f);

	while (vars.run)
	{ 
		if (SDL_PollEvent(&windowEvent)) 
		{
			switch (windowEvent.type)
			{
				case SDL_QUIT:
					vars.run = false;
					break;

				case SDL_KEYDOWN:
					deal_key(windowEvent.key, vars);
					break;

				case SDL_MOUSEWHEEL:
					deal_mouse_scroll(windowEvent.wheel, vars);
					break;

				default:
					break;
			} 
		} 

		// Clear the colorbuffer 
		// glClearColor(0.2f, 0.3f, 0.3f, 1.0f); 
		glClear(GL_COLOR_BUFFER_BIT);

		vars.shader->use();
		vars.shader->set_float("zoom", vars.zoom);
		vars.shader->set_float("center_x", vars.center_x);
		vars.shader->set_float("center_y", vars.center_y);
		// vars.shader->set_vec4("color_ranges", ranges);
		if (vars.name == "Julia")
		{
			vars.shader->set_float("julia_real", vars.julia_real);
			vars.shader->set_float("julia_img", vars.julia_img);
		}
		// glReadPixels(0, 0, WIDTH, HEIGHT, GL_DEPTH_COMPONENT, GL_FLOAT, pixel_data.data());
		// ranges = find_ranges(pixel_data);

		glBindVertexArray(vars.VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		// draw OpenGL 

		SDL_GL_SwapWindow(vars.window); 
	}
}