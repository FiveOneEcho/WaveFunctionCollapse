#include "configuration.h"

// Very temporary; just testing build configuration

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_REPEAT)
		glfwSetWindowShouldClose(window, GLFW_TRUE);
}


int main()
{
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
	glfwSetKeyCallback(window, keyCallback);

	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::print("I'm not feeling very GLAD...");
		return -1;
	}

	glClearColor(0.2f, 0.8f, 0.4f, 1.0f);
	while (!glfwWindowShouldClose(window))
	{
		glClear(GL_COLOR_BUFFER_BIT);
		glfwSwapBuffers(window);

		glfwWaitEvents();
	}

	glfwDestroyWindow(window);
	glfwTerminate();

	return 0;
}