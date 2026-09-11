#include "configuration.h"


int main()
{
	std::print("Hello world from {} on this fine {} at {}:{}!",
		"THE NEW PRINT FUNCTION", "Friday", 4, 32
	);

	if (!glfwInit())
	{
		std::print("Big bummer...");
		return -1;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(800, 600, "Test Test Test", NULL, NULL);

	if (!window)
	{
		std::print("Aw man...");
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);

	while (!glfwWindowShouldClose(window))
	{
		glfwSwapBuffers(window);
		glfwWaitEvents();
	}

	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}