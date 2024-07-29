#include <windows.h>

bool isRunning = true;

void* bufferMemory;
int bufferWidth;
int bufferHeight;
int bufferSize;
BITMAPINFO bufferBitmapInfo;

// This is for the callback (window.lpfnWndProc)
LRESULT CALLBACK WindowCallback(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);


int WinMain(HINSTANCE hInst, HINSTANCE hInstPrev, PSTR cmdline, int cmdshow)
{
	// Create Window Class
	WNDCLASS windowClass = {};
	// Makes sure you r drawing the window horizontal & vertical
	windowClass.style = CS_HREDRAW | CS_VREDRAW;
	// Class name
	windowClass.lpszClassName = L"Window Class";
	// Callback function (triggered when anything happens to the window)
	windowClass.lpfnWndProc = WindowCallback;
	// Get window handle
	windowClass.hInstance = hInst;


	// Register Class
	RegisterClass(&windowClass);


	// Create Window
	HWND window = CreateWindowEx(
		0,									// Optional window styles.
		windowClass.lpszClassName,				// Window class
		L"Learn to Program Windows",		// Window text
		WS_OVERLAPPEDWINDOW | WS_VISIBLE,   // Window style

											// Size and position
		CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,

		NULL,								// Parent window    
		NULL,								// Menu
		windowClass.hInstance,					// Instance handle
		NULL								// Additional application data
	);
	// Device context for strechDIBits() function in render
	HDC hDeviceContext = GetDC(window);


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
		// Need the Device Context, Buffer information, and the Bitmap Info
		StretchDIBits(hDeviceContext, 0, 0, bufferWidth, bufferHeight, 0, 0, bufferWidth, bufferHeight, bufferMemory, &bufferBitmapInfo, DIB_RGB_COLORS, SRCCOPY);
	}
}

LRESULT CALLBACK WindowCallback(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	LRESULT result = 0;

	// Switch that deals with the different call back messages
	switch (uMsg) {
	case WM_CLOSE:
	case WM_DESTROY:
		isRunning = false;
		break;

	case WM_SIZE:						// Getting the new size of the window
		RECT rect;						// Create a rectangle struct
		GetClientRect(hwnd, &rect);		// And pass it into this function along with the window
		bufferWidth = rect.right - rect.left;
		bufferHeight = rect.bottom - rect.top;

		// number of pixels     size of each pixel
		bufferSize = (bufferWidth * bufferHeight) * sizeof(unsigned int);
		// Checking if bufferMemory contains stuff in it, if it does
		// we will free that space and make a new one in place of it
		if (bufferMemory) VirtualFree(bufferMemory, 0, MEM_RELEASE);
		// Reserving memory in the heap without specifying the type
		// because we need this space to store the buffer size.
		// bufferMemory is of type void*
		// PAGE_READWRITE because the content in the the space in this heap is
		// going to keep changing as the user resizes the window.
		bufferMemory = VirtualAlloc(0, bufferSize, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
		// Now send this to windows to use it in render.

		// You need the bitmap info header for render as well.
		bufferBitmapInfo.bmiHeader.biSize = sizeof(bufferBitmapInfo.bmiHeader);
		bufferBitmapInfo.bmiHeader.biWidth = bufferWidth;
		bufferBitmapInfo.bmiHeader.biHeight = bufferHeight;
		bufferBitmapInfo.bmiHeader.biPlanes = 1;
		bufferBitmapInfo.bmiHeader.biBitCount = 32;
		bufferBitmapInfo.bmiHeader.biCompression = BI_RGB;
		// using the struct below to know which attributes this struct
		// contains that we can change or need to fill in.
		// 
		//typedef struct tagBITMAPINFOHEADER {
		//	DWORD biSize;
		//	LONG  biWidth;
		//	LONG  biHeight;
		//	WORD  biPlanes;
		//	WORD  biBitCount;
		//	DWORD biCompression;
		//	DWORD biSizeImage;
		//	LONG  biXPelsPerMeter;
		//	LONG  biYPelsPerMeter;
		//	DWORD biClrUsed;
		//	DWORD biClrImportant;
		//} BITMAPINFOHEADER, * LPBITMAPINFOHEADER, * PBITMAPINFOHEADER;

		break;
	default:
		result = DefWindowProc(hwnd, uMsg, wParam, lParam);
	}

	return result;
}