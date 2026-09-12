#include "AppWindow.hpp"

#ifdef _WIN32
void AppWindow::SetWindowStyling(GLFWwindow* window)
{
	HWND hwnd = glfwGetWin32Window(window);
	BOOL useDarkMode = TRUE;
	DwmSetWindowAttribute(hwnd, 20, &useDarkMode, sizeof(useDarkMode));
}
#else
void AppWindow::SetWindowStyling(GLFWwindow* window) { }
#endif

AppWindow::WindowState* AppWindow::getWindowStateFromGLFWwindow(GLFWwindow* window)
{
	if (window)
		return static_cast<WindowState*>(glfwGetWindowUserPointer(window));
	else
		return nullptr;
}

void AppWindow::errorCallback(int error, const char* desc)
{
	std::print(stderr, "A GLFW error has occurred ({}): {}", error, desc);
}

void AppWindow::closeCallback(GLFWwindow* window)
{
	WindowState* windowState = getWindowStateFromGLFWwindow(window);
	
	if (windowState)
		windowState->SafeDestroy();
}

void AppWindow::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	WindowState* windowState = getWindowStateFromGLFWwindow(window);

	windowState->Instance->keyEvent = KeyEvent{key, scancode, action, mods};
	windowState->Instance->key = key;

	if (action == GLFW_PRESS)
		windowState->Instance->OnKeyDown();

	if (action == GLFW_RELEASE)
		windowState->Instance->OnKeyUp();
}

void AppWindow::windowSizeCallback(GLFWwindow* window, int width, int height)
{
	WindowState* windowState = getWindowStateFromGLFWwindow(window);


	if (!windowState->glfwWindowIsDead)
	{
		glfwGetFramebufferSize(window, &width, &height);
		windowState->Instance->Loop();
		SetGLViewport(window);
		glfwSwapBuffers(window);
	}
}

void AppWindow::SetGLViewport(GLFWwindow* window)
{
	WindowState* windowState = getWindowStateFromGLFWwindow(window);

	int display_w, display_h;
	glfwGetFramebufferSize(window, &display_w, &display_h);
	glViewport(0, 0, display_w, display_h);
}

AppWindow::AppWindow(int width, int height, const char* title) :
	width(width), height(height)
{
	glfwSetErrorCallback(errorCallback);

	if (!glfwInit())
	{
		std::print(stderr, "GLFW failed to init.");
		exit(-1);
	}

	m_windowState = new WindowState(this);
	m_windowState->window = glfwCreateWindow(width, height, title, nullptr, nullptr);
	if (!m_windowState->window)
	{
		std::print(stderr, "Failed to create GLFW window.");
		exit(-1);
	}

	SetWindowStyling(m_windowState->window);

	glfwSetWindowUserPointer(m_windowState->window, m_windowState);

	glfwSetWindowCloseCallback(m_windowState->window, closeCallback);
	glfwSetKeyCallback(m_windowState->window, keyCallback);
	glfwSetFramebufferSizeCallback(m_windowState->window, windowSizeCallback);

	glfwMakeContextCurrent(m_windowState->window);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);

	glfwSwapInterval(1);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::print(stderr, "GLAD failed to initialize.");
		exit(-1);
	}

	deltaTime = 1.0;
	frameRate = 1.0;
	key = -1;
	mouseButton = -1;
	mouseX = 0;
	mouseY = 0;
	pMouseX = 0;
	pMouseY = 0;
	mouseEvent = MouseEvent{};
	keyEvent = KeyEvent{};
}

AppWindow::~AppWindow()
{
	if (!m_windowState->glfwWindowIsDead)
		m_windowState->SafeDestroy();

	glfwTerminate();
}

int AppWindow::Run(bool loop_every_frame)
{
	OnInit();

	double frame_time, last_frame_time = 0.0;
	while (!glfwWindowShouldClose(m_windowState->window))
	{
		frame_time = glfwGetTime();
		deltaTime = frame_time - last_frame_time;
		frameRate = 1.0 / deltaTime;
		last_frame_time = frame_time;

		if (loop_every_frame)
			glfwPollEvents();
		else
			glfwWaitEvents();

		if (!m_windowState->glfwWindowIsDead)
		{
			glfwGetFramebufferSize(m_windowState->window, &width, &height);
			Loop();
			SetGLViewport(m_windowState->window);
			glfwSwapBuffers(m_windowState->window);
		}
	}

	OnCleanup();
	return 0;
}