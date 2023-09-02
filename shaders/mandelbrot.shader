#version 330 core

in vec4 gl_FragCoord;
out vec4 frag_color;
// out float gl_FragDepth;
 
uniform float center_x;
uniform float center_y;
uniform float zoom;

#define MAX_ITERATION 500
#define WIDTH 980.0
#define HEIGHT 980.0

int get_iterations()
{
	float real = ((gl_FragCoord.x / WIDTH - 0.7) * zoom + center_x);
	float img = ((gl_FragCoord.y / HEIGHT - 0.5) * zoom + center_y);

	int i = 0;
	float const_real = real;
	float const_img = img;

	while (i < MAX_ITERATION)
	{
		float tmp_real = real;
		real = (real * real - img * img) + const_real;
		img = (2.0 * tmp_real * img) + const_img;

		float dist = real * real + img * img;

		if (dist > 4.0)
			break;

		i++;
	}
	return i;
}

vec4 return_color()
{
	int iter = get_iterations();
	if (iter == MAX_ITERATION)
	{
		// glFragDepth = 0.0f;
		return vec4(0.0f, 0.0f, 0.0f, 1.0f);
	}

	float i = float(iter) / MAX_ITERATION;
	return vec4(0.0f, i, 0.0f, 1.0f);
}

void main(void)
{
	frag_color = return_color();
}