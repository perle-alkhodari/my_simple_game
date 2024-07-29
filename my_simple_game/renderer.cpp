
void Render();
void ClearScreen(int color);
void DrawRect(int width, int height, int position, int color);



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

int Bracket(int minVal, int maxVal, int val) {
	val = (val < minVal) ? minVal : ((val > maxVal) ? maxVal : val);
	return val;
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