#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "shader.hh"
#include "canvas.hh"

float zoom = 0.5f;

float centerX = 0.0f;
float centerY = 0.0f;

float screenSizeX = 800.0f;
float screenSizeY = 800.0f;

void resizeCallback(GLFWwindow* window, int width, int height)
{
	screenSizeX = width; screenSizeY = height;
	glViewport (0, 0, width, height);
}

int main(void)
{
	if( glfwInit() != GLFW_TRUE )
		return -1;
	
	auto window = glfwCreateWindow(
		static_cast<int>(screenSizeX),
		static_cast<int>(screenSizeY),
		"Mandelbrot set",
		NULL, NULL
	);
	
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, resizeCallback);

	if( !gladLoadGLLoader((GLADloadproc)(glfwGetProcAddress)) )
		return -2;

	glfwShowWindow(window);
	
	glClearColor( 0.0f, 0.0f, 0.0f, 0.0f );

	LoadCanvas();
	LoadShader();

	double time = -0.16;
	double deltaTime = 0;
	
	while (!glfwWindowShouldClose(window))
	{
		deltaTime = glfwGetTime() - time;
		time = glfwGetTime();

		if(glfwGetKey(window, GLFW_KEY_ESCAPE))
			glfwSetWindowShouldClose(window, true);
		
		if(glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
			centerY += deltaTime * zoom;
		else if(glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
			centerY -= deltaTime * zoom;
		
		if(glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
			centerX -= deltaTime * zoom;
		else if(glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
			centerX += deltaTime * zoom;

		if(glfwGetKey(window, GLFW_KEY_MINUS) == GLFW_PRESS)
			zoom *= 1.02f;
		else if(glfwGetKey(window, GLFW_KEY_EQUAL) == GLFW_PRESS)
			zoom *= 0.98f;
		
		glUniform1f(glGetUniformLocation(SHADER_HANDLE, "zoom"), zoom);
		glUniform2f(glGetUniformLocation(SHADER_HANDLE, "center"), centerX, centerY);
		glUniform2f(glGetUniformLocation(SHADER_HANDLE, "screen"), screenSizeX, screenSizeY);

		glClear(GL_COLOR_BUFFER_BIT);
		
		glUseProgram(SHADER_HANDLE);
		DrawCanvas();

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	UnloadShader();
	UnloadCanvas();

	glfwDestroyWindow(window);
	glfwTerminate();
}
