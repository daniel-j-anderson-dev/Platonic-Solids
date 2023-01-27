#include "../include/SDL2/SDL.h"
#include "../include/Point.h"
#include "../include/Shape3D.h"
#include "../include/Quaternion.h"
const int WINDOW_WIDTH  = 1920;
const int WINDOW_HEIGHT = 1080;
const Point ORIGIN = Point(WINDOW_WIDTH/2, WINDOW_HEIGHT/2, 0);
const Point xAxis  = Point(1, 0, 0);
const Point yAxis  = Point(0, 1, 0);
const Point zAxis  = Point(0, 0, 1);

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

// Returns true if escape is pressed
bool handleInput(SDL_Event event, Shape3D &shape)
{
	double movementSpeed = 10;
	double angle 	 = .1;
	Point  axis			 = Point(0, 0, 0);
	if (SDL_PollEvent(&event))
	{
		if (event.type == SDL_KEYDOWN)
		{
			SDL_Keycode key = event.key.keysym.sym;
			if (key == SDLK_a)
			{
				axis.setX(1);
				angle = .1;
			}
			if (key == SDLK_d)
			{
				axis.setX(1);
				angle = -.1;
			}
			if (key == SDLK_w)
			{
				axis.setY(1);
				angle = .1;
			}
			if (key == SDLK_s)
			{
				axis.setY(1);
				angle = -.1;
			}
			if (key == SDLK_e)
			{
				axis.setZ(1);
				angle = .1;
			}
			if (key == SDLK_q)
			{
				axis.setZ(1);
				angle = -.1;
			}

			shape.rotate(axis, angle);

			//quit
			if (key == SDLK_ESCAPE)
			{
				return true;
			}
		}
	}
	return false;
}

int main(int argc, char *argv[])
{
	// Initialize SDL
	SDL_Init(SDL_INIT_VIDEO);

	// Create a window and a renderer
	SDL_Window*   window   = SDL_CreateWindow("Platonic Solids", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	// Create point to draw a line between and angle and axis to rotate about
	// Point  point  = Point(250, WINDOW_HEIGHT/2, 0);
	Shape3D cube  = Shape3D("Cube");

	SDL_Event event;
	while (true)
	{
		clearScreen(renderer);

		cube.draw(renderer, ORIGIN);

		handleInput(event, cube);
		// drawLine(renderer, point, ORIGIN);


		// if(handleInput(event, point))
		// {
		// 	break;	// stop execution if esc is pressed
		// }
	}

	// Clean up
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();

	return 0;
}
