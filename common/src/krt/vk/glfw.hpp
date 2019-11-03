
#pragma once

#include <GLFW/glfw3.h>

class Glfw
{
public:
	Glfw(int32_t w, int32_t h);
	~Glfw(void);
	int shouldClose(void);

	int32_t w;
	int32_t h;

	GLFWwindow *window;

private:
};
