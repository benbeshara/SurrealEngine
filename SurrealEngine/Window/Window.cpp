
#include "Precomp.h"
#include "Window.h"
#ifdef WIN32
#include "Win32/Win32Window.h"
#else
#include "X11/X11Window.h"
#endif

// TODO: base this off of ini setting, not dependent on OS macro

#ifdef WIN32

std::unique_ptr<DisplayWindow> DisplayWindow::Create(DisplayWindowHost* windowHost)
{
	return std::make_unique<Win32Window>(windowHost);
}

void DisplayWindow::ProcessEvents()
{
	Win32Window::ProcessEvents();
}

void DisplayWindow::RunLoop()
{
	Win32Window::RunLoop();
}

void DisplayWindow::ExitLoop()
{
	Win32Window::ExitLoop();
}

#else

std::unique_ptr<DisplayWindow> DisplayWindow::Create(DisplayWindowHost* windowHost)
{
	return std::make_unique<X11Window>(windowHost);
}

void DisplayWindow::ProcessEvents()
{
	X11Window::ProcessEvents();
}

void DisplayWindow::RunLoop()
{
	X11Window::RunLoop();
}

void DisplayWindow::ExitLoop()
{
	X11Window::ExitLoop();
}

#endif
