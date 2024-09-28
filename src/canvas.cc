#include "canvas.hh"

#include <glad/glad.h>

const float vertices[6 * 2] = {
	-1, -1,  // bottom left corner
	-1,  1,  // top left corner
	1,  1,  // top right corner
	1, -1,  // bottom right corner
	-1, -1,  // bottom left corner
	1,  1,  // top right corner
};	

void LoadCanvas()
{
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void DrawCanvas()
{
	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, 6);
}

void UnloadCanvas()
{
	glDeleteBuffers(1, &VBO);
	glDeleteVertexArrays(1, &VAO);
}
