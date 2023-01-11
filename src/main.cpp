#include "../include/SDL2/SDL.h"

int main(int argc, char *argv[])
{
	// Initialize SDL
	SDL_Init(SDL_INIT_VIDEO);

	// Create a window
	SDL_Window *window = SDL_CreateWindow("My Window", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, SDL_WINDOW_SHOWN);

	// Wait for the user to close the window
	SDL_Event event;
	while (true)
	{
		if (SDL_PollEvent(&event) && event.type == SDL_QUIT)
		{
			break;
		}
	}

	// Clean up
	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}
