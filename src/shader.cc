#include "shader.hh"

#include <iostream>
#include <cstring>

void LoadShader()
{
	GLuint vertex, fragment;
	
	int success = 0;
	char error_message[512];

// === VERTEX ===	
	vertex = glCreateShader(GL_VERTEX_SHADER);

	const int vSize = std::strlen(vertexShader);
	glShaderSource(vertex, 1, &vertexShader, &vSize);
	glCompileShader(vertex);

	glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertex, 512, nullptr, error_message);
		std::cout << "Error compiling vertex shader: " << error_message << "\n";
	}

// === FRAGMENT ===	
	fragment = glCreateShader(GL_FRAGMENT_SHADER);

	const int fSize = std::strlen(fragmentShader);
	glShaderSource(fragment, 1, &fragmentShader, &fSize);
	glCompileShader(fragment);

	glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragment, 512, nullptr, error_message);
		std::cout << "Error compiling fragment shader: " << error_message << "\n";
	}

// === PROGRAM ===	

	SHADER_HANDLE = glCreateProgram();
	
	glAttachShader(SHADER_HANDLE, vertex);
	glAttachShader(SHADER_HANDLE, fragment);
	
	glLinkProgram(SHADER_HANDLE);
 
	glGetProgramiv(SHADER_HANDLE, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(SHADER_HANDLE, 512, nullptr, error_message);
		std::cout << "Error linking shader program: " << error_message << "\n";
	}

	glDeleteShader(vertex);
	glDeleteShader(fragment);
}

void UnloadShader()
{
	glDeleteProgram(SHADER_HANDLE);
}
