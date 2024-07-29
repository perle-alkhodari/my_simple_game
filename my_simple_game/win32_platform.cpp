#include <windows.h>
bool isRunning = true;

// This is for the callback (window.lpfnWndProc)
LRESULT CALLBACK window_callback(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);


int WinMain(HINSTANCE hInst, HINSTANCE hInstPrev, PSTR cmdline, int cmdshow)
{
	// Create Window Class
	WNDCLASS window_class = {};
	// Makes sure you r drawing the window horizontal & vertical
	window_class.style = CS_HREDRAW | CS_VREDRAW;
	// Class name
	window_class.lpszClassName = L"Window Class";
	// Callback function (triggered when anything happens to the window)
	window_class.lpfnWndProc = window_callback;
	// Get window handle
	window_class.hInstance = hInst;


	// Register Class
	RegisterClass(&window_class);


	// Create Window
	HWND window = CreateWindowEx(
		0,									// Optional window styles.
		window_class.lpszClassName,				// Window class
		L"Learn to Program Windows",		// Window text
		WS_OVERLAPPEDWINDOW | WS_VISIBLE,   // Window style

											// Size and position
		CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,

		NULL,								// Parent window    
		NULL,								// Menu
		window_class.hInstance,					// Instance handle
		NULL								// Additional application data
	);


	// Loop that keeps the window running
	while (isRunning) {

		// Input
		MSG message;
		while (PeekMessage(&message, window, 0, 0, PM_REMOVE)) { 
			TranslateMessage(&message);
			DispatchMessageW(&message);
		}

		// Sim

		// Refresh
	}
}

LRESULT CALLBACK window_callback(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	LRESULT result = 0;

	// Switch that deals with the different call back messages
	switch (uMsg) {
	case WM_CLOSE:
	case WM_DESTROY:
		isRunning = false;
		break;

	default:
		result = DefWindowProc(hwnd, uMsg, wParam, lParam);
	}

	return result;
}