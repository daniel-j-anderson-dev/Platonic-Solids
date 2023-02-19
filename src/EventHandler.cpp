#include "../include/EventHandler.h"
#include "../include/SDL2/SDL.h"

EventHandler::EventHandler()
{
}

EventHandler::~EventHandler()
{
}

void EventHandler::handleInput(const Uint8* keys)
{
	axisOfRotation    = {0, 0, 0};
	axisOfTranslation = {0, 0, 0};
	isLocalRotation = true;
	isWorldRotation = false;

	Point xAxis = axes[0].vertices[2];
	Point yAxis = axes[1].vertices[2];
	Point zAxis = axes[2].vertices[2];

	if (keys[SDL_SCANCODE_ESCAPE])
		isRunning = false;
	if (keys[SDL_SCANCODE_LSHIFT])
		isLocalRotation = false;
	if (keys[SDL_SCANCODE_LCTRL])
		isWorldRotation = true;
	if (keys[SDL_SCANCODE_0])
	{
		setShapes();
		setAxes();
	}

	if (keys[SDL_SCANCODE_S])
		axisOfRotation.x++;
	if (keys[SDL_SCANCODE_W])
		axisOfRotation.x--;
	if (keys[SDL_SCANCODE_D])
		axisOfRotation.y++;
	if (keys[SDL_SCANCODE_A])
		axisOfRotation.y--;
	if (keys[SDL_SCANCODE_Q])
		axisOfRotation.z++;
	if (keys[SDL_SCANCODE_E])
		axisOfRotation.z--;
	if (keys[SDL_SCANCODE_SPACE])
	{
		axisOfRotation.x++;
		axisOfRotation.y++;
		axisOfRotation.z++;
	}

	if (keys[SDL_SCANCODE_RIGHT])
	{
		axisOfTranslation.x += xAxis.x;
		axisOfTranslation.y += xAxis.y;
		axisOfTranslation.z += xAxis.z;
	}
	if (keys[SDL_SCANCODE_LEFT]) // WHY DOESNT THIS WORK?!?!!?@!?!?
	{
		axisOfTranslation.x -= xAxis.x;
		axisOfTranslation.x -= xAxis.y;
		axisOfTranslation.x -= xAxis.z;
	}
	if (keys[SDL_SCANCODE_DOWN])
	{
		axisOfTranslation.x += yAxis.x;
		axisOfTranslation.y += yAxis.y;
		axisOfTranslation.z += yAxis.z;
	}
	if (keys[SDL_SCANCODE_UP])
	{
		axisOfTranslation.x -= yAxis.x;
		axisOfTranslation.y -= yAxis.y;
		axisOfTranslation.z -= yAxis.z;
	}
	if (keys[SDL_SCANCODE_PAGEUP])
	{
		axisOfTranslation.x += zAxis.x;
		axisOfTranslation.y += zAxis.y;
		axisOfTranslation.z += zAxis.z;
	}
	if (keys[SDL_SCANCODE_PAGEDOWN])
	{
		axisOfTranslation.x -= zAxis.x;
		axisOfTranslation.y -= zAxis.y;
		axisOfTranslation.z -= zAxis.z;
	}
}

void EventHandler::handleEvents(SDL_Event event)
{	
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
			case SDL_KEYDOWN:
				handleInput(SDL_GetKeyboardState(NULL));
				break;

			case SDL_KEYUP:
				handleInput(SDL_GetKeyboardState(NULL));
				break;
			// other events
		}
	}
}