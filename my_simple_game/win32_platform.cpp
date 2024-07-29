#include <windows.h>

bool isRunning = true;

// storing all the buffer variables in a struct
// to keep things organised.
struct RenderBuffer {
	int width, height, size;
	void* memory;
	BITMAPINFO bitmapInfo;
};
RenderBuffer renderBuffer;
//void* bufferMemory;
//int bufferWidth;
//int bufferHeight;
//int bufferSize;
//BITMAPINFO bufferBitmapInfo;

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
		// using a temp pixel pointer and looping through each pixel on our screen.
		// each pixel if of type unsigned int and the first one is bufferMemory.
		unsigned int* pixel = (unsigned int*)renderBuffer.memory;
		for (int y = 0; y < renderBuffer.height; y++) {
			for (int x = 0; x < renderBuffer.width; x++) {
				// Do something to the pixel.
				// then increment to next.
				*pixel++ = (0Xff00ff * x) + (0x00ff00 * y);
			}
		}

// Refresh
		// Need the Device Context, Buffer information, and the Bitmap Info
		StretchDIBits(hDeviceContext, 0, 0, renderBuffer.width, renderBuffer.height, 0, 0, renderBuffer.width, renderBuffer.height, renderBuffer.memory, &renderBuffer.bitmapInfo, DIB_RGB_COLORS, SRCCOPY);
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
		renderBuffer.width = rect.right - rect.left;
		renderBuffer.height = rect.bottom - rect.top;

		// number of pixels     size of each pixel
		renderBuffer.size = (renderBuffer.width * renderBuffer.height) * sizeof(unsigned int);
		// Checking if bufferMemory contains stuff in it, if it does
		// we will free that space and make a new one in place of it
		if (renderBuffer.memory) VirtualFree(renderBuffer.memory, 0, MEM_RELEASE);
		// Reserving memory in the heap without specifying the type
		// because we need this space to store the buffer size.
		// bufferMemory is of type void*
		// PAGE_READWRITE because the content in the the space in this heap is
		// going to keep changing as the user resizes the window.
		renderBuffer.memory = VirtualAlloc(0, renderBuffer.size, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
		// Now send this to windows to use it in render.

		// You need the bitmap info header for render as well.
		renderBuffer.bitmapInfo.bmiHeader.biSize = sizeof(renderBuffer.bitmapInfo.bmiHeader);
		renderBuffer.bitmapInfo.bmiHeader.biWidth = renderBuffer.width;
		renderBuffer.bitmapInfo.bmiHeader.biHeight = renderBuffer.height;
		renderBuffer.bitmapInfo.bmiHeader.biPlanes = 1;
		renderBuffer.bitmapInfo.bmiHeader.biBitCount = 32;
		renderBuffer.bitmapInfo.bmiHeader.biCompression = BI_RGB;
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