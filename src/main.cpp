#include "../include/SDL2/SDL.h"
#include "../include/Point.h"
#include "../include/Shape3D.h"
#include "../include/Quaternion.h"
#include <iostream>
#include <cmath>

void drawLine(SDL_Renderer* renderer, Point a, Point b)
{
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderDrawLine(renderer, a.getX(), a.getY(), b.getX(), b.getY());
	SDL_RenderPresent(renderer);
}

void clearScreen(SDL_Renderer* renderer)
{
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderClear(renderer);
}

double lengthOfLine(Point a, Point b)
{
	double dx  = b.getX() - a.getX();
	double dy  = b.getY() - a.getY();
	double dz  = b.getZ() - a.getZ();
	double dx2 = dx * dx;
	double dy2 = dy * dy;
	double dz2 = dz * dz;
	return sqrt(dx2 + dy2 + dz2);
}

int main(int argc, char *argv[])
{
	const int WINDOW_WIDTH  = 640;
	const int WINDOW_HEIGHT = 480;
	// Initialize SDL
	SDL_Init(SDL_INIT_VIDEO);

	// Create a window and a renderer
	SDL_Window*   window   = SDL_CreateWindow("Platonic Solids", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	// Create points to draw a line between
	// and angle and axis to rotate about
	Point  point  = Point(500, WINDOW_HEIGHT/2, 0);
	Point  origin = Point(WINDOW_WIDTH/2, WINDOW_HEIGHT/2, 0);
	Point  axis   = Point(0, 0, 1);
	double angle  = .01;

	int counter = 0;

	SDL_Event event;
	while (true)
	{
		// TODO: Handle quit event
		if (SDL_PollEvent(&event) && event.type == SDL_QUIT)
		{
			break;
		}

		clearScreen(renderer);

		drawLine(renderer, point, origin);

		point.rotate(origin, axis, angle);

		// Wait about 1/60 of a second
		SDL_Delay(16.67);
		counter++;
	}

	// Clean up
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();

	return 0;
}
