#include "helpers.cpp"


void Render();
void ClearScreen(int color);
void DrawRect(int posX, int posY, int width, int height, int color);
void DrawRectPercent(float x, float y, float width, float height, int color);


void Render(){ 
	unsigned int* pixel = (unsigned int*)renderBuffer.memory;
	for (int y = 0; y < renderBuffer.height; y++) {
		for (int x = 0; x < renderBuffer.width; x++) {
			// Do something to the pixel.
			// then increment to next.
			*pixel++ = (0Xff00ff * x) + (0x00ff00 * y);
		}
	}
}

void ClearScreen(int color) {
	unsigned int* pixel = (unsigned int*)renderBuffer.memory;
	for (int y = 0; y < renderBuffer.height; y++) {
		for (int x = 0; x < renderBuffer.width; x++) {
			// Do something to the pixel.
			// then increment to next.
			*pixel++ = color;
		}
	}
} 

void DrawRect(int posX, int posY, int width, int height, int color) {

	posX = Bracket(0, renderBuffer.width, posX);
	int posX2 = Bracket(0, renderBuffer.width, posX+width);
	posY = Bracket(0, renderBuffer.height, posY);
	int posY2 = Bracket(0, renderBuffer.height, posY+height);

	for (int i = posY; i < posY2; i++) {
		unsigned int* pixel = (unsigned int*)renderBuffer.memory + (((i)*renderBuffer.width) + posX);
		for (int j = posX; j < posX2; j++) {
			*pixel++ = color;
		}
	}
}

void DrawRectDynamicPosition(float x, float y, float width, float height, int color)
{
	x /= 100;
	y /= 100;
	x *= renderBuffer.width;
	y *= renderBuffer.height;
	x -= (width / 2);
	y -= (height / 2);

	DrawRect(x, y, width, height, color);
}

void DrawRectDynamicPosAndSize(float x, float y, float width, float height, int color)
{
	Bracket(0, 100, x);
	Bracket(0, 100, y);
	Bracket(0, 100, width);
	Bracket(0, 100, height);

	x /= 100;
	y /= 100;
	width /= 100;
	height /= 100;
	width *= renderBuffer.width;
	height *= renderBuffer.height;
	x *= renderBuffer.width;
	y *= renderBuffer.height;
	x -= (width / 2);
	y -= (height / 2);

	DrawRect(x, y, width, height, color);
}
