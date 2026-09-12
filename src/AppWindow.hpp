#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <print>

#ifdef _WIN32
#define GLFW_EXPOSE_NATIVE_WIN32
#include <GLFW/glfw3native.h>
#include <dwmapi.h>
#endif

class AppWindow
{
protected:
	struct MouseEvent
	{
		// information for scrolling and movement
	};

	struct KeyEvent
	{
		int key;
		int scancode;
		int action;
		int mods;
	};

public:
	float deltaTime, frameRate;
	int key, mouseButton;
	int mouseX, mouseY, pMouseX, pMouseY;
	int width, height;
	MouseEvent mouseEvent;
	KeyEvent keyEvent;

	AppWindow(int width, int height, const char* title);
	virtual ~AppWindow();

	AppWindow(const AppWindow&) = delete;
	AppWindow& operator=(const AppWindow&) = delete;

	int Run(bool loop_every_frame = true);

protected:
	struct WindowState
	{
		AppWindow* Instance;
		GLFWwindow* window;
		bool glfwWindowIsDead;

		WindowState(AppWindow* parent) :
			Instance(parent),
			window(nullptr),
			glfwWindowIsDead(false)
		{}

		void SafeDestroy()
		{
			if (!glfwWindowIsDead && window)
			{
				glfwDestroyWindow(window);
				glfwWindowIsDead = true;
			}
		}
	};

	WindowState* m_windowState = nullptr;

	virtual void Loop() = 0;
	virtual void OnInit() {};
	virtual void OnCleanup() {};
	
	virtual void OnWindowResize() {};
	virtual void OnKeyDown() {};
	virtual void OnKeyUp() {};
	virtual void OnMouseButton() {};
	virtual void OnMouseAxis(const MouseEvent& mouse_event) {};

	static void SetWindowStyling(GLFWwindow* window);
	static void SetGLViewport(GLFWwindow* window);

private:
	static void errorCallback(int error, const char* desc);
	static void closeCallback(GLFWwindow* window);
	static void keyCallback(GLFWwindow*, int key, int scancode, int action, int mods);
	static void windowSizeCallback(GLFWwindow* window, int width, int height);

	static WindowState* getWindowStateFromGLFWwindow(GLFWwindow* window);
};