#ifndef SHADER_HH_INCLUDED
#define SHADER_HH_INCLUDED

#include <glad/glad.h>

inline unsigned SHADER_HANDLE = 0;

void LoadShader();
void UnloadShader();

inline const char* vertexShader = R"(
#version 330 core

layout(location = 0) in vec2 pos;

void main()
{
	gl_Position = vec4(pos, 0.0f, 1.0f);
}

)";

inline const char* fragmentShader = R"(

#version 330 core

in vec2 gl_FragCoord;

uniform float zoom;
uniform vec2 center;
uniform vec2 screen;

out vec4 FragColor;
 
#define MAX_ITERATIONS 512
 
int get_iterations()
{
	float aspect = min(screen.x, screen.y);

	float real = ((gl_FragCoord.x / aspect - 0.5) * zoom + center.x) * 4.0;
	float imag = ((gl_FragCoord.y / aspect - 0.5) * zoom + center.y) * 4.0;

	float const_real = real;
	float const_imag = imag;

	float r2 = 0;
	int iterations = 0;

	while(iterations < MAX_ITERATIONS && r2 < 4.0)
	{
		float tmp_real = real;

		real = (real * real - imag * imag) + const_real;
		imag = (2.0 * tmp_real * imag) + const_imag;
   
		r2 = real * real + imag * imag;
		iterations++;
	}
	return iterations;
}

void main()
{
	int iter = get_iterations();
	if(iter == MAX_ITERATIONS)
	{
		FragColor = vec4(0.0f, 0.0f, 0.0f, 1.0f);
		return;
	}

	float iterations = float(iter) / MAX_ITERATIONS;
	FragColor = vec4(iterations, iterations, iterations, 1.0f);
}

)";

#endif
