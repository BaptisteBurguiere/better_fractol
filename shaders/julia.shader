#version 430 core

in vec4 gl_FragCoord;
out vec4 frag_color;
// out float gl_FragDepth;
 
uniform float center_x;
uniform float center_y;
uniform float zoom;
uniform float julia_real;
uniform float julia_img;

#define MAX_ITERATION 100
#define WIDTH 980.0
#define HEIGHT 980.0
// #define WIDTH 1920.0
// #define HEIGHT 1080.0

int get_iterations()
{
	float real = ((gl_FragCoord.x / WIDTH - 0.5) * zoom + center_x);
	float img = ((gl_FragCoord.y / HEIGHT - 0.5) * zoom + center_y);

	int i = 0;
	// float const_real = real;
	// float const_img = img;

	while (i < MAX_ITERATION)
	{
		float tmp_real = real;
		real = (real * real - img * img) + julia_real;
		img = (2.0 * tmp_real * img) + julia_img;

		float dist = real * real + img * img;

		if (dist > 4.0)
			break;

		i++;
	}
	return i;
}

vec4 return_color()
{
	float warmToColdGradient[20][3] = {
	    {0.980, 0.996, 0.996},  // Very Light Cyan
	    {0.878, 0.984, 0.996},  // Light Cyan
	    {0.776, 0.972, 0.996},  // Light Cyan
	    {0.678, 0.960, 0.996},  // Light Cyan
	    {0.580, 0.949, 0.996},  // Light Cyan
	    {0.482, 0.937, 0.996},  // Light Cyan
	    {0.384, 0.925, 0.996},  // Light Cyan
	    {0.286, 0.913, 0.996},  // Light Cyan
	    {0.188, 0.901, 0.996},  // Light Cyan
	    {0.090, 0.890, 0.996},  // Light Cyan
	    {0.000, 0.870, 0.996},  // Light Cyan
	    {0.000, 0.745, 0.996},  // Light Blue
	    {0.000, 0.623, 0.996},  // Light Blue
	    {0.000, 0.502, 0.996},  // Light Blue
	    {0.000, 0.380, 0.996},  // Light Blue
	    {0.000, 0.258, 0.996},  // Light Blue
	    {0.000, 0.137, 0.996},  // Light Blue
	    {0.000, 0.015, 0.996},  // Light Blue
	    {0.000, 0.000, 0.996},  // Blue
	    {0.000, 0.000, 0.870}   // Dark Blue
	};

	int i = get_iterations();
	if (i == MAX_ITERATION)
	{
		// glFragDepth = 0.0f;
		return vec4(0.0f, 0.0f, 0.0f, 1.0f);
	}
	return vec4(warmToColdGradient[i % 10][0], warmToColdGradient[i % 20][1], warmToColdGradient[i % 20][2], 1.0f);
}

void main(void)
{
	frag_color = return_color();
}