#include "configuration.h"

class WFC : public AppWindow
{
public:
	WFC(int w, int h, const char* title) : AppWindow(w, h, title) {};

	void Loop() override
	{
		glClearColor(0.3f, 0.5f, 0.4f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
	}
};

int main()
{
	WFC wfcApp(800, 600, "Test");
	wfcApp.Run();
}