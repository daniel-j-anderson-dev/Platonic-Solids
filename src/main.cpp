#include "../include/SDL2/SDL.h"
#include "../include/Point.h"
#include "../include/Shape3D.h"

int main(int argc, char *argv[])
{
	// Initialize SDL
	SDL_Init(SDL_INIT_VIDEO);

	// Create a window and a renderer
	SDL_Window*   window   = SDL_CreateWindow("My Window", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, SDL_WINDOW_SHOWN);
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	// Create points to draw a line between
	Point p1 = Point(10, 10);
	Point p2 = Point(100, 100);

	// Wait for the user to close the window
	SDL_Event event;
	while (true)
	{
		if (SDL_PollEvent(&event) && event.type == SDL_QUIT)
		{
			break;
		}

		// Clear window of previous frame
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		SDL_RenderClear(renderer);

		// Draw the line
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderDrawLine(renderer, (int)p1.getX(), (int)p1.getY(), (int)p2.getX(), (int)p2.getY());
		SDL_RenderPresent(renderer);

		p1.setX(p1.getX() + 1);
		p1.setY(p1.getY() + 1);

		p2.setX(p2.getX() + 1);
		p2.setY(p2.getY() + 1);

		SDL_Delay(17); // about 1/60 of a second
	}

	// Clean up
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();

	return 0;
}
