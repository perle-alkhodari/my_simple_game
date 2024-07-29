#define BACKGROUND_COLOR 0x237458

bool isDown(int inputButton);
bool isPressed(int inputButton);
bool isReleased(int inputButton);

void simulate_game(Input* input);

float xPos = 50;
float yPos = 50;
float xSize = 60;
float ySize = 60;
void simulate_game(Input* input)
{
	ClearScreen(BACKGROUND_COLOR);

	if (isPressed(BUTTON_UP)) {
		yPos += 1;
	}
	if (isPressed(BUTTON_LEFT)) {
		xPos -= 1;
	}
	if (isPressed(BUTTON_DOWN)) {
		yPos -= 1;
	}
	if (isPressed(BUTTON_RIGHT)) {
		xPos += 1;
	}
	DrawRectDynamicPosAndSize(xPos, yPos, xSize, ySize, 0x000000);
}




bool isDown(int inputButton)
{
	return input.buttons[inputButton].isDown;
}

bool isPressed(int inputButton)
{
	return input.buttons[inputButton].isDown && input.buttons[inputButton].changed;
}

bool isReleased(int inputButton)
{
	return !input.buttons[inputButton].isDown && input.buttons[inputButton].changed;
}
