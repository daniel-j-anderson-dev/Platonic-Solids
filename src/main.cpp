#include "../include/SDL2/SDL.h"
#include "../include/Point.h"
#include "../include/Shape3D.h"

int main(int argc, char *argv[])
{
	// Initialize SDL
	SDL_Init(SDL_INIT_VIDEO);

	// Create a window and a renderer
	SDL_Window*   window   = SDL_CreateWindow("Platonic Solids", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, SDL_WINDOW_SHOWN);
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	// Create points to draw a line between
	Point p1 = Point(500,   480/2, 0);
	Point p2 = Point(640/2, 480/2, 0);

	//Point axis = Point(0.57735026919, 0.57735026919, 0.57735026919);	// 👍
	Point axis = Point(0, 0, 1); 

	double angle = 0;

	// Wait for the user to close the window
	SDL_Event event;
	while (true)
	{
		// TODO: Handle quit event
		// Here we can see a little bit of Daniel's CRINGE
		if (SDL_PollEvent(&event) && event.type == SDL_QUIT)
		{
			break;
		}

		// Clear window of previous frame
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		SDL_RenderClear(renderer);

		// Draw the line
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderDrawLine(renderer, p1.getX(), p1.getY(), p2.getX(), p2.getY());
		SDL_RenderPresent(renderer);

		// Move each point
		// p1.increment();
		// Lol SUCK IT Daniel now the line just grows
		// p2.increment();

		// angle++;
		p1.rotate(p2, axis, M_PI/2);

		// Wait about 1/60 of a second
		SDL_Delay(17); 
	}

	// Clean up
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();

	return 0;
}
